#include "sonar.h"
#include "lstmSonar.h"
#include "correESP.h"
#include "ESPMotor.h"


// float local[4][2] = {{130,80},{60,180},{130,180},{60,80}};
//float local[7][2] = {{142,40},{142,120},{90,50},{40,120},{40,40},{90,120},{142,190}};
float local[7][2] = {{40,40},{40,120},{90,50},{142,120},{142,40},{90,120},{40,190}};

//float local[2][2] = {{40,40},{30,140}};

void setup() {
  //delay(8000);
  Serial.begin(115200);
  setup_correESP();
  setup_sonar();
  wait(0,500,1000);
  setup_Local();
}

int theta = 0;
double input[6] = {0.0f};
bool ok = 0;
void loop() {
  // getSonarData();
  // for (int i = 0;i < 4;i++){
  //   Serial.print(filteredSonar[i]);
  //   Serial.print(" ");
  // }
  // Serial.println();
  // double input[input_size] = {filteredSonar[0]/10.0,filteredSonar[1]/10.0,filteredSonar[2]/10.0,filteredSonar[3]/10.0,0,0};
  // getLocal(input);
  // // Serial.print(Foutput[0]);
  // // Serial.print(" ");
  // // Serial.println(Foutput[1]);

  // delay(1);

  // for (int i = 0;i < 4;i++){
  //   setAngle(i,1);
  //   Serial.print(getAngle(i));
  //   Serial.print(" ");
  // }
  // Serial.println();

  // if(!ok){
  //   for (int i = 0;i < 2;i++){
  //     moveTo(local[i][0],local[i][1],11);
  //   }
  //   ok = 1;
  // }
  // ESPsend(20.8);


  for (int i = 0;i < 7;i++){
    moveTo(local[i][0],local[i][1],11);
  }
  delay(10000);




  // trigger(2);
  // delay(150);
  // Serial.println(echo(2));
  // int dis = -1;
  // while(dis == -1){
  //   dis = echo(2);
  //   delay(10);
  // }
  // Serial.println(dis);


  // getSonarData();
  // for (int i = 0;i < SONAR_NUM;i++){
  //   Serial.print(ultra.cm[i]);
  //   Serial.print(" ");
  // }
  // Serial.println();
  // double input[input_size] = {ultra.cm[0]/10.0,ultra.cm[1]/10.0,ultra.cm[2]/10.0,ultra.cm[3]/10.0,0,0};
  // getLocal(input);
  // Serial.printf("%lf %lf\n",output[0],output[1]);
  // delay(10);





  // float num = 1.0*theta*M_PI/180;
  // // MySerial.println(num);
  // // delay(10);
  // // MySerial.flush();
  // move(num,&MySerial);
  // theta = (theta+10)%360;
}
