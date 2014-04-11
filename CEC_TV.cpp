#define DEBUG_CODES
//#define DEBUG_IRCODES

#include "CEC_TV.h"
#include "Common.h"

#include <RCSwitch.h>
extern RCSwitch subSwitch;

#define SWITCH_CODE_0_ON 1656842
#define SWITCH_CODE_0_OFF 1656834

static const char* vendor_tostring(const cec_vendor_id vendor)
{
  switch (vendor)
  {
  case CEC_VENDOR_SAMSUNG:
    return "Samsung";
  case CEC_VENDOR_LG:
    return "LG";
  case CEC_VENDOR_PANASONIC:
    return "Panasonic";
  case CEC_VENDOR_PIONEER:
    return "Pioneer";
  case CEC_VENDOR_ONKYO:
    return "Onkyo";
  case CEC_VENDOR_YAMAHA:
    return "Yamaha";
  case CEC_VENDOR_PHILIPS:
    return "Philips";
  case CEC_VENDOR_SONY:
    return "Sony";
  case CEC_VENDOR_TOSHIBA:
  case CEC_VENDOR_TOSHIBA2:
    return "Toshiba";
  case CEC_VENDOR_AKAI:
    return "Akai";
  case CEC_VENDOR_AOC:
    return "AOC";
  case CEC_VENDOR_BENQ:
    return "Benq";
  case CEC_VENDOR_DAEWOO:
    return "Daewoo";
  case CEC_VENDOR_GRUNDIG:
    return "Grundig";
  case CEC_VENDOR_MEDION:
    return "Medion";
  case CEC_VENDOR_SHARP:
    return "Sharp";
  case CEC_VENDOR_VIZIO:
    return "Vizio";
  case CEC_VENDOR_BROADCOM:
    return "Broadcom";
  case CEC_VENDOR_LOEWE:
    return "Loewe";
  case CEC_VENDOR_DENON:
    return "Denon";
  case CEC_VENDOR_MARANTZ:
    return "Marantz";
  case CEC_VENDOR_HARMAN_KARDON:
    return "Harman/Kardon";
  case CEC_VENDOR_PULSE_EIGHT:
    return "Pulse Eight";
  default:
    return "Unknown";
  }
}

