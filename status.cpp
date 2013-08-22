#include "packetserial.h"
#include "cmdcodes.h"
#include "Arduino.h"
#include "MemoryFree.h"
void send_mem_status(){
  char buff[2+sizeof(int)];
  buff[0] = STATUS;
  buff[1] = MEMFREE;
  //char buff[2] = freeMemory();
  int freemem = freeMemory();
  memcpy(&buff[2],&freemem,sizeof(int));
  
  //int len;
  //len = sprintf(buff, "Free Bytes: %i",freeMemory());
  packet_serial_send((byte*)buff,(byte) 2+sizeof(int));
}

void send_addr(int physical, byte logical){
  byte addresses[5];
  addresses[0] = STATUS;
  addresses[1] = STATUS_ADD;
  memcpy(&addresses[2],&physical,sizeof(int));
  addresses[4] = logical;
  packet_serial_send((byte*)addresses, 5); 
}
