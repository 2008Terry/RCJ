#include <NewPing.h>
#include <SPI.h>
#include "sonar.h"

#define RS04_1_TRIG 10//前
#define RS04_1_ECHO 9
#define RS04_2_TRIG 5//左
#define RS04_2_ECHO 4
#define RS04_3_TRIG 7//右
#define RS04_3_ECHO 6
#define RS04_4_TRIG 12//后
#define RS04_4_ECHO 11




//这里修改传感器个数
#define SONAR_NUM 4
//软件上设置超声波能够探测的最大距离
#define MAX_DISTANCE 240
//每个传感器 ping 之间的间隔为 35 毫秒（35 毫秒是避免跨传感器回声的最小值）
#define PING_INTERVAL 35 

const int ping_cycle = PING_INTERVAL * (SONAR_NUM + 1);
// +1 用于显示结果的计时器
unsigned long ping_timer[SONAR_NUM + 1]; 
//存储超声波距离。

//记录哪个传感器处于活动状态。
uint8_t current_sensor = 0;

NewPing sonar[SONAR_NUM] = {
  NewPing(RS04_1_TRIG, RS04_1_ECHO, MAX_DISTANCE),//front
  NewPing(RS04_2_TRIG, RS04_2_ECHO, MAX_DISTANCE),//left
  NewPing(RS04_3_TRIG, RS04_3_ECHO, MAX_DISTANCE),//right
  NewPing(RS04_4_TRIG, RS04_4_ECHO, MAX_DISTANCE)//back
//这里添加传感器
};

sonarData ultra;
/**
 * @brief 计时器中断方式循环显示超声波数据的函数
 * 
 
 */
void one_sensor_cycle() { 
  //Front:0  Left:1  Right:2  Back:3
  for (uint8_t i = 0; i < SONAR_NUM; i++) {
    Serial.print("ping");
    Serial.print(i);
    Serial.print(" ");
    Serial.print(ultra.cm[i]);
    Serial.print("\t");
  }
  Serial.println();
}

void echo_check() {
  if (sonar[current_sensor].check_timer()) { 
    ultra.cm[current_sensor] = sonar[current_sensor].convert_cm(sonar[current_sensor].ping_result);
  }
}

sonarData getSonarData(){
  for (uint8_t i = 0; i <= SONAR_NUM; i++) {
    if (millis() >= ping_timer[i]) {    
      ping_timer[i] += ping_cycle; 
      if (i == SONAR_NUM) one_sensor_cycle();
      else {
        sonar[current_sensor].timer_stop();
        current_sensor = i;
        sonar[current_sensor].ping_timer(echo_check);
      }
    }
  }
  return ultra;
}