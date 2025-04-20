#include "gray.h"

grayInfo getGray(){
  int Lval[4],Rval[4],Bval[4];
  Lval[0] = analogRead(Lout1),Lval[1] = analogRead(Lout2),Lval[2] = analogRead(Lout3),Lval[3] = analogRead(Lout4);
  Rval[0] = analogRead(Rout1),Rval[1] = analogRead(Rout2),Rval[2] = analogRead(Rout3),Rval[3] = analogRead(Rout4);
  Bval[0] = analogRead(Bout1),Bval[1] = analogRead(Bout2),Bval[2] = analogRead(Bout3),Bval[3] = analogRead(Bout4);
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