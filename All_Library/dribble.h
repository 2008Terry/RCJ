#pragma once

#include <Servo.h>
#include <Arduino.h>

#define graySuck A0
#define dribbleTrue A1
#define threshold 390


extern Servo esc;  // 创建Servo对象控制电调
extern const int escPin;
extern const int minThrottle;  // 最小油门（微秒）
extern const int maxThrottle;  // 最大油门（微秒）

void setup_dribble();
void spin(int num);
void suck();