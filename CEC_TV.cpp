#ifndef CEC_TV_H__
#define CEC_TV_H__

#define DEBUG_CODES
#define DEBUG_IRCODES

#include "CEC_TV.h"

void debugReceivedMsg(int source, int dest, unsigned char* buffer, int count){
    DbgPrint("%d -> %d (%d): ", source, dest, count);
    if (count){
        switch(buffer[0]){
            #ifdef DEBUG_CODES
            case CEC_FEATURE_ABORT: DbgPrint("FEATURE_ABORT\r\n"); break;
            case CEC_OTP_IMAGE_ON: DbgPrint("IMAGE_ON\r\n"); break;
            //case CEC_TUNER_UP: DbgPrint("CEC_TUNER_UP\r\n"); break;
            //case CEC_TUNER_DOWN: DbgPrint("CEC_TUNER_DOWN\r\n"); break;
//                case CEC_TUNER_STATUS: DbgPrint("CEC_TUNER_STATUS\r\n"); break;
//                case CEC_TUNER_STATUS_REQ: DbgPrint("CEC_TUNER_STATUS_REQ\r\n"); break;
//                case CEC_OTR_REC_ON: DbgPrint("CEC_OTR_REC_ON\r\n"); break;
//                case CEC_OTR_REC_STATUS: DbgPrint("CEC_OTR_REC_STATUS\r\n"); break;
//                case CEC_OTR_REC_OFF: DbgPrint("CEC_OTR_REC_OFF\r\n"); break;
            case CEC_OTP_TEXT_ON: DbgPrint("TEXT_ON\r\n"); break;
            case CEC_OTR_REC_SCREEN: DbgPrint("REC_SCREEN\r\n"); break;
                case CEC_DECK_REQ_STATUS: DbgPrint("CEC_DECK_REQ_STATUS\r\n"); break;
                case CEC_DECK_STATUS: DbgPrint("CEC_DECK_STATUS\r\n"); break;
                case CEC_INFO_LANG: DbgPrint("CEC_INFO_LANG\r\n"); break;
//                case CEC_TIMER_CLEAR_ANALOG: DbgPrint("CEC_TIMER_CLEAR_ANALOG\r\n"); break;
//                case CEC_TIMER_SET_ANALOG: DbgPrint("CEC_TIMER_SET_ANALOG\r\n"); break;
//                case CEC_TIMER_STATUS: DbgPrint("CEC_TIMER_STATUS\r\n"); break;
            case CEC_STANDBY: DbgPrint("STANDBY\r\n"); break;
            //case CEC_DECK_PLAY: DbgPrint("CEC_DECK_PLAY\r\n"); break;
            //case CEC_DECK_CTRL: DbgPrint("CEC_DECK_CTRL\r\n"); break;
//                case CEC_TIMER_STATUS_CLEARED: DbgPrint("CEC_TIMER_STATUS_CLEARED\r\n"); break;
                case CEC_MENU_UC_PRESSED: DbgPrint("CEC_MENU_UC_PRESSED\r\n"); break;
            case CEC_OSD_REQ_OSD: DbgPrint("OSD_REQ_OSD\r\n"); break;
            case CEC_OSD_SET_OSD: DbgPrint("OSD_SET_OSD\r\n"); break;
            case CEC_OSD_SEND: DbgPrint("CEC_OSD_SEND\r\n"); break;
//                case CEC_TIMER_SET_TITLE: DbgPrint("CEC_TIMER_SET_TITLE\r\n"); break;
                case CEC_AUDIO_MODE_REQ: DbgPrint("CEC_AUDIO_MODE_REQ\r\n"); break;
                case CEC_AUDIO_STATUS_REQ: DbgPrint("CEC_AUDIO_STATUS_REQ\r\n"); break;
                case CEC_AUDIO_MODE_SET: DbgPrint("CEC_AUDIO_MODE_SET\r\n"); break;
                case CEC_AUDIO_STATUS: DbgPrint("CEC_AUDIO_STATUS\r\n"); break;
                case CEC_Give_System_Audio_Mode_Status: DbgPrint("CEC_Give_System_Audio_Mode_Status\r\n"); break;
                case CEC_AUDIO_MODE: DbgPrint("CEC_AUDIO_MODE\r\n"); break;
            case CEC_ROUTING_CHANGED: DbgPrint("CEC_ROUTING_CHANGED\r\n"); break;
            case CEC_ROUTING_INFO: DbgPrint("ROUTING_INFO\r\n"); break;
            case CEC_ROUTING_ACTIVE: DbgPrint("ROUTING_ACTIVE\r\n"); break;
            case CEC_INFO_REQ_PHYS_ADDR: DbgPrint("INFO_REQ_PHYS_ADDR\r\n"); break;
            case CEC_INFO_PHYS_ADDR: DbgPrint("INFO_PHYS_ADDR\r\n"); break;
            case CEC_ROUTING_REQ_ACTIVE: DbgPrint("ROUTING_REQ_ACTIVE\r\n"); break;
            case CEC_ROUTING_REQ_PATH: DbgPrint("ROUTING_REQ_PATH\r\n"); break;
            case CEC_VENDOR_ID: DbgPrint("VENDOR_ID\r\n"); break;
            //case CEC_VENDOR_COMMAND: DbgPrint("CEC_VENDOR_COMMAND\r\n"); break;
            //case CEC_VENDOR_REMOTE_BDOWN: DbgPrint("CEC_VENDOR_REMOTE_BDOWN\r\n"); break;
            //case CEC_VENDOR_REMOTE_BUP: DbgPrint("CEC_VENDOR_REMOTE_BUP\r\n"); break;
            //case CEC_VENDOR_ID_REQ: DbgPrint("CEC_VENDOR_ID_REQ\r\n"); break;
            case CEC_MENU_REQ: DbgPrint("MENU_REQ\r\n"); break;
            case CEC_MENU_STATUS: DbgPrint("MENU_STATUS\r\n"); break;
            case CEC_POWER_REQ_STATUS: DbgPrint("POWER_REQ_STATUS\r\n"); break;
            case CEC_POWER_STATUS: DbgPrint("POWER_STATUS\r\n"); break;
            //case CEC_INFO_LANG_REQ: DbgPrint("CEC_INFO_LANG_REQ\r\n"); break;
//                case CEC_TUNER_SELECT_ANALOG: DbgPrint("CEC_TUNER_SELECT_ANALOG\r\n"); break;
//                case CEC_TUNER_SELECT_DIGITAL: DbgPrint("CEC_TUNER_SELECT_DIGITAL\r\n"); break;
//                case CEC_TIMER_SET_DIGITAL: DbgPrint("CEC_TIMER_SET_DIGITAL\r\n"); break;
//                case CEC_TIMER_CLEAR_DIGITAL: DbgPrint("CEC_TIMER_CLEAR_DIGITAL\r\n"); break;
//                case CEC_AUDIO_RATE: DbgPrint("CEC_AUDIO_RATE\r\n"); break;
            case CEC_ROUTING_INACTIVE: DbgPrint("ROUTING_INACTIVE\r\n"); break;
            case CEC_INFO_VERSION: DbgPrint("INFO_VERSION\r\n"); break;
            //case CEC_VENDOR_CEC_VERSION: DbgPrint("CEC_VENDOR_CEC_VERSION\r\n"); break;
            //case CEC_INFO_VERSION_REQ: DbgPrint("CEC_INFO_VERSION_REQ\r\n"); break;
            //case CEC_VENDOR_CEC_VERSION_REQ: DbgPrint("CEC_VENDOR_CEC_VERSION_REQ\r\n"); break;
            //case CEC_VENDOR_COMMAND_ID: DbgPrint("CEC_VENDOR_COMMAND_ID\r\n"); break;
            //case CEC_TIMER_CLEAR_EXTERNAL: DbgPrint("CEC_TIMER_CLEAR_EXTERNAL\r\n"); break;
            //case CEC_TIMER_SET_EXTERNAL: DbgPrint("CEC_TIMER_SET_EXTERNAL\r\n"); break;
            #endif//#DEBUG_CODES
            default: DbgPrint("unknown (%d)\r\n", buffer[0]); break;
        }
        if (count > 1) {
            for (int i = 1; i < count; i++)
            DbgPrint("%02X ", buffer[i]);
            DbgPrint("\r\n");
        }
    } else {
        DbgPrint("Ping \r\n");
    }
}