void debugReceivedMsg(int source, int dest, unsigned char* buffer, int count){
    DbgPrint("%d -> %d (%d): ", source, dest, count);
    if (count){
        #ifdef DEBUG_CODES
        switch(buffer[0]){
            case CEC_FEATURE_ABORT: Serial.print("FEATURE_ABORT"); break;
            case CEC_OTP_IMAGE_ON: Serial.print("IMAGE_ON"); break;
            //case CEC_TUNER_UP: DbgPrint("CEC_TUNER_UP"); break;
            //case CEC_TUNER_DOWN: DbgPrint("CEC_TUNER_DOWN"); break;
//                case CEC_TUNER_STATUS: DbgPrint("CEC_TUNER_STATUS"); break;
//                case CEC_TUNER_STATUS_REQ: DbgPrint("CEC_TUNER_STATUS_REQ"); break;
//                case CEC_OTR_REC_ON: DbgPrint("CEC_OTR_REC_ON"); break;
//                case CEC_OTR_REC_STATUS: DbgPrint("CEC_OTR_REC_STATUS"); break;
//                case CEC_OTR_REC_OFF: DbgPrint("CEC_OTR_REC_OFF"); break;
            case CEC_OTP_TEXT_ON: Serial.print("TEXT_ON"); break;
            case CEC_OTR_REC_SCREEN: Serial.print("REC_SCREEN"); break;
                /*case CEC_DECK_REQ_STATUS: DbgPrint("CEC_DECK_REQ_STATUS"); break;
                case CEC_DECK_STATUS: DbgPrint("CEC_DECK_STATUS"); break;*/
                case CEC_INFO_LANG: Serial.print("CEC_INFO_LANG"); break;
//                case CEC_TIMER_CLEAR_ANALOG: DbgPrint("CEC_TIMER_CLEAR_ANALOG"); break;
//                case CEC_TIMER_SET_ANALOG: DbgPrint("CEC_TIMER_SET_ANALOG"); break;
//                case CEC_TIMER_STATUS: DbgPrint("CEC_TIMER_STATUS"); break;
            case CEC_STANDBY: Serial.print("STANDBY"); break;
            //case CEC_DECK_PLAY: DbgPrint("CEC_DECK_PLAY"); break;
            //case CEC_DECK_CTRL: DbgPrint("CEC_DECK_CTRL"); break;
//                case CEC_TIMER_STATUS_CLEARED: DbgPrint("CEC_TIMER_STATUS_CLEARED"); break;
                case CEC_MENU_UC_PRESSED: Serial.print("CEC_MENU_UC_PRESSED"); break;
            case CEC_OSD_REQ_OSD: Serial.print("OSD_REQ_OSD"); break;
            case CEC_OSD_SET_OSD: Serial.print("OSD_SET_OSD"); break;
            case CEC_OSD_SEND: Serial.print("CEC_OSD_SEND"); break;
//                case CEC_TIMER_SET_TITLE: DbgPrint("CEC_TIMER_SET_TITLE"); break;
                case CEC_AUDIO_MODE_REQ: Serial.print("CEC_AUDIO_MODE_REQ"); break;
                case CEC_AUDIO_STATUS_REQ: Serial.print("CEC_AUDIO_STATUS_REQ"); break;
                case CEC_AUDIO_MODE_SET: Serial.print("CEC_AUDIO_MODE_SET"); break;
                case CEC_AUDIO_STATUS: Serial.print("CEC_AUDIO_STATUS"); break;
                case CEC_Give_System_Audio_Mode_Status: Serial.print("CEC_Give_System_Audio_Mode_Status"); break;
                case CEC_AUDIO_MODE: Serial.print("CEC_AUDIO_MODE"); break;
            case CEC_ROUTING_CHANGED: Serial.print("CEC_ROUTING_CHANGED"); break;
            case CEC_ROUTING_INFO: Serial.print("ROUTING_INFO"); break;
            case CEC_ROUTING_ACTIVE: Serial.print("ROUTING_ACTIVE"); break;
            case CEC_INFO_REQ_PHYS_ADDR: Serial.print("INFO_REQ_PHYS_ADDR"); break;
            case CEC_INFO_PHYS_ADDR: Serial.print("INFO_PHYS_ADDR"); break;
            case CEC_ROUTING_REQ_ACTIVE: Serial.print("ROUTING_REQ_ACTIVE"); break;
            case CEC_ROUTING_REQ_PATH: Serial.print("ROUTING_REQ_PATH"); break;
            case CEC_VENDOR_ID: Serial.print("VENDOR_ID"); break;
            //case CEC_VENDOR_COMMAND: DbgPrint("CEC_VENDOR_COMMAND"); break;
            //case CEC_VENDOR_REMOTE_BDOWN: DbgPrint("CEC_VENDOR_REMOTE_BDOWN"); break;
            //case CEC_VENDOR_REMOTE_BUP: DbgPrint("CEC_VENDOR_REMOTE_BUP"); break;
            //case CEC_VENDOR_ID_REQ: DbgPrint("CEC_VENDOR_ID_REQ"); break;
            case CEC_MENU_REQ: Serial.print("MENU_REQ"); break;
            case CEC_MENU_STATUS: Serial.print("MENU_STATUS"); break;
            case CEC_POWER_REQ_STATUS: Serial.print("POWER_REQ_STATUS"); break;
            case CEC_POWER_STATUS: Serial.print("POWER_STATUS"); break;
            //case CEC_INFO_LANG_REQ: DbgPrint("CEC_INFO_LANG_REQ"); break;
//                case CEC_TUNER_SELECT_ANALOG: DbgPrint("CEC_TUNER_SELECT_ANALOG"); break;
//                case CEC_TUNER_SELECT_DIGITAL: DbgPrint("CEC_TUNER_SELECT_DIGITAL"); break;
//                case CEC_TIMER_SET_DIGITAL: DbgPrint("CEC_TIMER_SET_DIGITAL"); break;
//                case CEC_TIMER_CLEAR_DIGITAL: DbgPrint("CEC_TIMER_CLEAR_DIGITAL"); break;
//                case CEC_AUDIO_RATE: DbgPrint("CEC_AUDIO_RATE"); break;
            case CEC_ROUTING_INACTIVE: Serial.print("ROUTING_INACTIVE"); break;
            case CEC_INFO_VERSION: Serial.print("INFO_VERSION"); break;
            //case CEC_VENDOR_CEC_VERSION: DbgPrint("CEC_VENDOR_CEC_VERSION"); break;
            //case CEC_INFO_VERSION_REQ: DbgPrint("CEC_INFO_VERSION_REQ"); break;
            //case CEC_VENDOR_CEC_VERSION_REQ: DbgPrint("CEC_VENDOR_CEC_VERSION_REQ"); break;
            //case CEC_VENDOR_COMMAND_ID: DbgPrint("CEC_VENDOR_COMMAND_ID"); break;
            //case CEC_TIMER_CLEAR_EXTERNAL: DbgPrint("CEC_TIMER_CLEAR_EXTERNAL"); break;
            //case CEC_TIMER_SET_EXTERNAL: DbgPrint("CEC_TIMER_SET_EXTERNAL"); break;
            default: DbgPrint("unknown (%d)", buffer[0]); break;
        }
        #endif//#DEBUG_CODES
        #ifndef DEBUG_CODES
            DbgPrint("%d", buffer[0]);
        #endif
        DbgPrint("\r\n");
        if (count > 1) {
            for (int i = 1; i < count; i++)
            DbgPrint("%02X ", buffer[i]);
            Serial.print("\r\n");
        }
    } else {
        Serial.print("Ping \r\n");
    }
}

