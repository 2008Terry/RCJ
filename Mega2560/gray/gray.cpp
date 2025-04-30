#include "gray.h"
#include <Arduino.h>

grayInfo getGray(){
  int Lval[4],Rval[4],Bval[4];
  Lval[0] = digitalRead(Lout1),Lval[1] = digitalRead(Lout2),Lval[2] = digitalRead(Lout3),Lval[3] = digitalRead(Lout4);
  Rval[0] = digitalRead(Rout1),Rval[1] = digitalRead(Rout2),Rval[2] = digitalRead(Rout3),Rval[3] = digitalRead(Rout4);
  Bval[0] = digitalRead(Bout1),Bval[1] = digitalRead(Bout2),Bval[2] = digitalRead(Bout3),Bval[3] = digitalRead(Bout4);
  grayInfo obj = {0,0,0};
  for (int i = 0;i < 4;i++){
    if(Lval[i] < white) obj.l++;
  }
  for (int i = 0;i < 4;i++){
    if(Rval[i] < white) obj.r++;
  }
  for (int i = 0;i < 4;i++){
    if(Bval[i] < white) obj.b++;
  }
  Serial.print(obj.l);
  Serial.print(" ");
  Serial.print(obj.r);
  Serial.print(" ");
  Serial.print(obj.b);
  Serial.print(" ");
  return obj;
}