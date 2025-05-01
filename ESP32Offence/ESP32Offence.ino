#include "infrared.h"
#include "lstmInfrared.h"
#include "correESP.h"
#include "sonar.h"
#include "lstmSonar.h"
#include "ESPMotor.h"



void setup() {
  Serial.begin(115200);
  setup_ESPMotor();
  setup_infra();
  setup_correESP();
  setup_sonar();
 // Serial.println("ok");
  setup_Local();
}

bool antiLocal = 0;
unsigned long antiLocalTime = 0x7f7f7f7f;
bool haveShot = 0;
void loop() {
  // digitalWrite(revolveTrue,HIGH);
  // if(digitalRead(alreadyRevolve) == HIGH){
  //   digitalWrite(shootDire,LOW);
  //   digitalWrite(shoot,HIGH);
  //   delay(10000);
  // }
  // ESPsend(20.95);
  // Serial.println(20.95);

  // if(suckBall()){ //offence code
  //   digitalWrite(revolveTrue,HIGH);
  //   if(digitalRead(alreadyRevolve) == HIGH){
  //     if(!antiLocal){
  //       antiLocalTime = min(antiLocalTime,millis());
  //       ESPsend(20.95); //add exclusive value of stop
  //       getSonarData();
  //       double input[input_size] = {filteredSonar[3]/10.0,filteredSonar[2]/10.0,filteredSonar[1]/10.0,filteredSonar[0]/10.0,0,0};
  //       getLocal(input);
  //       Serial.print("1 ");
  //       Serial.print(Foutput[0]);
  //       Serial.print(" ");
  //       Serial.println(Foutput[1]);
  //       if(millis()-antiLocalTime > 1700) antiLocal = 1;
  //     }
  //     else{
  //       ESPsend(14+1.5*M_PI);
  //       getSonarData();
  //       double input[input_size] = {filteredSonar[3]/10.0,filteredSonar[2]/10.0,filteredSonar[1]/10.0,filteredSonar[0]/10.0,0,timeInterval*32};
  //       getLocal(input);
  //       Serial.print("2 ");
  //       Serial.print(Foutput[0]);
  //       Serial.print(" ");
  //       Serial.println(Foutput[1]);
  //       if(Foutput[1] >= 40){
  //         int32_t stoptime = millis();
  //         while(millis()-stoptime < 200) ESPsend(20.95);
  //         if(Foutput[0] < 91) digitalWrite(shootDire,HIGH); // problem: localization!! 
  //         else digitalWrite(shootDire,LOW); 
  //         digitalWrite(shoot,HIGH);
  //         antiLocal = 0;
  //         antiLocalTime = 0x7f7f7f7f;
  //         while(digitalRead(alreadyRevolve) == HIGH){}

  //         digitalWrite(shoot,LOW);
  //         digitalWrite(revolveTrue,LOW);
  //         haveShot = 1;
  //         // while(1){}
  //         int32_t initialTime = millis();
  //         while(millis()-initialTime <= 500){
  //           ESPsend(6.9);
  //         }
  //       }
  //       //if(!haveShot) ESPsend(14+1.5*M_PI);
  //     }
  //   }
  // }
  // else{
  //   haveShot = 0;
  //   antiLocal = 0;
  //   antiLocalTime = 0x7f7f7f7f;
  //   Serial.println("trackball");
  //   digitalWrite(shoot,LOW);
  //   digitalWrite(revolveTrue,LOW);
  //   lock1Dire(32,0.013);
  // }


  lock1Dire(15,0.013);




  // int strengthF = maxNum(&Wire1);
  // int strengthB = maxNum(&Wire);
  // Serial.println(max(strengthF,strengthB));




  //moveBall();







 // Serial.println("run");

  // ESPsend(6.9);
  // delay(10);

  // getSonarData(); //0-4ms
  // for (int i = 0;i < 4;i++){
  //   Serial.print(ultra.cm[i]);
  //   Serial.print(" ");
  // }
  // Serial.println();
  // double input[input_size] = {ultra.cm[sonarDire[1][0]]/10.0,ultra.cm[sonarDire[1][1]]/10.0,
  // ultra.cm[sonarDire[1][2]]/10.0,ultra.cm[sonarDire[1][3]]/10.0,0,0};
  // getLocal(input); //15LSTM 2ms   50LSTM 13ms
  // Serial.print(output[0]);
  // Serial.print(" ");
  // Serial.println(output[1]);
  //delay(10);
}
