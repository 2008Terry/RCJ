#include "dribble.h"

Servo esc;  // 创建Servo对象控制电调
const int escPin = 13;
const int minThrottle = 1000;  // 最小油门（微秒）
const int maxThrottle = 2000;  // 最大油门（微秒）

void setup_dribble(){
  Wire.begin();
  Serial.println("Attaching ESC...");
  esc.attach(escPin, minThrottle, maxThrottle);
  Serial.println("Arming ESC...");
  esc.writeMicroseconds(minThrottle);
  delay(2000);  // 等待电调初始化
  
  Serial.println("ESC Ready!");
  pinMode(dribbleTrue,OUTPUT);
  pinMode(shootTrue,INPUT);
  pinMode(shootDire,INPUT);
  pinMode(revolveTrue,INPUT);
  pinMode(readyToGo,OUTPUT);
  delay(500);
}

void trigger(){
 // change_dis(num);
  Wire.beginTransmission(0x74);
  Wire.write(0x10);
  Wire.write(0xBD);
  Wire.endTransmission();
}
int echo(){
  Wire.beginTransmission(0x74);
  Wire.write(0x02);          
  Wire.endTransmission();
  Wire.requestFrom(0x74,2);
  byte buffer[2];
  int16_t result;
  while (Wire.available()) {
    buffer[0] = Wire.read(); 
    buffer[1] = Wire.read();   
  }
  result = 0;
  result = ((int16_t)buffer[0]<<8) + (int16_t)buffer[1];
  return result;
}
int dis = 10000;
int getSonar(){
  int val = echo();
  if(dis == 10000) trigger(); //the start of getSoar
  if(val == -1) return dis;
  else if(val < 0){
    trigger();
    return dis;
  }
  else{
    trigger();
    return dis = val;
  }
}

void spin(int num){ //0-1000 1000-2000 different direction
  esc.writeMicroseconds(num);
}

int dribbleSpeed = 1000;
const int suckThre = 200,dribbleThre = 40; //dis <= suckThre, suck ; dis <= dribbleThre, send to ESP32, dribbleTrue
int32_t dribbleTime,notDribbleTime,outRangeTime; //record time to identify condition
const int32_t timeThre = 300; //larger than this threshold -> true, change condition(dribble?suck?)
bool ready = 0,last = 0,range = 0;//record condition
void suck(int speed){
  getSonar();
  Serial.println(dis);
  if(dis <= suckThre){
    dribbleSpeed = speed;
    if(dis <= dribbleThre){
      if(last == 0 && ready == 0) dribbleTime = millis();
      if(millis() - dribbleTime > timeThre){
        digitalWrite(dribbleTrue,HIGH);
        Serial.println("dribble!");
        ready = 1;
      }
      last = 1;
    }
    else{
      if(last == 1 && ready == 1) notDribbleTime = millis();
      if(millis() - notDribbleTime > timeThre){
        digitalWrite(dribbleTrue,LOW);
        ready = 0;
      }
      last = 0;
    }
    range = 1;
  }
  else{
    if(range == 1) outRangeTime = millis();
    if(millis() - outRangeTime > timeThre){
      digitalWrite(dribbleTrue,LOW);
      dribbleSpeed = 1000;
    }
    range = 0;
  }
  spin(dribbleSpeed);


  // int val = analogRead(graySuck);
  // Serial.println(val);
  // if(val <= threshold){
  //   digitalWrite(dribbleTrue,HIGH);
  //   spin(1400);
  // }
  // else{
  //   digitalWrite(dribbleTrue,LOW);
  //   spin(1000);
  // }
}