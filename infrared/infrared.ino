#include "infrared.h"
#include "lstmInfrared.h"

void setup(){
  Serial.begin(115200);
  setup_infra();
}

void loop(){ 
  double ballDire = getBallDire();
  Serial.println(ballDire);
}