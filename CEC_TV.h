#include <Arduino.h>
#include "CEC_Device.h"
#include "CEC_Codes.h"

class CEC_TV : public CEC_Device
{
public:
  CEC_TV():CEC_Device(0), _sendUCTo(0){
      Promiscuous = true; //Relay all line traffic
      _powerStatus = testTVVoltage();
  };
  virtual ~CEC_TV(){};

protected:
    virtual void OnReceive(int source, int dest, unsigned char* buffer, int count);

    byte _powerStatus;
    unsigned char _sendUCTo;
    void powerOn();
    void powerOff(){return;}
    byte testTVVoltage(){return CEC_POWER_STATUS_STANDBY;}
};

class CEC_LogicalDeviceState
{
public:
    byte powerStatus;
    short physicalAddress;
    byte menuStatus;

};
