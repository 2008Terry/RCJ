#pragma once

#include "infrared10.h" //改成当前模型的参数库
#include <math.h>
#include <Arduino.h>
#include "infrared.h"

// 定义 LSTM 参数
#define input_size 2 // 输入特征数  
#define hidden_size 10 //隐藏单元数
#define output_size 2 //输出维度

// 加载权重
extern const double* weights_infrared[];

extern double hidden_state_infrared[hidden_size];
extern double cell_state_infrared[hidden_size];
extern double output_infrared[output_size];

double tanh_activation_infrared(double x);
double sigmoid_infrared(double x);
void lstm_step_infrared(double input[input_size]);
//void getLocal(double input[input_size]);

extern const int direF[8],direB[8];
extern int noBall;
float getBallDire();

