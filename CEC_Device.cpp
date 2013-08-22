#include "CEC_Device.h"
#include "packetserial.h"
#include "cmdcodes.h"

bool XX_GetLineState();
void XX_SetLineState(CEC_Device* device, bool state);

CEC_Device::CEC_Device(int physicalAddress)
: CEC_LogicalDevice(physicalAddress)
, _isrTriggered(false)
, _lastLineState2(true)
{
}

CEC_Device::~CEC_Device()
{
}

void CEC_Device::OnReady()
{
  // This is called after the logical address has been
  // allocated
  //DbgPrint("Device ready\n");
  //packet_serial_send("Device Ready",12);
}

extern "C" unsigned long millis();
void CEC_Device::OnReceive(int source, int dest, unsigned char* buffer, int count)
{
  // This is called when a frame is received.  To transmit
  // a frame call TransmitFrame.  To receive all frames, even
  // those not addressed to this device, set Promiscuous to true.

  //process and transmit serial packet
  /*int newcount = count + 3;
  unsigned char newbuffer[newcount];
  newbuffer[0] = RECV_PACKET;
  newbuffer[1] = source;
  newbuffer[2] = dest;
  int i;
  for (i = newcount - count; i< newcount; i++){ //space three for the cmd, src and dest
    newbuffer[i] = buffer[i - (newcount - count)]; //-2 on old buffer index to account for above
  }*/

  //packet_serial_send(newbuffer, newcount);
  //byte* payload, byte length
  DbgPrint("Packet received at %ld: %d -> %d (%d)\r\n", millis(), source, dest, count);
  for (int i = 0; i < count; i++)
    DbgPrint("%02X ", buffer[i]);
  DbgPrint("\r\n");

}

bool CEC_Device::LineState()
{
  return XX_GetLineState();
}

void CEC_Device::SetLineState(bool state)
{
  XX_SetLineState(this, state);
}

void CEC_Device::SignalIRQ()
{
  // This is called when the line has changed state
  _isrTriggered = true;
}

bool CEC_Device::IsISRTriggered()
{
  if (_isrTriggered)
  {
    _isrTriggered = false;
    return true;
  }
  return false;
}

void CEC_Device::Run()
{
  bool state = XX_GetLineState();
  if (_lastLineState2 != state)
  {
    _lastLineState2 = state;
    SignalIRQ();
  }
  CEC_LogicalDevice::Run();
}

