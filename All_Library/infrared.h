#pragma once


/*
imports:
#include <Wire.h> 
#define TCAADDR 0x70

setup:
Wire.begin();
*/

#include <Wire.h> 
#include <Arduino.h>
#include <math.h>

#define TCAADDR 0x70

int JMP_BEnum();
int JMP_BEstr();
void tcaselect(uint8_t bus);
void printInfrared();

