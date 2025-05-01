#include "correESP.h"


void setup() {
  Serial.begin(115200);
  setup_correESP();
}

int theta = 0;
void loop() {
  double num = 1.0*theta*M_PI/180;
  ESPsend(num);
  Serial.println(num);
  //delay(10);
  theta = (theta+10)%360;
}