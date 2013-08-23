#include "CEC_Device.h"
#include "CEC_Codes.h"
#include "CEC_TV.h"
//#include "cli.h"
#include <Wire.h>
#include "edid.h"
#include "MemoryFree.h"

#define IN_LINE 2
#define OUT_LINE 3
//#define HOTPLUG 4
#define LED1 13
/*#define LED2 5
#define LED3 6
#define LED4 7
#define LED5 8
#define LED6 9*/

//extern CEC_Device device(0x3000);
//CEC_Device device = NULL;
CEC_TV device;

void inputinterrupt(){
    device.Run();
}

void set_led(byte led, bool on){
  int pin = LED1;
  switch(led){
    case 1:
      pin = LED1;
      break;
    /*case 2:
      pin = LED2;
      break;
    case 3:
      pin = LED3;
      break;
    case 4:
      pin = LED4;
      break;
    case 5:
      pin = LED5;
      break;
    case 6:
      pin = LED6;
      break;*/
    default:
      return;
  }
  digitalWrite(pin, on ? HIGH : LOW);
  }

bool XX_GetLineState()
{
  int state = digitalRead(IN_LINE);
  return state == LOW;
}

void XX_SetLineState(CEC_Device* device, bool state)
{
  digitalWrite(OUT_LINE, state?LOW:HIGH);
  // give enough time for the line to settle before sampling
  // it
  delayMicroseconds(50);
  device->_lastLineState2 = XX_GetLineState();
}

void setup()
{
  Wire.begin();
  pinMode(OUT_LINE, OUTPUT);
  pinMode(IN_LINE, INPUT);

  pinMode(LED1, OUTPUT);
  /*pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);*/
  digitalWrite(LED1, LOW);
  /*digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, LOW);
  digitalWrite(LED6, LOW);*/


  digitalWrite(OUT_LINE, LOW);
  delay(1000);
  Serial.begin(115200);

  //device.MonitorMode = true;
  //int id = readEDID();
  //device = CEC_Device(0x0000);
  device = CEC_TV();

  //device.Promiscuous = true; //Relay all line traffic
  //device.Initialize(CEC_LogicalDevice::CDT_TV);
  //send_addr(device.getPhysical(), device.getLogical());
  //send_mem_status();
  digitalWrite(LED1, HIGH);
  Serial.println("ready");

  /*unsigned char buffer[4];

    buffer[0] = CEC_ROUTING_CHANGED;
    buffer[1] = 0x00;
    buffer[2] = 0;
    buffer[3] = 0x20;
    buffer[4] = 0;
    device.TransmitFrame(15, buffer, 5);
    Serial.println("transmitted");*/


  attachInterrupt(0, inputinterrupt,CHANGE);

}

void loop()
{
  if (Serial.available())
  {

    unsigned char c = Serial.read();

    detachInterrupt(0);

    switch (c)
    {
      case '1':
        device.TransmitMsg(4, CEC_STANDBY);
        break;
      case '2':
        device.TransmitMsg(4, CEC_INFO_REQ_PHYS_ADDR);
        break;
      case '3':
        device.TransmitMsg(4, CEC_POWER_REQ_STATUS);
        break;
      case 'r':
        device.TransmitMsg(5, CEC_AUDIO_MODE_REQ, 0x11, 0x00);
        break;
      case 'u':
        device.TransmitMsg(5, CEC_MENU_UC_PRESSED, 0x41);
        device.TransmitMsg(5, CEC_MENU_UC_RELEASED);
        break;
      case 'p':
        device.TransmitMsg(0xf, CEC_ROUTING_REQ_PATH, 0x20, 0x00);
        break;
      case 'a':
        device.TransmitMsg(0xf, CEC_ROUTING_REQ_ACTIVE);
        break;
      case 't':
        unsigned char buffer[] = {0};
        DbgPrint("ping: %d", device.TransmitWait(0x4, buffer, 0));
        break;
      case 'e':
        DbgPrint("read edid: %d", readEDID());
        break;
    }
  }
  detachInterrupt(0);
  device.Run();
  attachInterrupt(0, inputinterrupt,CHANGE);
}