void CEC_TV::OnReceive(int source, int dest, unsigned char* buffer, int count){
    //#ifdef DEBUG_CODES
        debugReceivedMsg(source, dest, buffer, count);
    //#endif //#DEBUG_CODES

    if (count && (dest == _logicalAddress || dest == CEC_BROADCAST)){
        switch(buffer[0]){
            case CEC_OTP_IMAGE_ON:
            case CEC_OTP_TEXT_ON:
                powerOn();
                break;
            case CEC_STANDBY:
                powerOff();
                break;
            case CEC_INFO_VERSION_REQ:
                TransmitMsgQ(source, CEC_INFO_VERSION, 0x04);//hdmi 1.3a
            case CEC_INFO_VERSION:
                break;
            case CEC_INFO_REQ_PHYS_ADDR:
                TransmitMsgQ(source, CEC_INFO_PHYS_ADDR, _physicalAddress >> 8, _physicalAddress & 0xFF, _deviceType);
                break;
            case CEC_POWER_REQ_STATUS:
                TransmitMsgQ(source, CEC_POWER_STATUS, _powerStatus);
                break;
            case CEC_ROUTING_ACTIVE:
                if (_powerStatus == CEC_POWER_STATUS_ON)
                {
                    _activeSrcBroadcast = 0;
                    DbgPrint("changing to input %d\r\n", buffer[1]>>4 & 0xf);
                    changeKoganInput(&irsend, buffer[1]>>4 & 0xf);
                    irrecv.enableIRIn(); // Re-enable receiver
                    TransmitMsgQ(source, CEC_OSD_REQ_OSD);
                }
                break;
            case CEC_ROUTING_INACTIVE:
                if (_powerStatus == CEC_POWER_STATUS_ON)
                    broadcastForActiveSource(true);//this probably shows up with nothing as other sources assume they're not active, but we check to be sure.
                    DbgPrint("should probably do proper check of device standby status, and switch to one if its active\r\n");
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
                            DbgPrint("On");
                            break;
                        case CEC_POWER_STATUS_STANDBY:
                            DbgPrint("on Standby");
                            break;
                        case CEC_POWER_STATUS_TRANSITION_STANDBY_TO_ON:
                            DbgPrint("Turning On");
                            break;
                        case CEC_POWER_STATUS_TRANSITION_ON_TO_STANDBY:
                            DbgPrint("Turning Off");
                            break;
                        default:
                            DbgPrint("UNKNOWN STATUS (%d)", buffer[1]);
                            break;
                    }
                    DbgPrint("\r\n");
                #endif
            case CEC_INFO_PHYS_ADDR:
                break;
            case CEC_OSD_SET_OSD:
                {
                    short osdLen = count -1;
                    if (osdLen){
                        char* osdName = new char[osdLen];
                        memcpy(osdName, buffer+1, osdLen);
                        osdName[osdLen] = 0;
                        DbgPrint("Device at logical %d is known as \"%s\"\r\n", source, osdName);
                        delete osdName;
                    }
                    break;
                }
            default:
                if (dest == _logicalAddress)//dont wanna do for bcast
                    DbgPrint("ABORT!\r\n");
                    //TransmitMsg(source, CEC_FEATURE_ABORT, CEC_ABORT_UNRECOGNIZED);
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

short currentInput = -1;

//6th item is hdmi 1
void changeKoganInput(IRsend* irsend, short hdmiInput)
{
    DbgPrint("current: %d, wanted: %d\r\n", currentInput, hdmiInput);
    int numPresses = 0;
    bool down = true;
    if (currentInput == hdmiInput)
        return;
    if (currentInput == -1)//its unknown
    {
        hdmiInput--;//make it 0 based
        numPresses = 2 + hdmiInput;//2 is from componenet
        //sendKoganCode(irsend, KOGAN_DTV);
        //delay(2000);
        sendKoganCode(irsend, 0x0F9);//switch to componenet
        sendKoganCode(irsend, 0x0F9);//switch to componenet
        delay(KOGAN_DELAY*2);
    } else if (currentInput < hdmiInput) {
        numPresses = hdmiInput - currentInput;
    } else {
        numPresses = currentInput - hdmiInput;
        down = false;
    }
    DbgPrint("presses: %d\r\n", numPresses);

    sendKoganCode(irsend, KOGAN_INPUT);
    delay(KOGAN_DELAY*2);
    for (int i=0; i < numPresses; i++){
        if (down)
            sendKoganCode(irsend, KOGAN_DOWN);
        else
            sendKoganCode(irsend, KOGAN_UP);
        delay(KOGAN_DELAY);
    }
    sendKoganCode(irsend, KOGAN_ENTER);
    currentInput = hdmiInput;
}

void CEC_TV::powerOn(){
    if (_powerStatus != CEC_POWER_STATUS_ON && _powerStatus != CEC_POWER_STATUS_TRANSITION_STANDBY_TO_ON) {
        _powerStatus = CEC_POWER_STATUS_TRANSITION_STANDBY_TO_ON;
        sendKoganCode(&irsend, KOGAN_POWER);
        _turnedOnAt = millis();
        irrecv.enableIRIn(); // Re-enable receiver
    }
}

void CEC_TV::broadcastForActiveSource(bool noResponseTurnOff)
{
    TransmitMsgQ(0xf, CEC_ROUTING_REQ_ACTIVE);//is called from within onreceive too
    _activeSrcBroadcastForStandby = noResponseTurnOff;
    _activeSrcBroadcast = millis();
}

void CEC_TV::checkStartupTimeout()
{
    if (_turnedOnAt){
        if (millis() - _turnedOnAt >= 15000)//takes about 13s to start up
        {
            _turnedOnAt = 0;
            _powerStatus = CEC_POWER_STATUS_ON;
            DbgPrint("TODO: proper power on check\r\n");
            broadcastForActiveSource();
        }
    }
    if (_activeSrcBroadcast && millis() - _activeSrcBroadcast >= 10000)//10 sec timeout
    {
        DbgPrint("activesrc triggered (%d): %s\r\n", _activeSrcBroadcast, _activeSrcBroadcastForStandby ? "true" : "false");
        if (_activeSrcBroadcastForStandby)
        {
            _activeSrcBroadcast = 0;
            powerOff();
        } else {
            int switchAddr = (currentInput != -1) ? currentInput << 12 : DEFAULT_INPUT_ADDR;
            TransmitMsg(0xf, CEC_ROUTING_REQ_PATH, switchAddr >> 8, switchAddr & 0xFF);
            broadcastForActiveSource(true);
        }
    }
}

void CEC_TV::powerOff()
{
    if(_powerStatus == CEC_POWER_STATUS_ON)
    {
        sendKoganCode(&irsend, KOGAN_POWER);
        _powerStatus = CEC_POWER_STATUS_STANDBY;
        TransmitMsg(CEC_BROADCAST, CEC_STANDBY);
        DbgPrint("TODO: proper power off check\r\n");
        irrecv.enableIRIn(); // Re-enable receiver
    }
    if (_powerStatus == CEC_POWER_STATUS_TRANSITION_STANDBY_TO_ON)
        DbgPrint("still transitioning!\r\n");
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
        TransmitMsgQ(_sendUCTo, CEC_MENU_UC_PRESSED, UCCode);
        TransmitMsgQ(_sendUCTo, CEC_MENU_UC_RELEASED);
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
    Run();
    SendQueued();
    checkStartupTimeout();
    decode_results results;
    if (irrecv.decode(&results)) {
        //#ifdef DEBUG_IRCODES
        DbgPrint("received something!\r\n");
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
            case REMOTE_1:
                check_remote_protocol
                delay(250);
                changeKoganInput(&irsend, 1);
                break;
            case REMOTE_2:
                check_remote_protocol
                delay(250);
                changeKoganInput(&irsend, 2);
                break;
            case REMOTE_3:
                check_remote_protocol
                delay(250);
                changeKoganInput(&irsend, 3);
                break;
            case REMOTE_4:
                check_remote_protocol
                delay(250);
                changeKoganInput(&irsend, 4);
                break;
            case REMOTE_0:
                check_remote_protocol
                delay(250);
                currentInput = -1;//reset it
                changeKoganInput(&irsend, 1);
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

#endif // CEC_TV_H__
