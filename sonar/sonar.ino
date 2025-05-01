#include "sonar.h"
#include "lstmSonar.h"

void setup() {
  Serial.begin(115200); 
  setup_sonar();
  wait(100,1000);
}

void loop(){
  //setAddress(0,0xD6);

  // for (int i = 0;i < 4;i++){
  //   trigger(i);
  //   delay(15); //try ping interval
  // }
  // unsigned long itime = millis();
  
  // while(itime+2000>=millis()){
  //   Serial.print(itime);
  //   Serial.print(" ");
  //   for (int i = 0;i < 4;i++){
  //     Serial.print(echo(i));
  //     Serial.print(" ");
  //   }
  //   Serial.println();
  //   delay(30); // try read interval
  // }



  getSonarData();
  for (int i = 0;i < 4;i++){
    Serial.print(filteredSonar[i]);
    Serial.print(" ");
  }
  Serial.println();
  double input[input_size] = {filteredSonar[0]/10.0,filteredSonar[1]/10.0,filteredSonar[2]/10.0,filteredSonar[3]/10.0,0,0};
  getLocal(input);
  Serial.print(output[0]);
  Serial.print(" ");
  Serial.print(output[1]);
  Serial.print(" ");
  Serial.print(Foutput[0]);
  Serial.print(" ");
  Serial.println(Foutput[1]);
  


  // for (int i = 0;i < 4;i++){
  // //  setAngle(i,1);
  //   Serial.print(getAngle(i));
  //   Serial.print(" ");
  // }
  //  Serial.println();



  // trigger(2);
  // // delay(100);
  // // Serial.println(echo(1));
  // int dis = -1;
  // while(dis == -1){
  //   dis = echo(2);
  // }
  // Serial.println(dis);




  //Serial.println("ok");
  // trigger(1);
  // delay(100);
  // Serial.println(echo(1));
  //setAngle(0,1);
  //getAngle(0);



  //getSonarData();

  // for (int i = 0;i < 1;i++){
  //   trigger(i);
  //   delay(70);
  //   Serial.print(echo(i));
  //   Serial.print(" ");
  // }
  // Serial.println();



//  trigger(0);
  //delay(100);
  // trigger(1);
  // delay(100);
  // for (int i = 1;i < 2;i++){
  //   Serial.print(echo(i));
  //   Serial.print(" ");
  // }
  // Serial.println();
  //setAddress(0,0xD0);
  // getAddress(0);
  // for (int i = 0;i < 4;i++){
  //   Serial.print(ultra.cm[i]);
  //   Serial.print(" ");
  // }
  // Serial.println();
  
}
