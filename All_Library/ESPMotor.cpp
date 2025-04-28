#include "ESPMotor.h"

int base = 0,bias = 0;
int32_t right = 0,left = 0,back = 0;
const int biasCoe = 0.8,turnThre = 40,marginDegree = 10,sonarDire[4][4] = {{0,1,2,3},{2,0,3,1},{3,2,1,0},{1,3,0,2}};
const double timeInterval = 0.01,deltaTheta[4] = {0,0.5*M_PI,M_PI,1.5*M_PI};


void setup_ESPMotor(){
  pinMode(suckTrue,INPUT);
  pinMode(shoot,OUTPUT);
}


int32_t sucktime = 0;
const int32_t suckThre = 20;
bool suckBall(){
  // combined with infrared to detect?
  int con = digitalRead(suckTrue);
  if(con == HIGH){
    sucktime++;
    if(sucktime > suckThre) return 1;
  }
  else sucktime = 0;
  return 0;
}



const double maxError = 0.01;
bool equal(double a,double b){
  return abs(a-b) <= maxError;
}
const int deflect = 10,widMargin = 45,lengMargin = 55;
const double diffCoe = 1.5;
double edgeDetect(double globalTheta,bool *stop){
  double diff = 0;
    if(width-output[0] <= widMargin){
      diff = (widMargin-(width-output[0]))*diffCoe;
      if(globalTheta < 0.5*M_PI || 1.5*M_PI < globalTheta){
        if(equal(globalTheta,0) || equal(globalTheta,2*M_PI)) *stop = 1;
        globalTheta = (globalTheta < 0.5*M_PI ? min((90+deflect+diff)/180.0*M_PI,M_PI) : max((270-deflect-diff)/180.0*M_PI,M_PI));
      }
      if(length-output[1] <= lengMargin){
        diff = (lengMargin-(length-output[1]))*diffCoe;
        Serial.println("corner up right");
        if(globalTheta < M_PI){
          if(equal(globalTheta,0.5*M_PI)) *stop = 1;
          globalTheta = (globalTheta < 0.5*M_PI ? max((360-deflect-diff)/180.0*M_PI,1.5*M_PI) : min((180+deflect+diff)/180.0*M_PI,1.5*M_PI));
        }
      }
      else if(output[1] <= lengMargin){
        diff = (lengMargin-output[1])*diffCoe;
        Serial.println("corner down right");
        if(M_PI < globalTheta){
          if(equal(globalTheta,1.5*M_PI)) *stop = 1;
          globalTheta = (globalTheta < 1.5*M_PI ? max((180-deflect-diff)/180.0*M_PI,0.5*M_PI) : min((deflect+diff)/180.0*M_PI,0.5*M_PI));
        }
      }
    }
    else if(output[0] <= widMargin){
      diff = (widMargin-output[0])*diffCoe;
      if(0.5*M_PI < globalTheta && globalTheta < 1.5*M_PI){
        if(equal(globalTheta,M_PI)) *stop = 1;
        globalTheta = (globalTheta < M_PI ? max((90-deflect-diff)/180.0*M_PI,0.0) : min((270+deflect+diff)/180.0*M_PI,2*M_PI));
      }

      if(length-output[1] <= lengMargin){
        diff = (lengMargin-(length-output[1]))*diffCoe;
        Serial.print(globalTheta);
        Serial.print(" ");
        Serial.println("corner up left");
        if(globalTheta < M_PI){
          if(equal(globalTheta,0.5*M_PI)) *stop = 1;
          globalTheta = (globalTheta < 0.5*M_PI ? max((360-deflect-diff)/180.0*M_PI,1.5*M_PI) : min((180+deflect+diff)/180.0*M_PI,1.5*M_PI));
        }
      }
      else if(output[1] <= lengMargin){
        diff = (lengMargin-output[1])*diffCoe;
        Serial.println("corner down left");
        if(M_PI < globalTheta){
          if(equal(globalTheta,1.5*M_PI)) *stop = 1;
          globalTheta = (globalTheta < 1.5*M_PI ? max((180-deflect-diff)/180.0*M_PI,0.5*M_PI) : min((deflect+diff)/180.0*M_PI,0.5*M_PI));
        }
      }
    }
    else{
      if(length-output[1] <= lengMargin){
        diff = (lengMargin-(length-output[1]))*diffCoe;
        if(globalTheta < M_PI){
          if(equal(globalTheta,0.5*M_PI)) *stop = 1;
          globalTheta = (globalTheta < 0.5*M_PI ? max((360-deflect-diff)/180.0*M_PI,1.5*M_PI) : min((180+deflect+diff)/180.0*M_PI,1.5*M_PI));
        }
      }
      else if(output[1] <= lengMargin){
        diff = (lengMargin-output[1])*diffCoe;
        if(M_PI < globalTheta){
          if(equal(globalTheta,1.5*M_PI)) *stop = 1;
          globalTheta = (globalTheta < 1.5*M_PI ? max((180-deflect-diff)/180.0*M_PI,0.5*M_PI) : min((deflect+diff)/180.0*M_PI,0.5*M_PI));
        }
      }
    }
  return globalTheta;
}

