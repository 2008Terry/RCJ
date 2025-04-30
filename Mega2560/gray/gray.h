#ifndef GRAY_H
#define GRAY_H





/*
imports:

setup:
pinMode(Lout1,INPUT);
pinMode(Lout2,INPUT);
pinMode(Lout3,INPUT);
pinMode(Lout4,INPUT);
pinMode(Rout1,INPUT);
pinMode(Rout2,INPUT);
pinMode(Rout3,INPUT);
pinMode(Rout4,INPUT);
pinMode(Bout1,INPUT);
pinMode(Bout2,INPUT);
pinMode(Bout3,INPUT);
pinMode(Bout4,INPUT);
*/

#define Bout1 A11
#define Bout2 A10
#define Bout3 A9
#define Bout4 A8

#define Rout1 A7
#define Rout2 A6
#define Rout3 A5
#define Rout4 A4

#define Lout1 A3
#define Lout2 A2
#define Lout3 A1
#define Lout4 A0

#define white 10

struct grayInfo{int l,r,b;};

grayInfo getGray();

#endif

