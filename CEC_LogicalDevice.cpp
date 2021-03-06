#include <Arduino.h>
#include "CEC_LogicalDevice.h"

int CEC_LogicalDevice::_validLogicalAddresses[6][5] =
	{	{CLA_TV,					CLA_FREE_USE,			CLA_UNREGISTERED,		CLA_UNREGISTERED,	CLA_UNREGISTERED,	},
		{CLA_RECORDING_DEVICE_1,	CLA_RECORDING_DEVICE_2,	CLA_RECORDING_DEVICE_3,	CLA_UNREGISTERED,	CLA_UNREGISTERED,	},
		{CLA_PLAYBACK_DEVICE_1,		CLA_PLAYBACK_DEVICE_2,	CLA_PLAYBACK_DEVICE_3,	CLA_UNREGISTERED,	CLA_UNREGISTERED,	},
		{CLA_TUNER_1,				CLA_TUNER_2,			CLA_TUNER_3,			CLA_TUNER_4,		CLA_UNREGISTERED,	},
		{CLA_AUDIO_SYSTEM,			CLA_UNREGISTERED,		CLA_UNREGISTERED,		CLA_UNREGISTERED,	CLA_UNREGISTERED,	},
		{CLA_UNREGISTERED,			CLA_UNREGISTERED,		CLA_UNREGISTERED,		CLA_UNREGISTERED,	CLA_UNREGISTERED,	},
		};

#define MAKE_ADDRESS(s,d) ((((s) & 0xf) << 4) | ((d) & 0xf))


CEC_LogicalDevice::CEC_LogicalDevice(int physicalAddress)
: CEC_Electrical(CLA_UNREGISTERED)
, _physicalAddress(physicalAddress)
, _logicalAddress(CLA_UNREGISTERED)
, _done(false)
, _waitTime(0)
, _primaryState(CEC_ALLOCATE_LOGICAL_ADDRESS)
, _deviceType(CDT_OTHER)
,_queuedToSend(0)
,_waitingTransmit(0)
{
	_secondaryState = CEC_XMIT_POLLING_MESSAGE;
	_tertiaryState = 0;
}

void CEC_LogicalDevice::Initialize(CEC_DEVICE_TYPE type)
{
	CEC_Electrical::Initialize();
	_deviceType = type;

        if (MonitorMode)
        {
            _primaryState = CEC_READY;
        } else if (_physicalAddress == 0) {//we are a TV!
            _logicalAddress = 0;
            SetAddress(_logicalAddress);
            _primaryState = CEC_READY;
            DbgPrint("Logical address assigned: %d\r\n", _logicalAddress);
            DbgPrint("Physical addresss used: %d\r\n", _physicalAddress);
        }
}
void set_led(byte led, bool on);
bool CEC_LogicalDevice::ProcessStateMachine(bool* success)
{
	unsigned char buffer[1];
	bool wait = false;

	switch (_primaryState)
	{
	case CEC_ALLOCATE_LOGICAL_ADDRESS:
		switch (_secondaryState)
		{
		case CEC_XMIT_POLLING_MESSAGE:
			// Section 6.1.3 specifies that <Polling Message> while allocating a Logical Address
			// will have the same initiator and destination address
			buffer[0] = MAKE_ADDRESS(_validLogicalAddresses[_deviceType][_tertiaryState], _validLogicalAddresses[_deviceType][_tertiaryState]);
			ClearTransmitBuffer();
			Transmit(buffer, 1);

			_secondaryState = CEC_RCV_POLLING_MESSAGE;
			wait = true;
			break;

		case CEC_RCV_POLLING_MESSAGE:
			if (success)
			{
				if (*success)
				{
					// Someone is there, try the next
					_tertiaryState++;
					if (_validLogicalAddresses[_deviceType][_tertiaryState] != CLA_UNREGISTERED)
						_secondaryState = CEC_XMIT_POLLING_MESSAGE;
					else
					{
						_logicalAddress = CLA_UNREGISTERED;
						DbgPrint("Logical address assigned: %d\r\n", _logicalAddress);
                        DbgPrint("Physical addresss used: %d\r\n", _physicalAddress);
						_primaryState = CEC_READY;
					}
				}
				else
				{
					// We hereby claim this as our logical address!
					_logicalAddress = _validLogicalAddresses[_deviceType][_tertiaryState];
                    SetAddress(_logicalAddress);
					DbgPrint("Logical address assigned: %d\n", _logicalAddress);
                    DbgPrint("Physical addresss used: %d\r\n", _physicalAddress);
					_primaryState = CEC_READY;
                    set_led(2, true);
				}
			}
			else
				wait = true;
			break;
		}
		break;

	case CEC_READY:
		_primaryState = CEC_IDLE;
		OnReady();
		wait = true;
		break;

	case CEC_IDLE:
		wait = true;
		break;
	}

	return wait;
}

