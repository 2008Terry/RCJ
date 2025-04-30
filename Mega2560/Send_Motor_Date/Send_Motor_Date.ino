#include <SPI.h>
#include <mcp2515.h>

struct can_frame canMsg1;
MCP2515 mcp2515(53);
int16_t current_L = 400,current_R = 0,current_B = -0,current = -0;

void setup(){
  canMsg1.can_id = 0x200;
  canMsg1.can_dlc = 8;
  //Left ID:1
  canMsg1.data[0] = (current_L>>8);
  canMsg1.data[1] = current_L;
  //Right ID:2
  canMsg1.data[2] = (current_R>>8);
  canMsg1.data[3] = current_R;
  //Back ID:3
  canMsg1.data[4] = (current_B>>8);
  canMsg1.data[5] = current_B;
  //ID:4 doesn't represent anything
  canMsg1.data[6] = (current>>8);
  canMsg1.data[7] = current;
  while(!Serial);
  Serial.begin(115200);
  mcp2515.reset();
  mcp2515.setBitrate(CAN_1000KBPS,MCP_8MHZ);
  mcp2515.setNormalMode();
  Serial.println("Example: Write to CAN");
}
void loop(){
  mcp2515.sendMessage(&canMsg1);
  Serial.println("Messages sent");
  delay(1);
}