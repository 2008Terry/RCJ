#include "MegaMotor.h"



const float kp = 8e-2,ki = 1.3e-5,kd = 5,dt = 1.5,turnCoe = 90;
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




// void staticLock(float lockDegree){
//   Serial.println(digitalRead(revolveTrue));
//   if(digitalRead(revolveTrue) == HIGH){
//     float theta = 0,diff = lockDegree-theta;
//     if(diff)
//     while(abs(diff) > 5){
//       while (Serial1.available()) {
//         char c = Serial1.read();
//         packet_decode(c);
//       }
//       theta = receive_imusol.eul[2];
//       Serial.println(theta);
//       int coe = (theta>0?-1:1);
//       float control[4] = {coe*speed,coe*speed,coe*speed,coe*speed};
//       Encoder_Control(control);
//       diff = lockDegree-theta
//     }
//     int32_t init = millis();
//     while(millis()-init <= 100){
//       float control[4] = {0,0,0,0};
//       Encoder_Control(control);
//     }
//     digitalWrite(readyToGo,HIGH);
//     alreadyRevolve = 1;
//   }

// }


bool alreadyRevolve = 0;
void offenceRevolve(int speed){
  if(alreadyRevolve) return;
  Serial.println(digitalRead(revolveTrue));
  if(digitalRead(revolveTrue) == HIGH){
    float theta = 0;
    while(180-abs(theta) > 5){
      while (Serial1.available()) {
        char c = Serial1.read();
        packet_decode(c);
      }
      theta = receive_imusol.eul[2];
      Serial.println(theta);
      int coe = (theta>0?-1:1);
      float control[4] = {coe*speed,coe*speed,coe*speed,coe*speed};
      Encoder_Control(control);
    }
    int32_t init = millis();
    while(millis()-init <= 100){
      float control[4] = {0,0,0,0};
      Encoder_Control(control);
    }
    digitalWrite(readyToGo,HIGH);
    alreadyRevolve = 1;
  }
}
void shoot(bool clockwise,int constSpin, int speed,int shotDegree,int spinDegree,int32_t waitTime){ //better shooting after sucking for 3 seconds!!
  /*
  clockwise -> which way to shoot
  speed -> backward speed to separate the ball
  shotDegree -> shoot at what degree
  waitTime -> how much time to wait after the shooting
  */
  int32_t stopmillis = 0x7f7f7f7f;
  bool alreadyShoot = 0;
  while(1){
    while (Serial1.available()) {
      char c = Serial1.read();
      packet_decode(c);
    }
    float theta = receive_imusol.eul[2];
    // Serial.println(theta);
    float accel = (180-abs(theta))*340;
    float v1 = -sqrt(2)*speed, v2 = sqrt(2)*speed, v3 = sqrt(2)*speed, v4 = -sqrt(2)*speed;
    if(clockwise){
      float control[4] = {v1+accel+constSpin,v2+accel+constSpin,v3+accel+constSpin,v4+accel+constSpin};
      if(alreadyShoot) for (int i = 0;i < 4;i++) control[i] = 0;
      if(theta < shotDegree && theta > 0){ //at shotDegree, shoot!
        dribbleSpeed = 1000;
        spin(dribbleSpeed);
        alreadyShoot = 1;
        stopmillis = min(stopmillis,millis());
        if(theta < spinDegree) for (int i = 0;i < 4;i++) control[i] = 0;
        if(millis() - stopmillis > waitTime) return;
      }
      Encoder_Control(control);
    }
    else{
      float control[4] = {v1-accel-constSpin,v2-accel-constSpin,v3-accel-constSpin,v4-accel-constSpin};
      if(alreadyShoot) for (int i = 0;i < 4;i++) control[i] = 0;
      if(-1*shotDegree < theta && theta < 0){ //at shotDegree, shoot!
        dribbleSpeed = 1000;
        spin(dribbleSpeed);
        alreadyShoot = 1;
        stopmillis = min(stopmillis,millis());
        if(theta < spinDegree) for (int i = 0;i < 4;i++) control[i] = 0;
        if(millis() - stopmillis > waitTime) return;
      }
      Encoder_Control(control);
    }
  }
}


