#include "CEC_Device.h"
#include "CEC_Codes.h"
//#include "cli.h"
#include <Wire.h>
#include "edid.h"
#include "MemoryFree.h"
#include "packetserial.h"
#include "status.h"
#include "cmdcodes.h"
#define IN_LINE 2
#define OUT_LINE 3
//#define HOTPLUG 4
#define LED1 13
/*#define LED2 5
#define LED3 6
#define LED4 7
#define LED5 8
#define LED6 9*/

//21 bytes
//ptype
//length
//src
//dest
//byte[15]

class CEC_TV : public CEC_Device
{
public:
  CEC_TV():CEC_Device(0){};
  virtual ~CEC_TV(){};

protected:
    virtual void OnReceive(int source, int dest, unsigned char* buffer, int count){
        DbgPrint("%d -> %d (%d): ", source, dest, count);
        if (count){
            switch(buffer[0]){
                case CEC_FEATURE_ABORT: DbgPrint("CEC_FEATURE_ABORT\r\n"); break;
                case CEC_OTP_IMAGE_ON: DbgPrint("CEC_OTP_IMAGE_ON\r\n"); break;
                //case CEC_TUNER_UP: DbgPrint("CEC_TUNER_UP\r\n"); break;
                //case CEC_TUNER_DOWN: DbgPrint("CEC_TUNER_DOWN\r\n"); break;
//                case CEC_TUNER_STATUS: DbgPrint("CEC_TUNER_STATUS\r\n"); break;
//                case CEC_TUNER_STATUS_REQ: DbgPrint("CEC_TUNER_STATUS_REQ\r\n"); break;
//                case CEC_OTR_REC_ON: DbgPrint("CEC_OTR_REC_ON\r\n"); break;
//                case CEC_OTR_REC_STATUS: DbgPrint("CEC_OTR_REC_STATUS\r\n"); break;
//                case CEC_OTR_REC_OFF: DbgPrint("CEC_OTR_REC_OFF\r\n"); break;
                case CEC_OTP_TEXT_ON: DbgPrint("CEC_OTP_TEXT_ON\r\n"); break;
                case CEC_OTR_REC_SCREEN: DbgPrint("CEC_OTR_REC_SCREEN\r\n"); break;
//                case CEC_DECK_REQ_STATUS: DbgPrint("CEC_DECK_REQ_STATUS\r\n"); break;
//                case CEC_DECK_STATUS: DbgPrint("CEC_DECK_STATUS\r\n"); break;
//                case CEC_INFO_LANG: DbgPrint("CEC_INFO_LANG\r\n"); break;
//                case CEC_TIMER_CLEAR_ANALOG: DbgPrint("CEC_TIMER_CLEAR_ANALOG\r\n"); break;
//                case CEC_TIMER_SET_ANALOG: DbgPrint("CEC_TIMER_SET_ANALOG\r\n"); break;
//                case CEC_TIMER_STATUS: DbgPrint("CEC_TIMER_STATUS\r\n"); break;
                case CEC_STANDBY: DbgPrint("CEC_STANDBY\r\n"); break;
                case CEC_DECK_PLAY: DbgPrint("CEC_DECK_PLAY\r\n"); break;
                case CEC_DECK_CTRL: DbgPrint("CEC_DECK_CTRL\r\n"); break;
//                case CEC_TIMER_STATUS_CLEARED: DbgPrint("CEC_TIMER_STATUS_CLEARED\r\n"); break;
//                case CEC_MENU_UC_PRESSED: DbgPrint("CEC_MENU_UC_PRESSED\r\n"); break;
                case CEC_OSD_REQ_OSD: DbgPrint("CEC_OSD_REQ_OSD\r\n"); break;
                case CEC_OSD_SET_OSD: DbgPrint("CEC_OSD_SET_OSD\r\n"); break;
                case CEC_OSD_SEND: DbgPrint("CEC_OSD_SEND\r\n"); break;
//                case CEC_TIMER_SET_TITLE: DbgPrint("CEC_TIMER_SET_TITLE\r\n"); break;
//                case CEC_AUDIO_MODE_REQ: DbgPrint("CEC_AUDIO_MODE_REQ\r\n"); break;
//                case CEC_AUDIO_STATUS_REQ: DbgPrint("CEC_AUDIO_STATUS_REQ\r\n"); break;
//                case CEC_AUDIO_MODE_SET: DbgPrint("CEC_AUDIO_MODE_SET\r\n"); break;
//                case CEC_AUDIO_STATUS: DbgPrint("CEC_AUDIO_STATUS\r\n"); break;
//                case CEC_Give_System_Audio_Mode_Status: DbgPrint("CEC_Give_System_Audio_Mode_Status\r\n"); break;
//                case CEC_AUDIO_MODE: DbgPrint("CEC_AUDIO_MODE\r\n"); break;
                case CEC_ROUTING_CHANGED: DbgPrint("CEC_ROUTING_CHANGED\r\n"); break;
                case CEC_ROUTING_INFO: DbgPrint("CEC_ROUTING_INFO\r\n"); break;
                case CEC_OTP_ACTIVE_SRC: DbgPrint("CEC_OTP_ACTIVE_SRC\r\n"); break;
                case CEC_INFO_REQ_PHYS_ADDR: DbgPrint("CEC_INFO_REQ_PHYS_ADDR\r\n"); break;
                case CEC_INFO_PHYS_ADDR: DbgPrint("CEC_INFO_PHYS_ADDR\r\n"); break;
                case CEC_ROUTING_REQ_ACTIVE: DbgPrint("CEC_ROUTING_REQ_ACTIVE\r\n"); break;
                case CEC_ROUTING_REQ_PATH: DbgPrint("CEC_ROUTING_REQ_PATH\r\n"); break;
                case CEC_VENDOR_ID: DbgPrint("CEC_VENDOR_ID\r\n"); break;
                case CEC_VENDOR_COMMAND: DbgPrint("CEC_VENDOR_COMMAND\r\n"); break;
                case CEC_VENDOR_REMOTE_BDOWN: DbgPrint("CEC_VENDOR_REMOTE_BDOWN\r\n"); break;
                case CEC_VENDOR_REMOTE_BUP: DbgPrint("CEC_VENDOR_REMOTE_BUP\r\n"); break;
                case CEC_VENDOR_ID_REQ: DbgPrint("CEC_VENDOR_ID_REQ\r\n"); break;
                case CEC_MENU_REQ: DbgPrint("CEC_MENU_REQ\r\n"); break;
                case CEC_MENU_STATUS: DbgPrint("CEC_MENU_STATUS\r\n"); break;
                case CEC_POWER_REQ_STATUS: DbgPrint("CEC_POWER_REQ_STATUS\r\n"); break;
                case CEC_POWER_STATUS: DbgPrint("CEC_POWER_STATUS\r\n"); break;
                case CEC_INFO_LANG_REQ: DbgPrint("CEC_INFO_LANG_REQ\r\n"); break;
//                case CEC_TUNER_SELECT_ANALOG: DbgPrint("CEC_TUNER_SELECT_ANALOG\r\n"); break;
//                case CEC_TUNER_SELECT_DIGITAL: DbgPrint("CEC_TUNER_SELECT_DIGITAL\r\n"); break;
//                case CEC_TIMER_SET_DIGITAL: DbgPrint("CEC_TIMER_SET_DIGITAL\r\n"); break;
//                case CEC_TIMER_CLEAR_DIGITAL: DbgPrint("CEC_TIMER_CLEAR_DIGITAL\r\n"); break;
//                case CEC_AUDIO_RATE: DbgPrint("CEC_AUDIO_RATE\r\n"); break;
                case CEC_ROUTING_INACTIVE: DbgPrint("CEC_ROUTING_INACTIVE\r\n"); break;
                case CEC_INFO_VERSION: DbgPrint("CEC_INFO_VERSION\r\n"); break;
                //case CEC_VENDOR_CEC_VERSION: DbgPrint("CEC_VENDOR_CEC_VERSION\r\n"); break;
                case CEC_INFO_VERSION_REQ: DbgPrint("CEC_INFO_VERSION_REQ\r\n"); break;
                //case CEC_VENDOR_CEC_VERSION_REQ: DbgPrint("CEC_VENDOR_CEC_VERSION_REQ\r\n"); break;
                case CEC_VENDOR_COMMAND_ID: DbgPrint("CEC_VENDOR_COMMAND_ID\r\n"); break;
                case CEC_TIMER_CLEAR_EXTERNAL: DbgPrint("CEC_TIMER_CLEAR_EXTERNAL\r\n"); break;
                case CEC_TIMER_SET_EXTERNAL: DbgPrint("CEC_TIMER_SET_EXTERNAL\r\n"); break;
                default: DbgPrint("unknown (%d)\r\n", buffer[0]); break;
            }
            if (count > 1) {
                for (int i = 1; i < count; i++)
                DbgPrint("%02X ", buffer[i]);
                DbgPrint("\r\n");
            }
        }
    };
};

//checksum

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

void handle_packet(byte* payload, byte length){
  //send_mem_status();
  if (payload[0] == REQ_ADD){
    send_addr(device.getPhysical(), device.getLogical());
  }
  if (payload[0] == SEND_PACKET){
    //read target addr from packet
    device.TransmitFrame(payload[2], &payload[3], length -3);
  }
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

  device.Promiscuous = true; //Relay all line traffic
  device.Initialize(CEC_LogicalDevice::CDT_TV);
  //send_addr(device.getPhysical(), device.getLogical());
  //send_mem_status();
  digitalWrite(LED1, HIGH);
  Serial.println("ready");

  unsigned char buffer[4];

    buffer[0] = CEC_ROUTING_CHANGED;
    buffer[1] = 0x00;
    buffer[2] = 0;
    buffer[3] = 0x20;
    buffer[4] = 0;
    device.TransmitFrame(15, buffer, 5);
    Serial.println("transmitted");


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