void lockWithLocal(int speed){
  double ballDire = getBallDire(); //3-4ms lstm10
  Serial.println(ballDire);
  if(ballDire == -1){
    //Serial.println("no ball");
    ESPsend(-1);
    //delay(5);
  }
  else{
    bias = 0;
    if(135+marginDegree < ballDire && ballDire <= 225){
      // counterclockwise spin
      right++;
      if(right > turnThre){
        base = (base+7)%28;
        left = right = back = 0;
      }
    }
    else if(315 <= ballDire ||  ballDire < 45-marginDegree){
      // clockwise spin
      left++;
      if(left > turnThre){
        base = (base+21)%28;
        left = right = back = 0;
      }
    }
    else if(225 < ballDire && ballDire < 315){
      back++;
      if(back > turnThre){
        base = (base+14)%28;
        left = right = back = 0;
      }
    }
    else{
      left = right = back = 0;
      //bias = (ballDire-90)*(ballDire-90)*biasCoe*(ballDire>90?1:-1);
      bias = (ballDire-90)*biasCoe;
    }
  //  Serial.printf("%d %d %d %d %d\n",left,right,back,bias,base);
    double globalTheta = (ballDire+bias)/180*M_PI+deltaTheta[base/7];
    while(globalTheta > 2*M_PI) globalTheta -= 2*M_PI;
    bool stop = 0;
    globalTheta = edgeDetect(globalTheta,&stop);
    double temp = globalTheta;
    temp -= deltaTheta[base/7];
    while(temp < 0) temp += 2*M_PI;
    while(temp > 2*M_PI) temp -= 2*M_PI;
    if(stop) ESPsend(6.9+base);
    else ESPsend(temp+base);
    getSonarData();
    for (int i = 0;i < 4;i++){
      Serial.print(ultra.cm[sonarDire[base/7][i]]);
      Serial.print(" ");
    }
    Serial.println();
    Serial.print(temp);
    Serial.printf(" %d ",stop);
    Serial.println(globalTheta);
    double input[input_size] = {ultra.cm[sonarDire[base/7][0]]/10.0,ultra.cm[sonarDire[base/7][1]]/10.0,
    ultra.cm[sonarDire[base/7][2]]/10.0,ultra.cm[sonarDire[base/7][3]]/10.0,
    speed*timeInterval*cos(globalTheta),speed*timeInterval*sin(globalTheta)};
    if(stop) input[4] = input[5] = 0;
    getLocal(input);
    // Serial.print(theta);
    // Serial.print(" ");
    Serial.print(output[0]);
    Serial.print(" ");
    Serial.println(output[1]);
  }
}


