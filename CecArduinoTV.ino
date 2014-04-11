#include "Common.h"
#include "CEC_Codes.h"
#include "CEC_TV.h"
//#include "cli.h"

#include <IRremote.h>
#include <RCSwitch.h>
//#include "edid.h"

#define IN_LINE 2
#define OUT_LINE 3
//#define HOTPLUG 4
#define LED1 11
/*#define LED2 5
#define LED3 6
#define LED4 7
#define LED5 8
#define LED6 9*/

//extern CEC_Device device(0x3000);
//CEC_Device device = NULL;
CEC_TV device = NULL;

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

RCSwitch subSwitch = RCSwitch();

void setup()
{
  Serial.begin(115200);
  Serial1.begin(115200);
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

  subSwitch.enableTransmit(10);


  //device.MonitorMode = true;
  //int id = readEDID();
  //device = CEC_Device(0x0000);
  device = CEC_TV(&Serial1);

  //device.Promiscuous = true; //Relay all line traffic
  device.Initialize();
  //send_addr(device.getPhysical(), device.getLogical());
  //send_mem_status();
  digitalWrite(LED1, HIGH);
  Serial.println("ready");

  //device.TransmitMsg(CEC_BROADCAST, CEC_INFO_PHYS_ADDR, 0, 0, 0);

  /*unsigned char buffer[4];

    buffer[0] = CEC_ROUTING_CHANGED;
    buffer[1] = 0x00;
    buffer[2] = 0;
    buffer[3] = 0x20;
    buffer[4] = 0;
    device.TransmitFrame(15, buffer, 5);
    Serial.println("transmitted");*/


  //attachInterrupt(0, inputinterrupt,CHANGE);

}

void loop()
{
  if (Serial.available())
  {

    unsigned char c = Serial.read();

    switch (c)
    {
      case '1':
        device.TransmitMsg(CEC_BROADCAST, 1, CEC_STANDBY);
        break;
      case '2':
        device.TransmitMsg(5, 1, CEC_INFO_REQ_PHYS_ADDR);
        break;
      case '3':
        device.TransmitMsg(5, 1, CEC_POWER_REQ_STATUS);
        break;
      /*case 'r':
        device.TransmitMsg(5, CEC_AUDIO_MODE_REQ, 0x11, 0x00);
        break;*/
      case 'u':
        device.TransmitMsg(5, 2, CEC_MENU_UC_PRESSED, CEC_UC_CODE_VOLUME_UP);
        device.TransmitMsg(5, 1, CEC_MENU_UC_RELEASED);
        break;
      case 'p':
        device.TransmitMsg(0xf, 3, CEC_ROUTING_REQ_PATH, 0x11, 0x00);
        break;
      case 'a':
        device.TransmitMsg(0xf, 1, CEC_ROUTING_REQ_ACTIVE);
        break;
      case 't':
          {
              //unsigned char buffer[] = {0};
              for (int addr = 1; addr< 0xf; addr++) {
                DbgPrint("ping(%d): %d\r\n", addr, device.TransmitMsg(addr, 0));
              }
              DbgPrint("end pings (%d)\r\n", millis());
              break;
          }
      /*case 'e':
        DbgPrint("read edid: %d", readEDID());
        break;*/
      case '8':
        device.TransmitMsg(4, 2, CEC_MENU_UC_PRESSED, CEC_UC_CODE_UP);
        device.TransmitMsg(4, 1, CEC_MENU_UC_RELEASED);
        break;
      case '4':
        device.TransmitMsg(4, 2, CEC_MENU_UC_PRESSED, CEC_UC_CODE_LEFT);
        device.TransmitMsg(4, 1, CEC_MENU_UC_RELEASED);
        break;
      case '6':
        device.TransmitMsg(4, 2, CEC_MENU_UC_PRESSED, CEC_UC_CODE_RIGHT);
        device.TransmitMsg(4, 1, CEC_MENU_UC_RELEASED);
        break;
      case '5':
        device.TransmitMsg(4, 2, CEC_MENU_UC_PRESSED, CEC_UC_CODE_DOWN);
        device.TransmitMsg(4, 1, CEC_MENU_UC_RELEASED);
        break;
      case 'n':
        device.TransmitMsg(4, 1, CEC_OSD_REQ_OSD);
        break;
      case 'i':
        device.TransmitMsg(4, 1, CEC_VENDOR_ID_REQ);
        break;
      case 'o':
        device.powerToggle();
        break;
      case 'm':
        device.TransmitMsg(5, 3, CEC_AUDIO_MODE_REQ, 0x14, 0);
        break;
      case 'c':
        device.TransmitMsg(5, 1, CEC_AUDIO_MODE_REQ);
        break;
    }
  }

  device.loop();
}
