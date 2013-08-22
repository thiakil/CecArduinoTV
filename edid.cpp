#include "Arduino.h"
#include "edid.h"
//#include "cli.h"
#include <Wire.h>
#include "Common.h"
#define EDID 0x50

#define EDID_LENGTH 128
#define EDID_EXTENSION_COUNT 126
#define EDID_MAX_EXTENSIONS 4
#define HDMI_IDENTIFIER 0x000C03
#define VENDOR_BLOCK    0x03

void readEDIDFrame(byte * buffer){
  byte chunk = 0;
  byte i = 0;
  for (chunk = 0; chunk < (EDID_LENGTH / 32) ; chunk++){
    Wire.requestFrom(EDID, 32);
    //DbgPrint("Reading i2c Response (%i bytes)\r\n", Wire.available());
    while (Wire.available() && i < EDID_LENGTH){
      buffer[i++] = Wire.read();
    }
  }
}

void printEDID(byte * buffer){
  for (int i = 0; i < EDID_LENGTH; i++){
    DbgPrint("%02X ", buffer[i]);
    if ((i > 1) && ((i + 1) % 16 == 0))
      DbgPrint("\r\n");
  }
  DbgPrint("\r\n");
}

void resetEDID(byte * buffer){
  //reset our buffer
  for (int i = 0; i < EDID_LENGTH; i++)
    buffer[i] = 0;
}

byte validateEDIDStructure(byte * buffer){
  byte csum = 0;
  for (int i = 0; i < EDID_LENGTH; i++)
    csum += buffer[i];
  return csum;
}

int readEDID(){
  byte buffer[EDID_LENGTH];
  byte edid_extensions = 0;

  Wire.beginTransmission(EDID);
  Wire.write(0x00); //Send a byte to initiate response
  Wire.endTransmission();

  Wire.beginTransmission(EDID);


  //check primary edid frame
  readEDIDFrame(buffer);
  int i = 0;

  //validate checksum
  if(validateEDIDStructure(buffer)){
    DbgPrint("bad edid %i \r\n", validateEDIDStructure(buffer));   //bad edid
    return ERROR_EDID_BAD_PACKET;
  }

  edid_extensions = buffer[EDID_EXTENSION_COUNT];
  printEDID(buffer);

  resetEDID(buffer);

  if (edid_extensions > EDID_MAX_EXTENSIONS)
    edid_extensions = EDID_MAX_EXTENSIONS;
//  DbgPrint("Found %i extensions\r\n", edid_extensions);
  //find CEA E-EDID
  for (i = 0; i < edid_extensions; i++){
    readEDIDFrame(buffer);
    if (buffer[0] == 0x02)
      break; //found the CEA packet

  }
  if (i == edid_extensions){
    //DbgPrint("CEA Packet not found\r\n");
    return ERROR_EDID_NO_CEA; //CEA packet not found
  }
  printEDID(buffer);
  if(validateEDIDStructure(buffer))
    return ERROR_EDID_BAD_PACKET;

  //    DbgPrint("bad edid %i \r\n", validateEDIDStructure(buffer));   //bad edid

  Wire.endTransmission();
  //DbgPrint("Done reading i2c\r\n");


  int start_offset, end_offset, hdmi_id;


  start_offset = 4;
  end_offset = buffer[2];
  for (i = start_offset; i < end_offset;
                /* Increased by data block len */
                i += ((buffer[i] & 0x1f) + 1)) {
    /* Find vendor specific block */
    if ((buffer[i] >> 5) == VENDOR_BLOCK) {
      hdmi_id = buffer[i + 1] | (buffer[i + 2] << 8) |
        buffer[i + 3] << 16;
      /* Find HDMI identifier */
      if (hdmi_id == HDMI_IDENTIFIER){
        //The following two bytes are the CEC physical address
        hdmi_id = (buffer[i+4] << 8) | buffer[i+5];

        //DbgPrint("Found HDMI CEC Physical Address %04X\r\n", hdmi_id);
        return hdmi_id;
      }
    }
  }
  return ERROR_EDID_NO_CEC;
}







