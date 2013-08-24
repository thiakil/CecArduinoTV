#ifndef CEC_TV_H__
#define CEC_TV_H__

#define DEBUG_CODES

#include "CEC_TV.h"
#include <IRremote.h>

void debugReceivedMsg(int source, int dest, unsigned char* buffer, int count){
    DbgPrint("%d -> %d (%d): ", source, dest, count);
    if (count){
        switch(buffer[0]){
            #ifdef DEBUG_CODES
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
            case CEC_ROUTING_ACTIVE: DbgPrint("CEC_ROUTING_ACTIVE\r\n"); break;
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

IRsend irsend;

void CEC_TV::OnReceive(int source, int dest, unsigned char* buffer, int count){
    #ifdef DEBUG_CODES
        debugReceivedMsg(source, dest, buffer, count);
    #endif //#DEBUG_CODES

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
                DbgPrint("status requested\r\n");
                TransmitMsgQ(source, CEC_POWER_STATUS, _powerStatus);
                DbgPrint("status sent\r\n");
                break;
            case CEC_ROUTING_ACTIVE:
                DbgPrint("TODO: change input\r\n");
                TransmitMsgQ(source, CEC_OSD_REQ_OSD);
                break;
            case CEC_ROUTING_INACTIVE:
                TransmitMsgQ(CEC_BROADCAST, CEC_ROUTING_REQ_ACTIVE);
                powerOff();
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

unsigned int koganTvPower[] = {0xBB6, 0xBDA, 0x1C6, 0x60A, 0x1BE, 0x60A, 0x1BE, 0x60A, 0x1BE, 0x622, 0x1AE, 0x61A,
                               0x1AE, 0x61A, 0x1B6, 0x9FA, 0x1BE, 0x60A, 0x1BE, 0x612, 0x1BE, 0x612, 0x1B6, 0x612,
                               0x1CE, 0x602, 0x1CE, 0x9EA, 0x1BE, 0x612, 0x1BE, 0x9F2, 0x1BE, 0x9FA, 0x1BE, 0xFD2, 0x1BE,};

void CEC_TV::powerOn(){
    if (_powerStatus != CEC_POWER_STATUS_ON && _powerStatus != CEC_POWER_STATUS_TRANSITION_STANDBY_TO_ON) {
        _powerStatus = CEC_POWER_STATUS_TRANSITION_STANDBY_TO_ON;
        irsend.sendRaw(koganTvPower, 37, 38);
        _turnedOnAt = millis();
    }
}

void CEC_TV::checkStartupTimeout()
{
    if (_turnedOnAt){
        if (millis() - _turnedOnAt >= 13000)//takes about 13s to start up
        {
            _turnedOnAt = 0;
            _powerStatus = CEC_POWER_STATUS_ON;
            DbgPrint("TODO: proper power on check\r\n");
        }
    }
}

void CEC_TV::powerOff()
{
    if(_powerStatus == CEC_POWER_STATUS_ON)
    {
        irsend.sendRaw(koganTvPower, 37, 38);
        irsend.sendRaw(koganTvPower, 37, 38);
        _powerStatus = CEC_POWER_STATUS_STANDBY;
        DbgPrint("TODO: proper power off check\r\n");
    }
    if (_powerStatus == CEC_POWER_STATUS_TRANSITION_STANDBY_TO_ON)
        DbgPrint("still transitioning!\r\n");
}

#endif // CEC_TV_H__
