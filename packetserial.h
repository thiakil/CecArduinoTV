#include <Wire.h>
#include "Arduino.h"
extern void packet_serial_send(unsigned char* payload, unsigned char length);
extern void packet_serial_run(void);
extern void handle_packet(byte* payload, byte length);
