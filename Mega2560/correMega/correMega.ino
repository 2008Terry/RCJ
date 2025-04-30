#include "correMega.h"

// Mega2560 接收 ESP32 发送的 float 数据
void setup() {
  Serial.begin(115200);
  setup_correMega();
}

void loop() {
  float num = receive();
  if(num != -1) Serial.println(num);
  
}