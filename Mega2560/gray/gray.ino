#include "gray.h"


void setup() {
  Serial.begin(115200);
  pinMode(Lout1,INPUT);
  pinMode(Lout2,INPUT);
  pinMode(Lout3,INPUT);
  pinMode(Lout4,INPUT);
  pinMode(Rout1,INPUT);
  pinMode(Rout2,INPUT);
  pinMode(Rout3,INPUT);
  pinMode(Rout4,INPUT);
  pinMode(Bout1,INPUT);
  pinMode(Bout2,INPUT);
  pinMode(Bout3,INPUT);
  pinMode(Bout4,INPUT);
}


void loop() {
  //getGray();
  int val = analogRead(Lout1);
  Serial.println(val);
}
