#ifndef CEC_TV_H_INCLUDED
#define CEC_TV_H_INCLUDED

#include <stdarg.h>
#include <Arduino.h>
#include <HardwareSerial.h>
//#include "CEC_Codes.h"
#include "cec_helpers.h"
#include "Message_defines.h"
#include "Common.h"
#include <IRremote.h>

//#define RECV_PIN 21

//atmega 328
#define RECV_PIN 12

// IRTX is 9 on mega with timer2

#define DEFAULT_INPUT_ADDR 0x1100

typedef struct logical_device_info {
char* osd_name;
cec_power_status power_status;
cec_physical_address phy_addr;
cec_version cec_ver;
cec_vendor_id vendor_id;
} logical_device_info;

typedef enum {
		CDT_TV,
		CDT_RECORDING_DEVICE,
		CDT_PLAYBACK_DEVICE,
		CDT_TUNER,
		CDT_AUDIO_SYSTEM,
		CDT_OTHER,				// Not a real CEC type..
	} CEC_DEVICE_TYPE;

class CEC_TV
{
public:
  CEC_TV(HardwareSerial* serialinterface):
  _sendUCTo(0)
  , _turnedOnAt(0)
  , irrecv(RECV_PIN)
  , _lastRemoteInputTime(0)
  , _lastRemoteInputCode(0)
  , _logicalAddress(0)
  , active_src1(0)
  , active_src2(0)
  {
      CECSerial = serialinterface;
      _powerStatus = testTVVoltage();
      irrecv.enableIRIn(); // Start the receiver
  };
  virtual ~CEC_TV(){};
  void Initialize()
  {
      CECSerial->write(MESSAGE_ENABLE_SEND);
      CECSerial->write(0);//phy1
      CECSerial->write(0);//phy2
      CECSerial->write(CDT_TV);
      int retval = CECBlockRead();
      DbgPrint("initialised %d\r\n", retval);
      for (int i = 0; i < 0xF; i++){
        devices[i].osd_name = 0;
        devices[i].power_status = CEC_POWER_STATUS_UNKNOWN;
        devices[i].phy_addr = 0;
        devices[i].cec_ver = CEC_VERSION_UNKNOWN;
        devices[i].vendor_id = CEC_VENDOR_UNKNOWN;
      }
  };
  void checkStartupTimeout();
  void powerOff();
  void powerToggle();
  void loop();
  void sendUC(cec_user_control_code UCCode);

    bool TransmitMsg(int targetAddress, int count, ...)
    {
        va_list ap;
        va_start(ap, count);
        CECSerial->write(MESSAGE_SEND_WITH_RESULT);
        CECSerial->write(count+1);
        CECSerial->write(targetAddress);
        //DbgPrint("%d, %d, %X, ", MESSAGE_SEND_WITH_RESULT, count+1, targetAddress);
        for (int i = 0; i < count; i++){
            unsigned char arg = va_arg(ap, unsigned int);
            CECSerial->write(arg);
            //Serial.print(arg,HEX); Serial.print(" ");
        }
        va_end(ap);
        //Serial.println(".");
        return CECBlockRead();
    };

    int CECAvailable() { return CECSerial->available(); };
    int CECBlockRead() { while (!CECAvailable()); return CECSerial->read(); };

    bool RequestAudio(cec_physical_address addr) { return TransmitMsg(5, 3, CEC_OPCODE_SYSTEM_AUDIO_MODE_REQUEST, split_2_byte(addr)); };
    bool RequestAudioOff() { return TransmitMsg(5, 1, CEC_OPCODE_SYSTEM_AUDIO_MODE_REQUEST); };
    bool SendRemoteCode(cec_logical_address dest, cec_user_control_code code) { return TransmitMsg(dest, 2, CEC_OPCODE_USER_CONTROL_PRESSED, code) && TransmitMsg(dest, 1, CEC_OPCODE_USER_CONTROL_RELEASE); };
    bool RequestPhyAddr(cec_logical_address dest) { return TransmitMsg(dest, 1, CEC_OPCODE_GIVE_PHYSICAL_ADDRESS); };
    bool RequestPwrStatus(cec_logical_address dest) { return TransmitMsg(dest, 1, CEC_OPCODE_GIVE_DEVICE_POWER_STATUS); };
    bool RequestPath(cec_physical_address addr) { return TransmitMsg(CECDEVICE_BROADCAST, 3, CEC_OPCODE_SET_STREAM_PATH, split_2_byte(addr)); };
    bool RequestActive() { return TransmitMsg(CECDEVICE_BROADCAST, 1, CEC_OPCODE_REQUEST_ACTIVE_SOURCE); };

protected:
    logical_device_info devices[0xE];

    virtual void OnReceive(int source, int dest, unsigned char* buffer, int count);

    byte _powerStatus;
    unsigned long _turnedOnAt;
    unsigned char _sendUCTo;
    void powerOn();

    byte testTVVoltage(){return CEC_POWER_STATUS_STANDBY;}

    IRsend irsend;
    IRrecv irrecv;

    short _logicalAddress;

    unsigned long _lastRemoteInputTime;
    unsigned long _lastRemoteInputCode;

    byte active_src1;
    byte active_src2;

    HardwareSerial* CECSerial;

};

class CEC_LogicalDeviceState
{
public:
    byte powerStatus;
    short physicalAddress;
    byte menuStatus;

};

void changeKoganInput(IRsend* irsend, short hdmiInput);
void sendKoganCode(IRsend* irsend, int code);

#endif // CEC_TV_H_INCLUDED