void CEC_LogicalDevice::OnReceiveComplete(unsigned char* buffer, int count)
{
	ASSERT(count >= 1);
	int sourceAddress = (buffer[0] >> 4) & 0x0f;
	int targetAddress = buffer[0] & 0x0f;
	OnReceive(sourceAddress, targetAddress, buffer + 1, count - 1);
}

bool CEC_LogicalDevice::TransmitFrame(int targetAddress, unsigned char* buffer, int count)
{
	if (_primaryState != CEC_IDLE)
		return false;

	unsigned char addr[1];

	addr[0] = MAKE_ADDRESS(_logicalAddress, targetAddress);
        ClearTransmitBuffer();
	if (!TransmitPartial(addr, 1))
		return false;
	return Transmit(buffer, count);
}

bool CEC_LogicalDevice::TransmitWait(int targetAddress, unsigned char* buffer, int count)
{
	while (_waitingTransmit){
		Run();
	}
	_waitingTransmit = true;
	_transmitResult = false;
	if (!TransmitFrame(targetAddress, buffer, count))
	{
		_waitingTransmit = false;
		return false;
	}
	while (_waitingTransmit){
		Run();
	}
	return _transmitResult;
}

bool CEC_LogicalDevice::TransmitMsg(int targetAddress, unsigned char message)
{
	unsigned char buffer[] = { message, };
	return TransmitWait(targetAddress, buffer, 1);
}
bool CEC_LogicalDevice::TransmitMsg(int targetAddress, unsigned char message, unsigned char param1)
{
	unsigned char buffer[] = { message, param1};
	return TransmitWait(targetAddress, buffer, 2);
}
bool CEC_LogicalDevice::TransmitMsg(int targetAddress, unsigned char message, unsigned char param1, unsigned char param2)
{
	unsigned char buffer[] = { message, param1, param2};
	return TransmitWait(targetAddress, buffer, 3);
}
bool CEC_LogicalDevice::TransmitMsg(int targetAddress, unsigned char message, unsigned char param1, unsigned char param2, unsigned char param3)
{
	unsigned char buffer[] = { message, param1, param2, param3};
	return TransmitWait(targetAddress, buffer, 4);
}
bool CEC_LogicalDevice::TransmitMsg(int targetAddress, unsigned char message, unsigned char param1, unsigned char param2, unsigned char param3, unsigned char param4)
{
	unsigned char buffer[] = { message, param1, param2, param3, param4};
	return TransmitWait(targetAddress, buffer, 5);
}

bool CEC_LogicalDevice::TransmitMsgQ(int targetAddress, unsigned char message)
{
	if (_queuedToSend == SEND_QUEUE_SIZE)
        return false;
	_sendQueueDest[_queuedToSend] = targetAddress;
	_sendQueue[_queuedToSend] = new unsigned char[1];
    _sendQueue[_queuedToSend][0] = message;
    _sendQueueCount[_queuedToSend] = 1;
    _queuedToSend++;
	return true;
}

bool CEC_LogicalDevice::TransmitMsgQ(int targetAddress, unsigned char message, unsigned char param1)
{
	if (_queuedToSend == SEND_QUEUE_SIZE)
        return false;
	_sendQueueDest[_queuedToSend] = targetAddress;
	_sendQueue[_queuedToSend] = new unsigned char[1];
    _sendQueue[_queuedToSend][0] = message;
    _sendQueue[_queuedToSend][1] = param1;
    _sendQueueCount[_queuedToSend] = 2;
    _queuedToSend++;
	return true;
}