void CEC_TV::OnReceive(int source, int dest, unsigned char* buffer, int count){
    //#ifdef DEBUG_CODES
        debugReceivedMsg(source, dest, buffer, count);
    //#endif //#DEBUG_CODES

    if (count /*&& (dest == _logicalAddress || dest == CEC_BROADCAST)*/){
        switch(buffer[0]){
            case CEC_OTP_IMAGE_ON:
            case CEC_OTP_TEXT_ON:
                powerOn();
                break;
            case CEC_STANDBY:
                powerOff();
                break;
            case CEC_INFO_VERSION_REQ:
                TransmitMsg(source, 2, CEC_INFO_VERSION, 0x04);//hdmi 1.3a
            case CEC_INFO_VERSION:
                break;
            case CEC_INFO_REQ_PHYS_ADDR:
                TransmitMsg(source, 4, CEC_INFO_PHYS_ADDR, 0, 0, CDT_TV);
                break;
            case CEC_POWER_REQ_STATUS:
                TransmitMsg(source, 2, CEC_POWER_STATUS, _powerStatus);
                break;
            case CEC_ROUTING_ACTIVE:
                /*if (_powerStatus == CEC_POWER_STATUS_ON)
                {
                    _activeSrcBroadcast = 0;
                    DbgPrint("changing to input %d\r\n", buffer[1]>>4 & 0xf);
                    //changeKoganInput(&irsend, buffer[1]>>4 & 0xf);
                    //irrecv.enableIRIn(); // Re-enable receiver
                    changeInputI2c(buffer[1]>>4 & 0xf);

                }*/
                active_src1 = buffer[1];
                active_src2 = buffer[2];
                DbgPrint("Got active src of %02X.%02X\n", active_src1, active_src2);
                DbgPrint("Asking for OSD: %d\n", TransmitMsg(source, 1,CEC_OSD_REQ_OSD));
                DbgPrint("Asking for audio mode: %d\n", TransmitMsg(5, 3, CEC_AUDIO_MODE_REQ, active_src1, active_src2));
                break;
            case CEC_ROUTING_INFO:
                active_src1 = buffer[3];
                active_src2 = buffer[4];
                TransmitMsg(5, 3, CEC_AUDIO_MODE_REQ, active_src1, active_src2);
            case CEC_ROUTING_INACTIVE:
                /*if (_powerStatus == CEC_POWER_STATUS_ON)
                    broadcastForActiveSource(true);//this probably shows up with nothing as other sources assume they're not active, but we check to be sure.
                    DbgPrint("TODO 139, cectv\r\n");*/
                break;
            case CEC_MENU_STATUS:
                if (buffer[1] == CEC_MENU_STATUS_ACTIVATED)
                    _sendUCTo = source;
                else
                    _sendUCTo = 0;
                break;
            case CEC_POWER_STATUS:
                #ifdef DEBUG_CODES
                    DbgPrint("device at logical %d is ", source);
                    switch (buffer[1]){
                        case CEC_POWER_STATUS_ON:
                            Serial.print("On");
                            break;
                        case CEC_POWER_STATUS_STANDBY:
                            Serial.print("on Standby");
                            break;
                        case CEC_POWER_STATUS_TRANSITION_STANDBY_TO_ON:
                            Serial.print("Turning On");
                            break;
                        case CEC_POWER_STATUS_TRANSITION_ON_TO_STANDBY:
                            Serial.print("Turning Off");
                            break;
                        default:
                            DbgPrint("UNKNOWN STATUS (%d)", buffer[1]);
                            break;
                    }
                    Serial.print("\r\n");
                #endif
                break;
            case CEC_INFO_PHYS_ADDR:
                DbgPrint("Device at logical %X is at %02X%02X device type %02X\r\n", source, buffer[1],buffer[2], buffer[3]);
                break;
            case CEC_OSD_SET_OSD:
                #ifdef DEBUG_CODES
                {
                    short osdLen = count -1;
                    if (osdLen){
                        char* osdName = new char[osdLen];
                        memcpy(osdName, buffer+1, osdLen);
                        osdName[osdLen] = 0;
                        DbgPrint("Device at logical %X is known as \"%s\"\r\n", source, osdName);
                        delete osdName;
                    }
                    break;
                }
                #endif
            case CEC_AUDIO_MODE_SET://this tells us that the receiver is on/off
                subSwitch.send(buffer[1] ? SWITCH_CODE_0_ON : SWITCH_CODE_0_OFF, 24);
                DbgPrint("AUdio mode set: %x\r\n", buffer[1]);
                break;
            case CEC_VENDOR_ID:
                {
                    long vendorid = (long)buffer[1] << 16 | (long)buffer[2] << 8 | buffer[3];
                    DbgPrint("Device at logical %X is a %s (%06lX)\n", source, vendor_tostring((cec_vendor_id)vendorid), vendorid);
                    break;
                }
            //no response messages:
            case CEC_FEATURE_ABORT:
            case CEC_AUDIO_STATUS://receiver giving volume status
                break;
            default:
                if (dest != CEC_BROADCAST){//dont wanna do for bcast
                    Serial.print("ABORT!\r\n");
                    TransmitMsg(source, 2, CEC_FEATURE_ABORT, CEC_ABORT_UNRECOGNIZED);
                }
                break;
        }
    }
}

