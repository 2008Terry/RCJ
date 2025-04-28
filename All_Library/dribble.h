#pragma once

#include <Servo.h>
#include <Arduino.h>
#include <Wire.h>



#define dribbleTrue 23
#define shootTrue 22


extern Servo esc;  // 创建Servo对象控制电调
extern const int escPin;
extern const int minThrottle;  // 最小油门（微秒）
extern const int maxThrottle;  // 最大油门（微秒）

void setup_dribble();
void trigger();
int echo();
extern int dis;
int getSonar();
void spin(int num);

extern int dribbleSpeed;
extern const int suckThre,dribbleThre;
extern int32_t dribbleTime,notDribbleTime,outRangeTime;
extern const int32_t timeThre;
extern bool ready,last,range;

void suck(int speed);