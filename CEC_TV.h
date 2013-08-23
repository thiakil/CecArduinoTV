#include "CEC_Device.h"
#include "CEC_Codes.h"

class CEC_TV : public CEC_Device
{
public:
  CEC_TV():CEC_Device(0){
      Promiscuous = true; //Relay all line traffic
      Initialize(CEC_LogicalDevice::CDT_TV);
  };
  virtual ~CEC_TV(){};

protected:
    virtual void OnReceive(int source, int dest, unsigned char* buffer, int count);

    byte powerStatus;
    void powerOn(){}
    void powerOff(){}
    bool testTVVoltage(){return false;}
};