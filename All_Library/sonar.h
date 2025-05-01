#pragma once


#include <Wire.h>
#include <Arduino.h>
#include "KalmanFilter.h"

// #define BUS  0x70 //这个是测距的BUS 看你们设成什么地址自己写
// #define deviceAddress 0x74

#define I2C_SDA 11
#define I2C_SCL 12
//这里修改传感器个数
#define SONAR_NUM 4
//每个传感器 ping 之间的间隔为 35 毫秒（35 毫秒是避免跨传感器回声的最小值）
#define PING_INTERVAL 15 
#define readInterval 30

extern const int ping_cycle;
extern unsigned long ping_timer[SONAR_NUM + 1]; 
struct sonarData{
  int cm[SONAR_NUM];
};
extern sonarData ultra;
extern int filteredSonar[4];
extern const int address[4];
//void change_dis(uint8_t bus);
void setup_sonar();
void waitnum(int num, double thre,int waitTime);
int wait(double thre,int waitTime);
void trigger(int num);
int echo(int num);
void period();
sonarData getSonarData();
int getAngle(int num);
void setAngle(int num,int level);
void setAddress(int num,int addr);
int getAddress(int num);