#define KOGAN_POWER 0x20B
#define KOGAN_INPUT 0x21C
#define KOGAN_UP 0x22B
#define KOGAN_DOWN 0x22C
#define KOGAN_LEFT 0x22D
#define KOGAN_RIGHT 0x22E
#define KOGAN_DTV 0x232
#define KOGAN_MENU 0x215
#define KOGAN_ENTER 0x22F
#define KOGAN_ASPECT 0x231
#define KOGAN_EXIT 0x230
#define KOGAN_3D 0x233
//#define KOGAN_ 0x


#define REMOTE_PROTOCOL RC6
#define check_remote_protocol if (results.decode_type != REMOTE_PROTOCOL) break;

#define REMOTE_UP 0x2858
#define REMOTE_DOWN 0x2859
#define REMOTE_LEFT 0x285A
#define REMOTE_RIGHT 0x285B
#define REMOTE_ENTER 0x285C
#define REMOTE_POWER 0x280C
#define REMOTE_BACK 0x2883
#define REMOTE_MENU 0x2854
#define REMOTE_SKIP_BACK 0x286D
#define REMOTE_SKIP_FORWARD 0x2870
#define REMOTE_PAUSE 0x283C
#define REMOTE_PLAY 0x286F
//#define REMOTE_RED 0x286D
//#define REMOTE_GREEN 0x286E
//#define REMOTE_YELLOW 0x286F
//#define REMOTE_BLUE 0x2870
//#define REMOTE_AV 0x547AB8
#define REMOTE_1 0x2801
#define REMOTE_2 0x2802
#define REMOTE_3 0x2803
#define REMOTE_4 0x2804
#define REMOTE_5 0x2805
#define REMOTE_6 0x2806
#define REMOTE_7 0x2807
#define REMOTE_8 0x2808
#define REMOTE_9 0x2809
#define REMOTE_0 0x2800
#define REMOTE_RECORD 0x28FF
#define REMOTE_STOP 0x286E
#define REMOTE_GUIDE 0x28CC
//#define REMOTE_ 0x


#define KOGAN_DELAY 500
void sendKoganCode(IRsend* irsend, int code)
{
    irsend->sendKogan(code, 32);
    irsend->sendKogan(code, 32);
}

void CEC_TV::powerOn(){
    if (_powerStatus != CEC_POWER_STATUS_ON && _powerStatus != CEC_POWER_STATUS_TRANSITION_STANDBY_TO_ON) {
        _powerStatus = CEC_POWER_STATUS_TRANSITION_STANDBY_TO_ON;
        sendKoganCode(&irsend, KOGAN_POWER);
        _turnedOnAt = millis();
        irrecv.enableIRIn(); // Re-enable receiver
        //TransmitMsg(5, CEC_AUDIO_MODE_REQ, 0x10, 0x00);
    }
}

