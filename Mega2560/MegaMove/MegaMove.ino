#include "packet.h"
#include "imu_data_decode.h"
#include "MegaMotor.h"
#include "gray.h"
#include "correMega.h"



void setup() {
  Serial.begin(115200);

  
  setup_correMega();
  
  setup_MegaMotor();

  delay(1500);
}

int cita = 0;
void loop() {
  // while (Serial1.available()) {
  //   char c = Serial1.read();
  //   packet_decode(c);
  // }
  // float delta_cita = receive_imusol.eul[2];
  // Serial.println(delta_cita);

  // moveToBall(0,2000,1000);
  // delay(10);
  // moveToBall(1,2000,1000);
  // delay(10);
  // moveToBall(M_PI,2000,1000);
  // moveToBall(-0.5*M_PI,2000,1000);
  
  //obeyMove();

  // obeyLock(500,10);
  // pureMove(0,0.5*M_PI,800,1500);
  // pureMove(90,0.5*M_PI,800,1500);
  // pureMove(180,0.5*M_PI,800,1500);
  // pureMove(-90,0.5*M_PI,800,1500);


  // pureMove(0,2000,1000);
  // pureMove(M_PI,2000,1000);
  // maxPureMove(0,9000,1000);
  // maxPureMove(M_PI,9000,1000);
  
  // maxPureMove(0,2000,1000);
  // maxPureMove(M_PI,2000,1000);


  pureMove(0,cita/180.0*M_PI,2000,50);
  cita = (cita+10)%360;
  Serial.println(cita);
  // Serial.println(digitalRead(CAN_INT_PIN));


  // for (int i = 0;i < 4;i++){
  //   Serial.print(actual_Speed[i]);
  //   Serial.print(" ");
  // }
  // Serial.println();




  // pureMove(0,3000,1000);
  // pureMove(0.5*M_PI,3000,1000); //max speed 15000?
  // pureMove(M_PI,3000,1000);
  // pureMove(1.5*M_PI,3000,1000);

  // float control[4] = {4000, -4000, -0, 0};
  // Encoder_Control(control);//1.5ms


 // pureMove(180.0/M_PI,5000,30);
 // pureMove(90,5000,30);
  //obeyMove();

}
