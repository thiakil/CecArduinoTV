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
    unsigned char buffer[3];

    detachInterrupt(0);

    switch (c)
    {
      case '1':
        buffer[0] = CEC_STANDBY;
        device.TransmitFrame(4, buffer, 1);
        break;
      case '2':
        buffer[0] = CEC_INFO_REQ_PHYS_ADDR;
        device.TransmitFrame(4, buffer, 1);
        break;
      case '3':
        buffer[0] = CEC_POWER_REQ_STATUS;
        device.TransmitFrame(4, buffer, 1);
        break;
      case 'u':
        buffer[0] = CEC_AUDIO_MODE_REQ;
        buffer[1] = 0x11;
        buffer[2] = 0;
        device.TransmitFrame(5, buffer, 3);
        break;
      case 'i':
        buffer[0] = CEC_MENU_UC_PRESSED;
        buffer[1] = 0x41;
        device.TransmitFrame(5, buffer, 2);
        break;
      case 'o':
        buffer[0] = CEC_MENU_UC_RELEASED;
        device.TransmitFrame(5, buffer, 1);
        break;
      case 'p':
        buffer[0]=CEC_ROUTING_REQ_PATH;
        buffer[1]=0x20;
        buffer[2]=0;
        device.TransmitFrame(0xf, buffer, 3);
        break;
      case 'a':
        buffer[0]=CEC_ROUTING_REQ_ACTIVE;
        device.TransmitFrame(0xf, buffer, 1);
        break;
      case 't':
        buffer[0] = 0;
        DbgPrint("ping: %d", device.TransmitFrame(0x4, buffer, 0));
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
