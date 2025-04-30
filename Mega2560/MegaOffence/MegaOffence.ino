#include "packet.h"
#include "imu_data_decode.h"
#include "MegaMotor.h"
#include "gray.h"
#include "correMega.h"
#include "dribble.h"

void setup() {
  Serial.begin(115200);

  setup_correMega();
  setup_MegaMotor();
  setup_dribble();
  // delay(1000);
  // spin(2000);
  // delay(3000);
  // pureMove(180,1.5*M_PI,4000,500);
}

//int cita = 0;
void loop() {
  // selfRevolve(4000);
  // if(digitalRead(shootTrue) == HIGH){
  //   if(digitalRead(shootDire) == LOW){
  //     shoot(1,4000,135,120,10000);
  //   }
  //   else{
  //     shoot(0,4000,135,120,10000);
  //   }
  // }
  


  // offenceRevolve(4500);//offence code
  // if(digitalRead(shootTrue) == HIGH){ 
  //   //Serial.println("ok");
  //   spin(2000);
  //   if(digitalRead(shootDire) == LOW){
  //     shoot(1,200,4000,135,120,1000);
  //   }
  //   else{
  //     shoot(0,200,4000,135,120,1000);
  //   }
  //   alreadyRevolve = 0;
  //   digitalWrite(readyToGo,LOW);
  //   //delay(60000);
  // }
  // else{
  //   // alreadyRevolve = 0;
  //   //digitalWrite(readyToGo,LOW);
  //   suck(2000);
  //   obeyLock(4400,13);
  // }


  // suck(2000);
  obeyLock(1000,10);




 // Serial.println(receive());
  // double num = receive();
  // if(num != -1) Serial.println(num);

  // suck(1200);
  // getSonar();
  // Serial.println(dis);








  // obeyLock(1514,10);

  // suck(1200);
  //obeyLock(4816,10);
  // trigger();
  // delay(100);
  // Serial.println(echo());

  // Serial.println("ok");
  

  //shoot(1,4000,135,120,10000);

  // spin(2000);
  // delay(3000);
  // spin(1000);
  // delay(1000);



  //delay(10000);
 // suck();



  //Serial.println(getSonar());


  // trigger();
  // delay(100);
  // Serial.println(echo());














  // suck();
  // shoot(1,4000,135);

}
