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
  setup_Local();
}


double defenceDire = 90;
int condition;
const double defenceInterval = 0.015,speed = 17;

void loop() {
  // ESPsend(6.95);
  
  // for (int i = 0;i < 50;i++){
  //   ESPsend(0);
  //   Serial.println(0);
  //   delay(15);
  // }
  // for (int i = 0;i < 50;i++){
  //   ESPsend(6.95);
  //   Serial.println("stop");
  //   delay(15);
  // }
  // for (int i = 0;i < 50;i++){
  //   ESPsend(M_PI);
  //   Serial.println(180);
  //   delay(15);
  // }
  // for (int i = 0;i < 50;i++){
  //   ESPsend(6.95);
  //   Serial.println("stop");
  //   delay(15);
  // }




  getSonarData(); //defence code
  double input[input_size] = {filteredSonar[0]/10.0,filteredSonar[1]/10.0,filteredSonar[2]/10.0,filteredSonar[3]/10.0,0,0};
  if(condition == 1){
    input[4] = -1*defenceInterval*speed;
  }
  else if(condition == 2){
    input[4] = defenceInterval*speed;
  }
  getLocal(input);
  // for (int i = 0;i < 4;i++){
  //   Serial.print(filteredSonar[i]);
  //   Serial.print(" ");
  // }
  // Serial.println();
  // Serial.print(Foutput[0]);
  // Serial.print(" ");
  // Serial.println(Foutput[1]);
  defenceDire = getBallDire();
  Serial.print(defenceDire);
  Serial.println("ball dire");
  Serial.println(Foutput[1]); //use raw data??
  //ocillation function to replace ESPsend(6.95)
  if(defenceDire == -1){
    ESPsend()
    ESPsend(6.95);
    condition = 0;
  }
  if(95 < defenceDire && defenceDire < 270){
    if(Foutput[0] <= 60){
      ESPsend(6.95);
      condition = 0;
    }
    else{
      condition = 1;
      if(Foutput[1] > 45){
        ESPsend((180+10)/180.0*M_PI);
        Serial.println(190);
      }
      else if(Foutput[1] < 35){
        ESPsend((180-10)/180.0*M_PI);
        Serial.println(170);
      }
      else{
        ESPsend(M_PI);
        Serial.println(180);
      }
    }
  }
  else if(defenceDire < 85 || 270 < defenceDire){
    if(Foutput[0] >= 120){
      ESPsend(6.95);
      condition = 0;
    }
    else{
      condition = 2;
      if(Foutput[1] > 45){
        ESPsend((360-10)/180.0*M_PI);
        Serial.println(350);
      }
      else if(Foutput[1] < 35){
        ESPsend(10/180.0*M_PI);
        Serial.println(10);
      }
      else{
        ESPsend(0);
        Serial.println(0);
      }
    }
  }
  else{
    ESPsend(6.95);
    condition = 0;
  }
}
