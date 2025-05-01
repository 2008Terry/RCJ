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

#define suckTrue 46 //dribbleTrue 23  Mega: whether the ball is being dribbled
#define shoot 3 //shootTrue 22   ESP: decide to shoot
#define shootDire 20 //shootDire 24   ESP: which direction to shoot
#define revolveTrue 19 //revolveTrue 25   ESP: decide to revolve
#define alreadyRevolve 8 //readyToGo 26  Mega: whether completed revolve


void lock1Dire(int speed,double interval);
void lock2Dire(int speed,double interval);
void lockWithLocal(int speed,double interval);
void locking();

#define radius 5
void moveTo(float x,float y,float speed,int interval);
void offenceMoveTo(float x,float y,float speed);
void moveBall();
//void move(double theta);