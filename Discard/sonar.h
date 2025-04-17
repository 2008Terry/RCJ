#ifndef SONAR_H
#define SONAR_H


/*
imports:
#include <NewPing.h>
#include <SPI.h>

setup:
ping_timer[0] = millis() + 75;
for (uint8_t i = 0; i < SONAR_NUM; i++) {
  ping_timer[i+1] = ping_timer[i] + PING_INTERVAL;
}
*/

#define SUDDEN_THRESHOLD 30 // 数据突然变化的阈值，默认为20cm


//这里修改传感器个数
#define SONAR_NUM 4
//软件上设置超声波能够探测的最大距离
#define MAX_DISTANCE 240
//每个传感器 ping 之间的间隔为 35 毫秒（35 毫秒是避免跨传感器回声的最小值）
#define PING_INTERVAL 35 

// +1 用于显示结果的计时器
extern unsigned long ping_timer[SONAR_NUM + 1]; 
//存储超声波距离。
struct sonarData{
  unsigned int cm[SONAR_NUM];
};
//记录哪个传感器处于活动状态。
extern uint8_t current_sensor;

extern NewPing sonar[SONAR_NUM];


void one_sensor_cycle();
void echo_check();
sonarData getSonarData();
#endif

