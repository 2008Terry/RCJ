#include "infrared.h"


int JMP_BEnum(){
  Wire.beginTransmission(0x01);
  Wire.write(14); 
  Wire.write(8); 
  Wire.endTransmission();
  Wire.requestFrom(0x01,1);    // request 6 bytes from slave device #8
  int c;
  while (Wire.available()) { // slave may send less than requested
    c = Wire.read(); // receive a byte as character
    Serial.println(c);         // print the character
  }
  return c;
}
int JMP_BEstr(){
  Wire.beginTransmission(0x01);
  Wire.write(14); 
  Wire.write(9); 
  Wire.endTransmission();
  Wire.requestFrom(0x01,1);    // request 6 bytes from slave device #8
  int c;
  while (Wire.available()) { // slave may send less than requested
    c = Wire.read(); // receive a byte as character
    Serial.println(c);         // print the character
  }
  return c;
}

void tcaselect(uint8_t bus) {
    if (bus > 7) return;
    Wire.begin();//开启iic设备总线，mpu6050类必须先开启总线，对于LCD显示屏这行代码可有可无
    Wire.beginTransmission(TCAADDR);//向tca9548建立通信
    Wire.write(1 << bus);//向iic总线写入tca9548选择连通的地址（0~7接口）
    Wire.endTransmission(); //关闭通信
    /*
    Serial.print("  /bus:");
    Serial.print(bus);
    Serial.print(":");
    */
}

void printInfrared(){
  tcaselect(0);//1号
  //Serial.print("信号强度：");
  Serial.print("1 ");
  JMP_BEnum();
  JMP_BEstr();
 // Serial.print("第一块板子通道号：");
  
//  Serial.println();
  tcaselect(1);//2号
 // Serial.print("信号强度：");
 // Serial.print("2 ");
//  JMP_BEnum();
 // JMP_BEstr();
 // Serial.print("第二块板子通道号：");
  
  Serial.println();
}
