class TV_Control
{
public:
  TV_Control(){}
  virtual ~TV_Control(){};
  
  virtual void powerOff();
  virtual void powerToggle();
  
  virtual void loop();

  virtual void powerOn();

  virtual byte getTvPowerStatus(){return CEC_POWER_STATUS_STANDBY;};
  virtual bool isTransitionedToOn();

  virtual void changeHdmiInput(int input);

protected:

    IRsend irsend;

};

class TV_ControlKogan : TV_Control
{
public:
  TV_ControlKogan();
  ~TV_ControlKogan();

protected:
  bool hotplugVoltagePresent();

};