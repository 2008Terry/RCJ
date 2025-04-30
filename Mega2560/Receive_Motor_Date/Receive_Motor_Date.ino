#include <SPI.h>
#include <mcp2515.h>

struct can_frame canMsg;
MCP2515 mcp2515(53);


void setup() {
  Serial.begin(115200);
  mcp2515.reset();
  mcp2515.setBitrate(CAN_1000KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();
}
void loop() {
  Serial.println("ok");
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
    Serial.print(canMsg.can_id, HEX);
    Serial.print(" ");
    Serial.print(canMsg.can_dlc, HEX);
    Serial.print(" ");
    

    Serial.print("转子机械角度： ");
    int result_angle = ((uint16_t)canMsg.data[0]<<8) + canMsg.data[1];
    Serial.print(result_angle,DEC);
    Serial.print("; ");

    Serial.print("转子转速： ");
    int result_speed = ((uint16_t)canMsg.data[2]<<8) + canMsg.data[3];
    Serial.print(result_speed,DEC);
    Serial.print("; ");

    Serial.print("实际输出转矩： ");
    
    int result_torque = ((uint16_t)canMsg.data[4]<<8) + canMsg.data[5];
    Serial.print(result_torque,DEC);
    Serial.print("; ");
    Serial.println();
  }
  delay(100);
}