void CEC_TV::checkStartupTimeout()
{
    if (_turnedOnAt){
        if (millis() - _turnedOnAt >= 15000)//takes about 13s to start up
        {
            _turnedOnAt = 0;
            _powerStatus = CEC_POWER_STATUS_ON;
            Serial.print("TODO: proper power on check\r\n");
            TransmitMsg(CEC_BROADCAST, 3, CEC_ROUTING_INFO, 0x10, 0);
            if (active_src1)
                TransmitMsg(5, 3, CEC_AUDIO_MODE_REQ, active_src1, active_src2);
        }
    }
}

void CEC_TV::powerOff()
{
    while (_powerStatus == CEC_POWER_STATUS_TRANSITION_STANDBY_TO_ON)
        checkStartupTimeout();

    if(_powerStatus == CEC_POWER_STATUS_ON)
    {
        sendKoganCode(&irsend, KOGAN_POWER);
        _powerStatus = CEC_POWER_STATUS_STANDBY;
        TransmitMsg(5, 1, CEC_AUDIO_MODE_REQ);
        TransmitMsg(CEC_BROADCAST, 1, CEC_STANDBY);
        TransmitMsg(5, 1, CEC_AUDIO_MODE_REQ);
        Serial.print("TODO: proper power off check\r\n");
        irrecv.enableIRIn(); // Re-enable receiver
    }
}

void CEC_TV::powerToggle()
{
    if(_powerStatus == CEC_POWER_STATUS_ON)
        powerOff();
    else
        powerOn();
}

void CEC_TV::sendUC(unsigned char UCCode)
{
    if (_sendUCTo)
    {
        TransmitMsg(_sendUCTo, 2, CEC_MENU_UC_PRESSED, UCCode);
        TransmitMsg(_sendUCTo, 1, CEC_MENU_UC_RELEASED);
    }
}

#ifdef DEBUG_IRCODES
void debugIRCode(decode_results *results) {
  int codeType = results->decode_type;
  int count = results->rawlen;
  if (codeType == UNKNOWN) {
    unsigned int rawCodes[RAWBUF]; // The durations if raw
    int codeLen; // The length of the code
    Serial.println("Received unknown code, saving as raw");
    codeLen = results->rawlen - 1;
    Serial.println(codeLen);
    // To store raw codes:
    // Drop first value (gap)
    // Convert from ticks to microseconds
    // Tweak marks shorter, and spaces longer to cancel out IR receiver distortion
    Serial.print("unsigned int unknownCode[] = {");
    for (int i = 1; i <= codeLen; i++) {
      if (i % 2) {
        // Mark
        rawCodes[i - 1] = results->rawbuf[i]*USECPERTICK - MARK_EXCESS;
        //Serial.print(" m");
      }
      else {
        // Space
        rawCodes[i - 1] = results->rawbuf[i]*USECPERTICK + MARK_EXCESS;
        //Serial.print(" s");
      }
      //Serial.print("0x");
      Serial.print(rawCodes[i - 1]);
      Serial.print(", ");
    }
    Serial.println("};");
  }
  else {
    if (codeType == NEC) {
      Serial.print("Received NEC: ");
      if (results->value == REPEAT) {
        // Don't record a NEC repeat value as that's useless.
        Serial.println("repeat; ignoring.");
        return;
      }
    }
    else if (results->decode_type == KOGAN) {
     Serial.print("Decoded KOGAN: ");
    }
    else if (codeType == SONY) {
      Serial.print("Received SONY: ");
    }
    else if (codeType == RC5) {
      Serial.print("Received RC5: ");
    }
    else if (codeType == RC6) {
      Serial.print("Received RC6: ");
    }
    else if (codeType == JVC) {
      Serial.print("Received JVC: ");
    }
    else if (results->decode_type == SAMSUNG) {
    Serial.print("Decoded SAMSUNG: ");
    }
    else if (results->decode_type == SANYO) {
    Serial.print("Decoded SANYO: ");
    }
    else if (results->decode_type == PANASONIC) {
    Serial.print("Decoded PANASONIC: ");
    }
    else if (results->decode_type == MITSUBISHI) {
    Serial.print("Decoded MITSUBISHI: ");
    }
    else if (results->decode_type == RCMM) {
    Serial.print("Decoded RCMM: ");
    }
    else {
      Serial.print("Unexpected codeType ");
      Serial.print(codeType, DEC);
      Serial.println("");
    }
    Serial.println(results->value, HEX);
    //codeValue = results->value;
    //codeLen = results->bits;
  }
}
#endif

