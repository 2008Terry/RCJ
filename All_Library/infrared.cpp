#include "infrared.h"

void setup_infra(){
  Wire.begin(FSDA,FSCL);
  Wire1.begin(BSDA,BSCL);
}

int maxChannel(TwoWire *wire){
 // tcaselect(num);
  wire->beginTransmission(0x01);
  wire->write(14); 
  wire->write(8); 
  wire->endTransmission();
  wire->requestFrom(0x01,1);    // request 6 bytes from slave device #8
  int c;
  while (wire->available()) { // slave may send less than requested
    c = wire->read(); // receive a byte as character
   // Serial.println(c);         // print the character
  }
  return c;
}
int maxNum(TwoWire *wire){
 // tcaselect(num);
  wire->beginTransmission(0x01);
  wire->write(14); 
  wire->write(9); 
  wire->endTransmission();
  wire->requestFrom(0x01,1);    // request 6 bytes from slave device #8
  int c;
  while (wire->available()) { // slave may send less than requested
    c = wire->read(); // receive a byte as character
  //  Serial.println(c);         // print the character
  }
  return c;
}

// void tcaselect(uint8_t bus) {
//     if (bus > 7) return;
//     Wire.begin();//开启iic设备总线，mpu6050类必须先开启总线，对于LCD显示屏这行代码可有可无
//     Wire.beginTransmission(TCAADDR);//向tca9548建立通信
//     Wire.write(1 << bus);//向iic总线写入tca9548选择连通的地址（0~7接口）
//     Wire.endTransmission(); //关闭通信
//     /*
//     Serial.print("  /bus:");
//     Serial.print(bus);
//     Serial.print(":");
//     */
// }

int channelNum(int t, TwoWire *wire){
 // tcaselect(num);
  wire->beginTransmission(0x01);
  wire->write(14); 
  wire->write(t); 
  wire->endTransmission();
  wire->requestFrom(0x01,1);
  int c;
  while (wire->available()) { // slave may send less than requested
    c = wire->read(); // receive a byte as character
  //  Serial.println(c);         // print the character
  }
  return c;
}
void printInfrared(){
  //Serial.print("信号强度：");
  Serial.print("1 ");
  Serial.print(maxChannel(&Wire));
  Serial.print(" ");
  Serial.println(maxNum(&Wire));
 // Serial.print("第一块板子通道号：");
  
//  Serial.println();
 // Serial.print("信号强度：");
  // Serial.print("2 ");
  // Serial.print(maxChannel(&Wire1));
  // Serial.print(" ");
  // Serial.println(maxNum(&Wire1));
 // Serial.print("第二块板子通道号：");
  
 // Serial.println();
}
