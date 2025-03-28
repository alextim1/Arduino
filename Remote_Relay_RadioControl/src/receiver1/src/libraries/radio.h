#ifndef BLINK
#define BLINK

#include "blink.h"

#endif

#ifndef RADIO
#define RADIO

#include <stdint.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#endif

//----------- Types & Enums --------------

typedef struct radioPayload
{
    /* data */
    States  state = {DISENGAGED};
    uint8_t request = {HIGH};
} RadioPayload;


//------------ radio constatnts ------------

const uint8_t mosi = 11;
const uint8_t miso = 12;
const uint8_t sck = 13;

const uint8_t ce = 9;
const uint8_t csn = 10;

const uint8_t addresses [][6] = {"00001","00002","00003","00004"};