void CEC_TV::loop()
{
    if (CECSerial->available()){
        switch (CECSerial->read())
        {
        case MESSAGE_REPORT_LOGICAL:
            _logicalAddress = CECBlockRead();
            DbgPrint("got logical addr: %d.\r\n", _logicalAddress);
            TransmitMsg(CEC_BROADCAST, 4, CEC_INFO_PHYS_ADDR, 0, 0, 0);
            break;
        case MESSAGE_RECIEVED:
            byte len = CECBlockRead();
            if (len < 1) {
              //error
              DbgPrint("got bogus len %d.\r\n", len);
              break;
            }
            len--;//remove addr
            byte address = CECBlockRead();//contains both dst and src!
            byte* message = (byte*)malloc(len);
            for (int i = 0; i<len; i++){
              message[i] = CECBlockRead();
            }
            OnReceive(address >> 4, address & 0xF, message, len);
        }
    }
    checkStartupTimeout();
    decode_results results;
    if (irrecv.decode(&results)) {
        //#ifdef DEBUG_IRCODES
        //Serial.print("received something!\r\n");
        results.value = ~ (1 << results.bits-1);
        Serial.println(results.value, HEX);
        //#endif
        if (results.value == REPEAT){//defined in IRremote.h
            unsigned long timeNow = millis();
            if (_lastRemoteInputTime /*&& timeNow-_lastRemoteInputTime >= 20*/ && timeNow - _lastRemoteInputTime <= 200)
            {
                results.value = _lastRemoteInputCode;
                _lastRemoteInputTime = millis();
                //Serial.println("REPEAT");
                //Serial.println(results.value, HEX);
            }
            //Serial.println(timeNow - _lastRemoteInputTime);
        } else {
            _lastRemoteInputTime = millis();
            _lastRemoteInputCode = results.value;
            //Serial.println(results.value, HEX);
            //Serial.println(_lastRemoteInputCode, HEX);
        }
        switch (results.value)
        {
            case REMOTE_POWER:
                check_remote_protocol
                delay(250);
                powerToggle();
                break;
            case REMOTE_GUIDE:
                check_remote_protocol
                delay(250);
                sendKoganCode(&irsend, KOGAN_ASPECT);
                break;
            case REMOTE_UP:
                check_remote_protocol
                //delay(100);
                sendUC(CEC_UC_CODE_UP);
                break;
            case REMOTE_DOWN:
                check_remote_protocol
                //delay(100);
                sendUC(CEC_UC_CODE_DOWN);
                break;
            case REMOTE_LEFT:
                check_remote_protocol
                //delay(100);
                sendUC(CEC_UC_CODE_LEFT);
                break;
            case REMOTE_RIGHT:
                check_remote_protocol
                //delay(100);
                sendUC(CEC_UC_CODE_RIGHT);
                break;
            case REMOTE_ENTER:
                check_remote_protocol
                //delay(100);
                sendUC(CEC_UC_CODE_SELECT);
                break;
            case REMOTE_BACK:
                check_remote_protocol
                //delay(100);
                sendUC(CEC_UC_CODE_EXIT);
                break;
            case REMOTE_PLAY:
                check_remote_protocol
                //delay(100);
                sendUC(CEC_UC_CODE_PLAY);
                break;
            case REMOTE_PAUSE:
                check_remote_protocol
                //delay(100);
                sendUC(CEC_UC_CODE_PAUSE);
                break;
            case REMOTE_SKIP_BACK:
                check_remote_protocol
                //delay(100);
                sendUC(CEC_UC_CODE_BACKWARD);
                break;
            case REMOTE_SKIP_FORWARD:
                check_remote_protocol
                //delay(100);
                sendUC(CEC_UC_CODE_FORWARD);
                break;
            case REMOTE_STOP:
                check_remote_protocol
                //delay(100);
                sendUC(CEC_UC_CODE_STOP);
                break;
            case REMOTE_RECORD:
                check_remote_protocol
                //delay(100);
                sendUC(CEC_UC_CODE_RECORD);
                break;
            #ifdef DEBUG_IRCODES
            default:
                debugIRCode(&results);
            #endif
        }
        irrecv.resume(); // resume receiver
    }
}