bool CEC_LogicalDevice::TransmitMsgQ(int targetAddress, unsigned char message, unsigned char param1, unsigned char param2)
{
	if (_queuedToSend == SEND_QUEUE_SIZE)
        return false;
	_sendQueueDest[_queuedToSend] = targetAddress;
	_sendQueue[_queuedToSend] = new unsigned char[2];
    _sendQueue[_queuedToSend][0] = message;
    _sendQueue[_queuedToSend][1] = param1;
    _sendQueue[_queuedToSend][2] = param2;
    _sendQueueCount[_queuedToSend] = 3;
    _queuedToSend++;
	return true;
}

bool CEC_LogicalDevice::TransmitMsgQ(int targetAddress, unsigned char message, unsigned char param1, unsigned char param2, unsigned char param3)
{
	if (_queuedToSend == SEND_QUEUE_SIZE)
        return false;
	_sendQueueDest[_queuedToSend] = targetAddress;
	_sendQueue[_queuedToSend] = new unsigned char[3];
    _sendQueue[_queuedToSend][0] = message;
    _sendQueue[_queuedToSend][1] = param1;
    _sendQueue[_queuedToSend][2] = param2;
    _sendQueue[_queuedToSend][3] = param3;
    _sendQueueCount[_queuedToSend] = 4;
    _queuedToSend++;
	return true;
}

bool CEC_LogicalDevice::TransmitMsgQ(int targetAddress, unsigned char message, unsigned char param1, unsigned char param2, unsigned char param3, unsigned char param4)
{
	if (_queuedToSend == SEND_QUEUE_SIZE)
        return false;
	_sendQueueDest[_queuedToSend] = targetAddress;
	_sendQueue[_queuedToSend] = new unsigned char[4];
    _sendQueue[_queuedToSend][0] = message;
    _sendQueue[_queuedToSend][1] = param1;
    _sendQueue[_queuedToSend][2] = param2;
    _sendQueue[_queuedToSend][3] = param3;
    _sendQueue[_queuedToSend][4] = param4;
    _sendQueueCount[_queuedToSend] = 5;
    _queuedToSend++;
	return true;
}


void CEC_LogicalDevice::OnTransmitComplete(bool success)
{
	if (_primaryState == CEC_ALLOCATE_LOGICAL_ADDRESS &&
		_secondaryState == CEC_RCV_POLLING_MESSAGE &&
		_logicalAddress == CLA_UNREGISTERED)
	{
		while (!ProcessStateMachine(&success))
			;
	}
        else {
          //DbgPrint("Transmit: %d\r\n", success);
          _waitingTransmit = false;
		  _transmitResult = success;
        }
}

void CEC_LogicalDevice::SendQueued()
{
    if (_queuedToSend){
        //DbgPrint("sending queued (%d)\r\n", _queuedToSend);
        for (int i = 0; i < _queuedToSend; i++){
            //DbgPrint("sending queued msg (%d)\r\n", _sendQueue[i][0]);
            TransmitWait(_sendQueueDest[i], _sendQueue[i], _sendQueueCount[i]);
            _sendQueueDest[i] = 0;
            delete _sendQueue[i]; _sendQueue[i] = 0;
            _sendQueueCount[i] = 0;
        }
        _queuedToSend = 0;
	}
}

void CEC_LogicalDevice::Run()
{
	// Initial pump for the state machine (this will cause a transmit to occur)
	while (!ProcessStateMachine(NULL))
		;

	if (((_waitTime == (unsigned long)-1 && !TransmitPending()) || (_waitTime != (unsigned long)-1 && _waitTime > micros())) && !IsISRTriggered())
		return;

        unsigned long wait = Process();
        if (wait != (unsigned long)-2)
	        _waitTime = wait;

	return;
}

unsigned char CEC_LogicalDevice::getLogical(){
  return _logicalAddress;
}

int CEC_LogicalDevice::getPhysical(){
  return _physicalAddress;
}


