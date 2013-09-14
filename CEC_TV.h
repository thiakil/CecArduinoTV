#ifndef CEC_TV_H_INCLUDED
#define CEC_TV_H_INCLUDED

#include <Arduino.h>
#include "CEC_Device.h"
#include "CEC_Codes.h"
#include <IRremote.h>

//#define RECV_PIN 21

//atmega 328
#define RECV_PIN 12

#define DEFAULT_INPUT_ADDR 0x1000

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
    virtual void OnReceive(int source, int dest, unsigned char* buffer, int count);

    byte _powerStatus;
    unsigned long _turnedOnAt;
    unsigned long _activeSrcBroadcast;
    bool _activeSrcBroadcastForStandby;//if true no response = turn off. if false, request stream path (default hdmi input if unknown input)
    unsigned char _sendUCTo;
    void powerOn();

    void broadcastForActiveSource(bool noResponseTurnOff = false);

    byte testTVVoltage(){return CEC_POWER_STATUS_STANDBY;}

    IRsend irsend;
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
