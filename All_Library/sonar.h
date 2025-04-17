#pragma once

/*
imports:
#include <Wire.h>

setup:
Wire.begin();
ping_timer[0] = millis() + 75;
for (uint8_t i = 0; i < SONAR_NUM; i++) {
  ping_timer[i+1] = ping_timer[i] + PING_INTERVAL;
}
*/

#include <Wire.h>
#include <Arduino.h>


#define BUS  0x70 //这个是测距的BUS 看你们设成什么地址自己写
#define deviceAddress 0x74

//这里修改传感器个数
#define SONAR_NUM 4
//每个传感器 ping 之间的间隔为 35 毫秒（35 毫秒是避免跨传感器回声的最小值）
#define PING_INTERVAL 60 

extern const int ping_cycle;
extern unsigned long ping_timer[SONAR_NUM + 1]; 
struct sonarData{
  int cm[SONAR_NUM];
};
extern sonarData ultra;
extern const int address[4];
//void change_dis(uint8_t bus);
void trigger(int num);
int echo(int num);
void period();
sonarData getSonarData();
int getAngle(int num);
void setAngle(int num,int level);
void setAddress(int num,int addr);
int getAddress(int num);

