#include "dribble.h"

Servo esc;  // 创建Servo对象控制电调
const int escPin = 13;
const int minThrottle = 1000;  // 最小油门（微秒）
const int maxThrottle = 2000;  // 最大油门（微秒）

void setup_dribble(){
  Serial.println("Attaching ESC...");
  esc.attach(escPin, minThrottle, maxThrottle);
  Serial.println("Arming ESC...");
  esc.writeMicroseconds(minThrottle);
  delay(2000);  // 等待电调初始化
  
  Serial.println("ESC Ready!");
  pinMode(graySuck,INPUT);
  pinMode(dribbleTrue,OUTPUT);
}

void spin(int num){ //0-1000 1000-2000 different direction
  esc.writeMicroseconds(num);
}

void suck(){
  int val = analogRead(graySuck);
  Serial.println(val);

  if(val <= threshold){
    Serial.println("ball");
    digitalWrite(dribbleTrue,HIGH);
    spin(1600);
  }
  else{
    digitalWrite(dribbleTrue,LOW);
    spin(1000);
  }
}