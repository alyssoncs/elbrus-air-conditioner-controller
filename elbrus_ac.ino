#include "elbrus_ac.h"

const int DELAY_TIME = 1000;    /* Time to wait to change the temperature again */

IRsend irsend;

void setup() {

}

/*
 * iterate through all the supported temperatures
 */
void loop() {

  for (int i = MIN_TEMP; i <= MAX_TEMP; i++) {
    int khz = 38;
    byte temperatureBuff[MESSAGE_SIZE]; /* MESSAGE_SIZE is defined in elbrus_ac.h */
    
    getTemperatureRepresentation(temperatureBuff, MESSAGE_SIZE, i);
    sendRawByBit(irsend, temperatureBuff, khz);
  }

  delay(DELAY_TIME);
}

