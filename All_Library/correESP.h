#pragma once

#include <Arduino_BuiltIn.h>
#include <HardwareSerial.h>

extern HardwareSerial MySerial;

void setup_correESP();
void ESPsend(double info);