void locking(){
  double ballDire = getBallDire(); //3-4ms lstm10
  Serial.println(ballDire);
  if(ballDire == -1) ESPsend(-1);
  else{
    bias = 0;
    if(135+marginDegree < ballDire && ballDire <= 225){
      // counterclockwise spin
      right++;
      if(right > turnThre){
        base = (base+7)%28;
        left = right = back = 0;
      }
    }
    else if(315 <= ballDire ||  ballDire < 45-marginDegree){
      // clockwise spin
      left++;
      if(left > turnThre){
        base = (base+21)%28;
        left = right = back = 0;
      }
    }
    else if(225 < ballDire && ballDire < 315){
      back++;
      if(back > turnThre){
        base = (base+14)%28;
        left = right = back = 0;
      }
    }
    else{
      left = right = back = 0;
      //bias = (ballDire-90)*(ballDire-90)*biasCoe*(ballDire>90?1:-1);
      bias = (ballDire-90)*biasCoe;
    }
    Serial.printf("%d %d %d %d %d\n",left,right,back,bias,base);
    float theta = (ballDire+bias)/180*M_PI;
    ESPsend(theta+base);
  }
  delay(9);
}



void moveTo(float x,float y,float speed){
  bool add;
  float ratio,theta;
  while(abs(output[0]-x) > radius || abs(output[1]-y) > radius){
    ESPsend(theta); //getting localization (for like 1-2 seconds) in setup is better
    getSonarData();
    double input[input_size] = {ultra.cm[0]/10.0,ultra.cm[1]/10.0,ultra.cm[2]/10.0,ultra.cm[3]/10.0,speed*timeInterval*cos(theta),speed*timeInterval*sin(theta)};
   // double input[input_size] = {ultra.cm[0]/10.0,ultra.cm[1]/10.0,ultra.cm[2]/10.0,ultra.cm[3]/10.0,0,0};
    getLocal(input);
    Serial.print(theta);
    Serial.print(" ");
    Serial.print(output[0]);
    Serial.print(" ");
    Serial.println(output[1]);

    add = (x <= output[0]);
    ratio = 1.0*(-output[1]+y)/(-output[0]+x),theta = atan(ratio)+(add?M_PI:0);
    if(theta < 0) theta += 2*M_PI;
  }
}

void offenceMoveTo(float x,float y,float speed){
  bool add;
  float ratio,gloablTheta;
  while(abs(output[0]-x) > radius || abs(output[1]-y) > radius){
    float theta = gloablTheta-M_PI;
    while(theta < 0) theta += 2*M_PI;
    ESPsend(theta+14); //getting localization (for like 1-2 seconds) in setup is better
    getSonarData();
    double input[input_size] = {ultra.cm[3]/10.0,ultra.cm[2]/10.0,ultra.cm[1]/10.0,ultra.cm[0]/10.0,speed*timeInterval*cos(gloablTheta),speed*timeInterval*sin(gloablTheta)};
   // double input[input_size] = {ultra.cm[0]/10.0,ultra.cm[1]/10.0,ultra.cm[2]/10.0,ultra.cm[3]/10.0,0,0};
    getLocal(input);
    Serial.print(gloablTheta);
    Serial.print(" ");
    Serial.print(output[0]);
    Serial.print(" ");
    Serial.println(output[1]);

    add = (x <= output[0]);
    ratio = 1.0*(-output[1]+y)/(-output[0]+x),gloablTheta = atan(ratio)+(add?M_PI:0);
    if(gloablTheta < 0) gloablTheta += 2*M_PI;
  }
}


void moveBall(){
  double ballDire = getBallDire(); //3-4ms lstm10
  Serial.println(ballDire);
  if(ballDire == -1){
    ESPsend(-1);
  }
  else{
    double bias = (ballDire-90)*biasCoe,theta;
    //??suck == true -> 直推
    if(60 <= ballDire && ballDire <= 120){
      theta = (ballDire+bias)/180*M_PI;
    }
    else if(270 <= ballDire || ballDire < 60){
      ballDire -= 90;
      while(ballDire < 0) ballDire += 360;
      theta = ballDire/180*M_PI;
    }
    else/* if(120 < ballDire && ballDire < 270)*/{
      ballDire += 90;
      while(ballDire > 360) ballDire -= 360;
      theta = ballDire/180*M_PI;
    }
    Serial.print(theta/M_PI*180);
    Serial.println(" theta");
    ESPsend(theta);
  }
  delay(6);
  
  //localization??
}






// void move(double theta,HardwareSerial* serial){
//   serial->println(theta);
//   delay(10);
//   serial->flush();
// }
