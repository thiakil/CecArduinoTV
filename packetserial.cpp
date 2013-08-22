#include "Serial.h"
#include "packetserial.h"
typedef enum {
  IdleWait,
  ReadLength,
  Receiving,
  CheckSum,
  SendAck,
  SendNack,
  HandlePacket,
  ResetBuffer
} 
PacketSerialState;

#define ACK 0xFD
#define NACK 0xFE
#define STARTBYTE 0x02
#define PACKET_SERIAL_BUFFER_LENGTH 32
static PacketSerialState currentState;
static byte buffer[PACKET_SERIAL_BUFFER_LENGTH];
static byte length;
static byte position;

static boolean validate_checksum(byte checksum);
void packet_serial_send(byte* payload, byte length);
//extern void handle_packet(byte* payload, byte length);


void packet_serial_run(){

  switch(currentState){

    //States
  case IdleWait:
    //check for bytes waiting
    if (Serial.available()){
      if (Serial.read() == STARTBYTE)
        currentState=ReadLength;
      else
        currentState=SendNack; 
    }
    //if first byte = x02, state = ReadLength
    //else send reject //ignore?
    break;   


  case ReadLength:
    //if byte waiting, packet length = byte value, state = receiving
    if (Serial.available()){
      length = Serial.read();
      currentState=Receiving;
    }
    break;

  case Receiving:
    //if byte waiting
    if (Serial.available()){
      buffer[position++] = Serial.read(); //byte
      //if  position reachse length, state = checksum
      if (position >= length){ //check this, is checksum part of length?
        currentState=CheckSum;
      }
    }
    break;

  case CheckSum:
    //if byte waiting,
    if (Serial.available()){
      byte checksum = Serial.read();

      boolean valid = validate_checksum(checksum);
      if (valid)
        currentState=SendAck;
      else
        currentState=SendNack;
    }
    break;

  case SendAck:
    //send ack
    Serial.write(ACK);
    currentState=HandlePacket;
    break;


  case SendNack:
    //send nack
    Serial.write(NACK);
    currentState=ResetBuffer;
    break;

  case HandlePacket:
    //call process packet function
    handle_packet(buffer,length);
    currentState = ResetBuffer;
    break;

  case ResetBuffer:
    //reset buffer and length/position vars
    int i;
    for (i = 0; i < PACKET_SERIAL_BUFFER_LENGTH; i++){
      buffer[i] = 0;
    }
    position = 0;
    length = 0;
    currentState = IdleWait;
    break;

  default:
    //something terrible happened
    currentState=ResetBuffer;
    break;
  } 


}


static boolean validate_checksum(byte checksum){
  byte bytesum = 0;
  bytesum += length;

  byte i;
  for (i=0; i < length; i++){
    bytesum = (byte) (bytesum + buffer[i]);
  }

  bytesum = (byte) (256 - bytesum);

  if (bytesum == checksum){
    return true;
  } 
  else {
    //log_debug("invalid packet checksum");
    return false;
  }

}

void packet_serial_send(byte* payload, byte length){
  //Send start byte
  Serial.write(STARTBYTE);
  //Send Length
  Serial.write(length);
  //Send payload
  byte i;
  for (i = 0; i < length; i++){
    Serial.write(payload[i]);
  }
  //Send checksum byte
  byte bytesum = 0;
  bytesum += length;
  for (i=0; i < length; i++){
    bytesum = (byte) (bytesum + payload[i]); 
  }
  bytesum = (byte) (256 - bytesum);
  Serial.write(bytesum);
  
  //check response byte
  byte resp = Serial.read();
 
}





