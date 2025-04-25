#include "MegaMotor.h"



const float kp = 8e-2,ki = 1.3e-5,kd = 5,dt = 1.5,turnCoe = 20;
//l:0 r:1 b:2
int v[4],actual_Speed[4];
float integral[4],derivative[4],error[4],pre_error[4];
//Left ID:1  Right ID:2  Back ID:3 


struct can_frame canMsg_OUT;
struct can_frame canMsg_IN;
MCP2515 mcp2515(53);

void setup_MegaMotor(){
  Serial1.begin(115200);
  canMsg_OUT.can_id = 0x200;
  canMsg_OUT.can_dlc = 8;
  imu_data_decode_init();
  mcp2515.reset();
  mcp2515.setBitrate(CAN_1000KBPS,MCP_8MHZ);
  mcp2515.setNormalMode();
  Serial.println("Example: Write to CAN");
}

float moveDire = 0;
void obeyBallMove(){
  float theta = receive();
  Serial.println(moveDire);
  if(theta == -1){
    moveToBall(moveDire,3000,1);
  }
  else{
    if(theta <= 1.5*M_PI) moveDire = theta-0.5*M_PI;
    else moveDire = theta-2.5*M_PI;
    moveToBall(moveDire,3000,4);
  }
}


int nodata = 200;
float obeyMove(){
  float theta = receive();
  if(theta == -1){
    nodata++;
    //Serial.println(nodata);
    if(nodata > 30){
      if(0 <= moveDire && moveDire < 7) theta = 6.8;
      else if(7 <= moveDire && moveDire < 14) theta = 13.8;
    }
    else{
      if(0 <= moveDire && moveDire < 7) theta = 6.5;
      else if(7 <= moveDire && moveDire < 14) theta = 13.5;
    }
  }
  else{
    nodata = 0;
    moveDire = theta;
  }
  if(0 <= theta && theta < 7){
    //Serial.println(theta);
    if(theta == 6.5){
      pureMove(moveDire,2000,1);
      return moveDire;
    }
    else if(theta == 6.8){
      pureMove(0,0,1);
      return -1;
    }
    else{
      pureMove(moveDire,2000,8);
      return moveDire;
    }
  }
  else if(7 <= theta && theta < 14){
    // Serial.print(theta);
    // Serial.print("  track ball\n");


    // float temp;
    // if(moveDire-7 <= 1.5*M_PI) temp = moveDire-7-0.5*M_PI;
    // else temp = moveDire-7-2.5*M_PI;
   // Serial.println(temp);
    if(theta == 13.5){
      moveToBall(moveDire-7,500,1);
      return moveDire-7;
    }
    else if(theta == 13.8){
      moveToBall(0,0,1);
      return -1;
    }
    else{
      moveToBall(moveDire-7,500,10);
      return moveDire-7;
    }
  }
}

void moveToBall(float cita,float speed,int duration){
  float vx = speed*cos(cita), vy = speed*sin(cita),
  v1 = sqrt(2)*(vx+vy), v2 = sqrt(2)*(vx-vy), v3 = -sqrt(2)*(vx+vy), v4 = -sqrt(2)*(vx-vy),turn;
  if(cita <= 1.5*M_PI) turn = (0.5*M_PI-cita)/M_PI*180*turnCoe;
  else turn = (2.5*M_PI-cita)/M_PI*180*turnCoe;
  int32_t itime = millis();
 // Serial.println(itime);
  while(itime+duration >= millis()){
    //lock direction? add gyro
    // float delta_cita = -cita/M_PI*180;
    // float turn = delta_cita*turnCoe;
    float control[4] = {v1+turn, v2+turn, v3+turn, v4+turn};
    if(speed == 0){
      for (int i = 0;i < 4;i++) control[i] = 0;
    }
    Encoder_Control(control);//1.5ms
  }
}
void maxPureMove(float cita,float maxSpeed,int duration){
  float vx = maxSpeed*cos(cita), vy = maxSpeed*sin(cita),
  v1 = sqrt(2)*(vx+vy), v2 = sqrt(2)*(vx-vy), v3 = -sqrt(2)*(vx+vy), v4 = -sqrt(2)*(vx-vy);
  int32_t itime = millis();
  while(itime+duration >= millis()){
    while (Serial1.available()) {
      char c = Serial1.read();
      packet_decode(c);
    }
    float delta_cita = receive_imusol.eul[2];
  //  Serial.println(delta_cita);
    float turn = delta_cita*turnCoe;
    float control[4] = {v1+turn, v2+turn, v3+turn, v4+turn};
    float maxv = 0;
    for (int i = 0;i < 4;i++){
      maxv = max(maxv,abs(control[i]));
    }
    float coe = maxSpeed/maxv;
    for (int i = 0;i < 4;i++){
      control[i] *= coe;
    }
    Encoder_Control(control);//1.5ms
  }
}
void pureMove(float cita,float speed,int duration){
 // Serial.println(cita);
  //Serial.print(" ");
  float origin_cita = cita;
  float vx = speed*cos(cita), vy = speed*sin(cita),
  v1 = sqrt(2)*(vx+vy), v2 = sqrt(2)*(vx-vy), v3 = -sqrt(2)*(vx+vy), v4 = -sqrt(2)*(vx-vy);
  // Serial.print(v1);
  // Serial.print(" ");
  // Serial.print(v2);
  // Serial.print(" ");
  // Serial.print(v3);
  // Serial.print(" ");
  // Serial.println(v4);
  int32_t itime = millis();
 // Serial.println(itime);
  while(itime+duration >= millis()){
   // Serial.println(millis());
    while (Serial1.available()) {
      char c = Serial1.read();
      packet_decode(c);
    }
    float delta_cita = receive_imusol.eul[2];
  //  Serial.println(delta_cita);
    float turn = delta_cita*turnCoe;
    float control[4] = {v1+turn, v2+turn, v3+turn, v4+turn};
   // float control[4] = {v1, v2, v3, v4};
    Encoder_Control(control);//1.5ms
  }
}

