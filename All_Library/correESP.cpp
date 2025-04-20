#include "correESP.h"
HardwareSerial MySerial(1);

void setup_correESP(){
  MySerial.begin(115200, SERIAL_8N1, 17, 18); //17RX 18TX 
}

void ESPsend(double info){
  MySerial.println(info);
  //delay(10);
  MySerial.flush();
}