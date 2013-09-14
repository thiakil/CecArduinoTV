#include <IRremote.h>

#include <TinyWireS.h>
#ifndef TWI_RX_BUFFER_SIZE
#define TWI_RX_BUFFER_SIZE ( 16 )
#endif

#define IS_IR_SLAVE
#include "IRModule_config.h"

IRsend irsend;

#define KOGAN_DELAY 500
void sendKoganCode(IRsend* irsend, int code)
{
    irsend->sendKogan(code, 32);
    irsend->sendKogan(code, 32);
}

//6th item is hdmi 1
void changeInput(IRsend* irsend, short hdmiInput, short currentInput)
{
    //DbgPrint("current: %d, wanted: %d\r\n", currentInput, hdmiInput);
    int numPresses = 0;
    bool down = true;
    if (currentInput == hdmiInput)
        return;
    if (currentInput == -1)//its unknown
    {
        hdmiInput--;//make it 0 based
        numPresses = 2 + hdmiInput;//2 is from componenet
        //sendKoganCode(irsend, TVCODE_DTV);
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
    //DbgPrint("presses: %d\r\n", numPresses);

    sendKoganCode(irsend, TVCODE_INPUT);
    delay(KOGAN_DELAY*2);
    for (int i=0; i < numPresses; i++){
        if (down)
            sendKoganCode(irsend, TVCODE_DOWN);
        else
            sendKoganCode(irsend, TVCODE_UP);
        delay(KOGAN_DELAY);
    }
    sendKoganCode(irsend, TVCODE_ENTER);
    currentInput = hdmiInput;
}

void receiveEvent(uint8_t howMany)
{
    if (howMany < 1)
    {
        // Sanity-check
        return;
    }
    if (howMany > TWI_RX_BUFFER_SIZE)
    {
        // Also insane number
        return;
    }
    
    //digitalWrite(4, HIGH);

    int i2cCmd = TinyWireS.receive();
    int param =0; 
    howMany--;
    
    switch(i2cCmd){
      case TVCOMAND_power:
        SENDFUNC(TVCODE_POWER);
        break;
      case TVCOMAND_changeinput:
        if (howMany == 2)
        {
          changeInput(&irsend, TinyWireS.receive(), TinyWireS.receive());
        }
        break;
      case TVCOMAND_aspect:
        SENDFUNC(TVCODE_ASPECT);
        break;
      case TVCOMAND_sendcode:
        SENDFUNC(TinyWireS.receive());
        break;
    }
    
    /*while(howMany--)
    {
        param = TinyWireS.receive();
    }
        //digitalWrite(4, LOW);
    */
}


void setup()
{
    TinyWireS.begin(I2C_SLAVE_ADDRESS);
    TinyWireS.onReceive(receiveEvent);
    pinMode(4, OUTPUT);
}


void loop() {
  TinyWireS_stop_check();
}