void moveWithGray(float cita,float speed,int duration){
  //float oricita = cita/180*M_PI,cita = oricita,realTheta;
  float oricita = cita,realTheta;
  int itime = millis();
  while(itime+duration <= millis()){
    grayInfo g = getGray();
    if(g.b > 0){
      if(M_PI <= oricita && oricita < 1.5*cita) cita = 170.0/180*M_PI;
      else if(1.5*M_PI <= oricita) cita = 10.0/180*M_PI;
    }
    else{
     if(g.l > 0 && g.r > 0){
        //if()
      }
      else if(g.l > 0){
        if(0.5*M_PI <= oricita && oricita < M_PI) cita = 80.0/180*M_PI;
        else if(M_PI <= oricita && oricita < 1.5*cita) cita = 280.0/180*M_PI;
      }
      else if(g.r > 0){
        if(oricita < 0.5*M_PI) cita = 100.0/180*M_PI;
        else if(1.5*M_PI <= oricita) cita = 260.0/180*M_PI;
      }
    }
    if(g.b == 0 && g.l == 0 && g.r == 0) realTheta = oricita;
    else realTheta = cita;
    float vx = speed*cos(realTheta), vy = speed*sin(realTheta),
    v1 = sqrt(2)*(vx+vy), v2 = sqrt(2)*(vx-vy), v3 = -sqrt(2)*(vx+vy), v4 = -sqrt(2)*(vx-vy);
    while (Serial1.available()) {
      char c = Serial1.read();
      packet_decode(c);
    }
    float delta_cita = receive_imusol.eul[2];
    float turn = delta_cita*200;
    float control[4] = {v1+turn, v2+turn, v3+turn, v4+turn};
    Encoder_Control(control);//1.5ms
  }
}


void Encoder_Control(float goal[4]){
  bool tf[4] = {0,0,0,0};
  while(!(tf[0] && tf[1] && tf[2] && tf[3])){
    //Serial.println("stuck");
    // uint8_t result = mcp2515.readMessage(&canMsg_IN);
    // Serial.println(result);
    if (mcp2515.readMessage(&canMsg_IN) == MCP2515::ERROR_OK) {
     //  Serial.print(canMsg_IN.can_id, HEX);
      // Serial.print(" motor\n");
      actual_Speed[canMsg_IN.can_id-0x200-1] = ((uint16_t)canMsg_IN.data[2]<<8) + canMsg_IN.data[3];
      tf[canMsg_IN.can_id-0x200-1] = 1;
      //Serial.println(tf[2]);
    }
  }
  //Serial.println("ok");
  for (int i = 0;i < 4;i++){
    // Serial.print(actual_Speed[i]);
    // Serial.print(" ");
    error[i] = goal[i]-actual_Speed[i];
    integral[i] += error[i]*dt;
    derivative[i] = (error[i]-pre_error[i])/dt;
    v[i] += error[i]*kp + integral[i]*ki + derivative[i]*kd;
    if(v[i] >= 10000) v[i] = 10000;
    else if (v[i] <= -10000) v[i] = -10000;
  }

  //Left ID:1
  canMsg_OUT.data[0] = (v[0]>>8);
  canMsg_OUT.data[1] = v[0];
  //Right ID:2
  canMsg_OUT.data[2] = (v[1]>>8);
  canMsg_OUT.data[3] = v[1];
  //Back ID:3
  canMsg_OUT.data[4] = (v[2]>>8);
  canMsg_OUT.data[5] = v[2];
  //ID:4 doesn't represent anything
  canMsg_OUT.data[6] = (v[3]>>8);
  canMsg_OUT.data[7] = v[3];
  mcp2515.sendMessage(&canMsg_OUT);
 // Serial.println("sent");
  for (int i = 0;i < 4;i++) pre_error[i] = error[i];
}
