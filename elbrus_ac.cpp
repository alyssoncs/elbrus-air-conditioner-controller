#include <Arduino.h>
#include "elbrus_ac.h"


/* Bytes 7 and 13 define the temperature */
byte MSG[MESSAGE_SIZE] = {B00111011, B00101100, 
                          B10011011, B01111111,
                          B11111111, B11011011,
                          B00111111, B00000000,
                          B10111111, B11111111,
                          B11111111, B11111111,
                          B11111111, B00000000
};

static byte reverseBitsInByte(byte b) {
  return (b&1U<<0)<<7|(b&1U<<1)<<5|(b&1U<<2)<<3|(b&1U<<3)<<1|(b&1U<<4)>>1|(b&1U<<5)>>3|(b&1U<<6)>>5|(b&1U<<7)>>7;
}


static int getBit(byte bitArr[], unsigned int bitpos) {
  if (bitArr) {
    unsigned int index = bitpos / 8;
    byte mask = 1<<(7-(bitpos%8));

    return (bitArr[index] & mask) != 0;
  }
  
  return -1;
}

void getTemperatureRepresentation(byte out[], int len, int temperature) {
  temperature = constrain(temperature, MIN_TEMP, MAX_TEMP);
  
  byte b07 = BYTE07_MIN + (temperature - MIN_TEMP);
  byte b13 = BYTE13_MIN + (temperature - MIN_TEMP);
  
  if (out && len >= MESSAGE_SIZE) {
    for (int i = 0; i < MESSAGE_SIZE; i++)
      out[i] = MSG[i];

    out[7]  = reverseBitsInByte(b07);
    out[13] = reverseBitsInByte(b13);
  }
}


void sendRawByBit(IRsend irsend, byte buf[], int khz) {  
  const int timeArr[] = {CLEAR_BIT_TIME, SET_BIT_TIME};
  
  irsend.enableIROut(khz);
  irsend.mark(HEADER_MARK);
  irsend.space(HEADER_SPACE);
  
  for (int i = 0; i < MESSAGE_BITS; i++) {
    irsend.mark(SEPARATOR_MARK);
    irsend.space(timeArr[getBit(buf, i)]);
  }
  
  irsend.mark(SEPARATOR_MARK);
  irsend.space(0);
}

