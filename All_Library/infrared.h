#pragma once



#include <Wire.h> 
#include <Arduino.h>
#include <math.h>

#define TCAADDR 0x70

//void tcaselect(uint8_t bus);

#define FSDA 10
#define FSCL 9
#define BSDA 11
#define BSCL 12 //with sonar

void setup_infra();
int maxChannel(TwoWire *wire);
int maxNum(TwoWire *wire);
int channelNum(int t, TwoWire *wire);
void printInfrared();

