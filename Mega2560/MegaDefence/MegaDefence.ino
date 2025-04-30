#include "packet.h"
#include "imu_data_decode.h"
#include "MegaMotor.h"
#include "gray.h"
#include "correMega.h"
#include "dribble.h"



void setup() {
  Serial.begin(115200);
  setup_correMega();
  setup_MegaMotor();
}

void loop() {
  obeyLock(2000,10);
}
