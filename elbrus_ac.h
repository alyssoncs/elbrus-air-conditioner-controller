#ifndef ELBRUS_AC_H
#define ELBRUS_AC_H

#include <Arduino.h>
#include <IRremote.h>

/* time interval values, specific to this air conditioner (in microseconds)*/
#define HEADER_MARK     2900
#define HEADER_SPACE    1650
#define SEPARATOR_MARK  400
#define SET_BIT_TIME    400
#define CLEAR_BIT_TIME  1150

/* number of bits in a message, this does not count the header's bits nor the separator marks */
#define MESSAGE_BITS    112

/* minimum and maximum temperatures in Celsius supported/tested so far */
#define MIN_TEMP        16
#define MAX_TEMP        25

/* 
 * bytes 7 and 13 are the only bytes that appear to change when changing between temperatures 
 * these are its values when the air conditioner is in MIN_TEMP Celsius
 */
#define BYTE07_MIN      B11110000
#define BYTE13_MIN      B10110010

/* size in bytes of a message */
#define MESSAGE_SIZE  (MESSAGE_BITS)/8 + !!((MESSAGE_BITS)%8)


/* 
 *  fill the out array of length len, with the temperature representation of this air conditioner
 *  this representation can than be used by the sendRawByBit, to send a command to the AC
 */
void getTemperatureRepresentation(byte out[], int len, int temperature);

/*
 * send a command inside the buff buffer to the air conditioner
 */
void sendRawByBit(IRsend irsend, byte buff[], int khz);

#endif
