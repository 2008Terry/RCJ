#pragma once

/*
imports:
#include <mcp2515.h>
#include "packet.h"
#include "imu_data_decode.h"
#include <math.h>
#include "MegaMotor.h"

setup:
canMsg_OUT.can_id = 0x200;
canMsg_OUT.can_dlc = 8;
imu_data_decode_init();
mcp2515.reset();
mcp2515.setBitrate(CAN_1000KBPS,MCP_8MHZ);
mcp2515.setNormalMode();
Serial.println("Example: Write to CAN");
*/

#include <mcp2515.h>
#include "packet.h"
#include "imu_data_decode.h"
#include <math.h>
#include "gray.h"
#include <SPI.h>
#include "correMega.h"


extern const float kp,ki,kd,dt;
//l:0 r:1 b:2
extern int v[4],actual_Speed[4];
extern float integral[4],derivative[4],error[4],pre_error[4];
//Left ID:1  Right ID:2  Back ID:3 


extern struct can_frame canMsg_OUT;
extern struct can_frame canMsg_IN;
extern MCP2515 mcp2515;

extern float moveDire;
float obeyMove();
void moveWithGray(float cita,float speed,int duration);
void pureMove(float cita,float speed,int duration);
void Encoder_Control(float goal[4]);

