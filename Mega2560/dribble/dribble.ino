#include "dribble.h"


void setup() {
  Serial.begin(115200);
  setup_dribble();
}

void loop() {
  // int val = analogRead(graySuck);
  // Serial.println(val);
  suck(1200);
  // spin(1600);
  // delay(3000);
  // spin(1000);
  // delay(1000);
}
