#pragma once

#include <Servo.h>
#include <Arduino.h>
#include <Wire.h>



#define dribbleTrue 23 //suckTrue 46  Mega: whether the ball is being dribbled
#define shootTrue 22 //shoot 3  ESP: decide to shoot
#define shootDire 24 //shootDire 20   ESP: which direction to shoot
#define revolveTrue 25 //revolveTrue 19   ESP: decide to revolve
#define readyToGo 26 //alreadyRevolve 13  Mega: whether completed revolve

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