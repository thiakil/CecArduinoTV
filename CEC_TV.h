#ifndef CEC_TV_H_INCLUDED
#define CEC_TV_H_INCLUDED

#include <Arduino.h>
#include "CEC_Device.h"
#include "CEC_Codes.h"
#include <IRremote.h>

#include "IRModule/IRModule_config.h"

//#define RECV_PIN 21

//atmega 328
#define RECV_PIN 12

#define DEFAULT_INPUT_ADDR 0x1000

typedef struct logical_device_info {
char* osd_name,
cec_power_status power_status,
cec_physical_address phy_addr,
cec_version cec_ver,
} logical_device_info;

class CEC_TV : public CEC_Device
{
public:
  CEC_TV()
  : CEC_Device(0)
  , _sendUCTo(0)
  , _turnedOnAt(0)
  , irrecv(RECV_PIN)
  , _lastRemoteInputTime(0)
  , _lastRemoteInputCode(0)
  , _activeSrcBroadcast(0)
  , _activeSrcBroadcastForStandby(false)
  {
      Promiscuous = true; //Relay all line traffic
      _powerStatus = testTVVoltage();
      irrecv.enableIRIn(); // Start the receiver
  };
  virtual ~CEC_TV(){};
  void checkStartupTimeout();
  void powerOff();
  void powerToggle();
  void loop();
  void sendUC(unsigned char UCCode);

protected:
    logical_device_info devices[0xE];
    bool RequestAudio(cec_physical_address addr) { return TrasmitMsg(5, 3, CEC_OPCODE_SYSTEM_AUDIO_MODE_REQUEST, split_2_byte(addr)); };
    bool RequestAudioOff() { return TrasmitMsg(5, 1, CEC_OPCODE_SYSTEM_AUDIO_MODE_REQUEST); };
    bool SendRemoteCode(cec_logical_address dest, cec_user_control_code code) { return TransmitMsg(dest, 2, CEC_OPCODE_USER_CONTROL_PRESSED, code) && TransmitMsg(dest, 1, CEC_OPCODE_USER_CONTROL_RELEASE); };
    bool RequestPhyAddr(cec_logical_address dest) { return TransmitMsg(dest, 1, CEC_INFO_REQ_PHYS_ADDR); };
    bool RequestPwrStatus(cec_logical_address dest) { return TransmitMsg(dest, 1, CEC_POWER_REQ_STATUS); };
    bool RequestPath(cec_physical_address addr) { return TransmitMsg(CECDEVICE_BROADCAST, 3, CEC_ROUTING_REQ_PATH, split_2_byte(addr)); };
    bool RequestActive() { return TransmitMsg(CECDEVICE_BROADCAST, 1, CEC_ROUTING_REQ_ACTIVE); };

    virtual void OnReceive(int source, int dest, unsigned char* buffer, int count);

    byte _powerStatus;
    unsigned long _turnedOnAt;
    unsigned long _activeSrcBroadcast;
    bool _activeSrcBroadcastForStandby;//if true no response = turn off. if false, request stream path (default hdmi input if unknown input)
    unsigned char _sendUCTo;
    void powerOn();

    void broadcastForActiveSource(bool noResponseTurnOff = false);

    byte testTVVoltage(){return CEC_POWER_STATUS_STANDBY;}

    //IRsend irsend;
    IRrecv irrecv;

    unsigned long _lastRemoteInputTime;
    unsigned long _lastRemoteInputCode;
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
