#include "correMega.h"

void setup_correMega(){
  Serial2.begin(115200); // 波特率必须和 ESP32 一致
}

float receive(){
  //Serial.println(Serial2.available());
  if (Serial2.available() >= 4){
    String serialData = Serial2.readStringUntil('\n');
    float data = serialData.toFloat();
    //Serial.println(data,6);
    return data;
  }
  return -1;
}