float moveDire = 0;
void obeyBallMove(){ //lock dribbler toward ball
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


const double maxError = 0.001;
bool equal(double a,double b){
  return abs(a-b) <= maxError;
}

int32_t nodata = 200,stop = 0;
const int32_t stopThre = 20;
void obeyLock(int speed,int interval){ 
  /*offence code, move with 4 direction locked
  speed -> puremove speed, in speed of wheels
  interval -> move how long, in ms
  */
  float theta = receive();
  //Serial.println(theta);
  if(theta != -1){
    Serial.print("theta ");
    Serial.println(theta);
  }
  // return;
  if(theta == -1){
    nodata++;
    //Serial.println(nodata);
    if(nodata > 50){ // be aware of the range of nodata!!
      if(0 <= moveDire && moveDire < 7) theta = 6.8;
      else if(7 <= moveDire && moveDire < 14) theta = 13.8;
      else if(14 <= moveDire && moveDire < 21) theta = 20.8;
      else if(21 <= moveDire && moveDire < 28) theta = 27.8;
    }
    else{
      if(0 <= moveDire && moveDire < 7) theta = 6.5;
      else if(7 <= moveDire && moveDire < 14) theta = 13.5;
      else if(14 <= moveDire && moveDire < 21) theta = 20.5;
      else if(21 <= moveDire && moveDire < 28) theta = 27.5;
    }
  }
  else{
    nodata = 0;
    moveDire = theta;
    if(0 <= theta && theta <= 2*M_PI ||
    7 <= theta && theta <= 7+2*M_PI ||
    14 <= theta && theta <= 14+2*M_PI ||
    21 <= theta && theta <= 21+2*M_PI){
      
      stop = abs(stop-1);
    }
    if(equal(theta,6.9) || equal(theta,13.9) || 
    equal(theta,20.9) || equal(theta,27.9)) stop++;
  }
  
  if(0 <= moveDire && moveDire < 7){
    // Serial.print("theta2  ");
    // Serial.print(theta);
    // Serial.print(" ");
    // Serial.println(moveDire);
    
    if(stop > stopThre || theta == 6.8 || equal(theta,6.9)){
      //Serial.println("ok");
      pureMove(0,0,0,1);
      return -1;
    }
    else if(equal(theta,6.95)){
      pureMove(0,0,0,interval);
    }
    else if(theta == 6.5){
      pureMove(0,moveDire,speed,1);
      return moveDire;
    }
    else{
      pureMove(0,moveDire,speed,interval);
      return moveDire;
    }
  }
  else if(7 <= moveDire && moveDire < 14){
    if(stop > stopThre || theta == 13.8 || equal(theta,13.9)){
      pureMove(90,0,0,1);
      return -1;
    }
    else if(equal(theta,13.95)){
      pureMove(90,0,0,interval);
    }
    else if(theta == 13.5){
      pureMove(90,moveDire-7,speed,1);
      return moveDire-7;
    }
    else{
      pureMove(90,moveDire-7,speed,interval);
      return moveDire-7;
    }
  }
  else if(14 <= moveDire && moveDire < 21){
    if(stop > stopThre || theta == 20.8 || equal(theta,20.9)){
      pureMove(180,0,0,1);
      return -1;
    }
    else if(equal(theta,20.95)){
      Serial.println("ok");
      pureMove(180,0,0,interval);
    }
    else if(theta == 20.5){
      pureMove(180,moveDire-14,speed,1);
      return moveDire-7;
    }
    else{
      pureMove(180,moveDire-14,speed,interval);
      return moveDire-7;
    }
  }
  else if(21 <= moveDire && moveDire < 28){
    if(stop > stopThre || theta == 27.8 || equal(theta,27.9)){
      pureMove(-90,0,0,1);
      return -1;
    }
    else if(equal(theta,27.95)){
      pureMove(-90,0,0,interval);
    }
    else if(theta == 27.5){
      pureMove(-90,moveDire-21,speed,1);
      return moveDire-7;
    }
    else{
      pureMove(-90,moveDire-21,speed,interval);
      return moveDire-7;
    }
  }
}




float obeyMove(){ //useless?
  float theta = receive();
  if(theta == -1){
    nodata++;
    Serial.println(nodata);
    if(nodata > 50){
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
    Serial.println(theta);
    if(theta == 6.5){
      pureMove(0,moveDire,2064,1);
      return moveDire;
    }
    else if(theta == 6.8){
      pureMove(0,0,0,1);
      return -1;
    }
    else{
      pureMove(0,moveDire,2064,8);
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

void moveToBall(float cita,float speed,int duration){ //move toward ball, called by obeyBallMove()
  /*
  cita -> ballDire in radian
  speed -> total speed, in speed of wheels 
  duration -> how much time to move
  */
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
    // if(speed == 0){
    //   for (int i = 0;i < 4;i++) control[i] = 0;
    // }
    Encoder_Control(control);//1.5ms
  }
}
void maxPureMove(float cita,float maxSpeed,int duration){ //useless? to move at maximum speed at all direction
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
void pureMove(float lock, float cita,float speed,int duration){
  /*
  lock -> lock at which direction to move: 0front 90left 180back -90right
  cita -> local move direction, in radian
  speed -> robot total speed
  duration -> move how long
  */
  float vx = speed*cos(cita), vy = speed*sin(cita),
  v1 = sqrt(2)*(vx+vy), v2 = sqrt(2)*(vx-vy), v3 = -sqrt(2)*(vx+vy), v4 = -sqrt(2)*(vx-vy);
  int32_t itime = millis();
 // Serial.println(itime);
  while(itime+duration >= millis()){
   // Serial.println(millis());
    while (Serial1.available()) {
      char c = Serial1.read();
      packet_decode(c);
    }
    float delta_cita = receive_imusol.eul[2]-lock;
    if(delta_cita > 180) delta_cita -= 360;
    if(delta_cita < -180) delta_cita += 360;
  //  Serial.println(delta_cita);
    float turn = delta_cita*turnCoe;
    float control[4] = {v1+turn, v2+turn, v3+turn, v4+turn};


    // Serial.print("speed ");
    // Serial.println(speed);
    // for (int i = 0;i < 4;i++){
    //   Serial.print(control[i]);
    //   Serial.print(" ");
    // }
    // Serial.println();
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
    uint8_t result = mcp2515.readMessage(&canMsg_IN);
    Serial.println(result);
    if (mcp2515.readMessage(&canMsg_IN) == MCP2515::ERROR_OK) {
      Serial.print(canMsg_IN.can_id, HEX);
      Serial.print(" motor\n");
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
