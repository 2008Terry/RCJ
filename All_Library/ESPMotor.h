#pragma once

#include "correESP.h"
#include "lstmInfrared.h"
#include "lstmSonar.h"
#include <Arduino.h>




extern int base,bias;
extern int32_t right,left,back;
extern const int biasCoe,turnThre,marginDegree,sonarDire[4][4];
extern const double timeInterval,deltaTheta[4],maxError;
extern const int deflect;
extern const double diffCoe;

void setup_ESPMotor();
extern int32_t sucktime;
extern const int32_t suckThre;
bool suckBall();
bool equal(double a,double b);
double edgeDetect(double globalTheta,bool *stop);


#define width 182
#define length 243

#define suckTrue 46
#define shoot 3




void lockWithLocal(int speed);
void locking();

#define radius 5
void moveTo(float x,float y,float speed);
void offenceMoveTo(float x,float y,float speed);
void moveBall();
//void move(double theta);