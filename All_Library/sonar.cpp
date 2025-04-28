#include "sonar.h"


//const int ping_cycle = PING_INTERVAL * (SONAR_NUM + 1);
// +1 用于显示结果的计时器
const int ping_cycle = PING_INTERVAL * SONAR_NUM;
unsigned long ping_timer[SONAR_NUM + 1]; 
//存储超声波距离。

sonarData ultra;
int filteredSonar[4];
const int address[4] = {0x68,0x69,0x6A,0x6B};

// void change_dis(uint8_t bus) {
//   if (bus > 7) return;
//   Wire.begin();//开启iic设备总线，mpu6050类必须先开启总线，对于LCD显示屏这行代码可有可无
//   Wire.beginTransmission(BUS);//向tca9548建立通信
//   Wire.write(1 << bus);//向iic总线写入tca9548选择连通的地址（0~7接口）
//   Wire.endTransmission(); //关闭通信
// }
void setup_sonar(){
  Wire.begin(I2C_SDA,I2C_SCL);
  ping_timer[0] = millis() + 75;
  for (uint8_t i = 0; i < SONAR_NUM; i++) {
    ping_timer[i+1] = ping_timer[i] + PING_INTERVAL;
  }

}
void wait(int num,double thre,int waitTime){
  while(ultra.cm[num] == 0) getSonarData();
  while(1){
    getSonarData();
    Serial.println(ultra.cm[num]);
    if(ultra.cm[num] < thre && ultra.cm[num] != -1){
      Serial.println("begin!");
      delay(waitTime);
      return;
    }
  }
  
}
void trigger(int num){
 // change_dis(num);
  Wire.beginTransmission(address[num]);
  Wire.write(0x10);     
  Wire.write(0xB8);      
  Wire.endTransmission();
}
int echo(int num){
  //change_dis(num);
  Wire.beginTransmission(address[num]);
  Wire.write(0x02);          
  Wire.endTransmission();
  Wire.requestFrom(address[num],2);
  byte buffer[2];
  int16_t result;
  while (Wire.available()) {
   // Serial.println("ok");
    buffer[0] = Wire.read(); 
    buffer[1] = Wire.read();   
  }
  /*
  Serial.print(result);
  Serial.println("mm");
  */
  //   Wire.requestFrom(0x74,1);
  // while (int length = Wire.available()) {
  //   buffer[1] = Wire.read();        		
  // }
  result = 0;
  result = ((int16_t)buffer[0]<<8) + (int16_t)buffer[1];
  // if(result > 0){
  //   Serial.print(result);
  //   Serial.println("mm ");
  //   data[num-2] = result;
  // }
  return result;
}
void period(){
  for (uint8_t i = 0; i < SONAR_NUM; i++) {
    int dis = echo(i);
    //Serial.print(echo(i));
    if(dis > 0){
      ultra.cm[i] = dis;
      filteredSonar[i] = sonarFilter[i].update(ultra.cm[i]);
    }
    // Serial.print(ultra.cm[i]);
    // Serial.print(" ");
  }
  // Serial.println();
}
sonarData getSonarData(){
  for (uint8_t i = 0;i <= SONAR_NUM;i++){
    // Serial.print(i);
    // Serial.print(" ");
    // Serial.print(millis());
    // Serial.println();
    if(millis() >= ping_timer[i]){
      if(i == SONAR_NUM){
        ping_timer[i] += readInterval;
        period();
      }
      else{
        ping_timer[i] += ping_cycle;
        trigger(i);
      }
      
    }
  }
  return ultra;
}
int getAngle(int num){
  //change_dis(num);
  Wire.beginTransmission(address[num]);
  Wire.write(0x07);
  Wire.endTransmission();
  Wire.requestFrom(address[num],1);
  byte angle;
  while(Wire.available()){
 //   Serial.println("ok2");
    angle = Wire.read();  
    //Serial.println(a);
  }
  return angle;
}
void setAngle(int num,int level){
//  change_dis(num);
  Wire.beginTransmission(address[num]);
  Wire.write(0x07);     
  Wire.write(level); //angle
  Wire.endTransmission();
}
void setAddress(int num,int addr){
 // change_dis(num);
  Wire.beginTransmission(0x6A);
  Wire.write(0x05);     
  Wire.write(addr);      
  Wire.endTransmission();
}
int getAddress(int num){
 // change_dis(num);
  Wire.beginTransmission(address[num]);
  Wire.write(0x05);     
  Wire.endTransmission();
  Wire.requestFrom(address[num],1);
  int add;
  while(Wire.available()){
    add = Wire.read();
    Serial.println(add, HEX);
  }
  return add;
}