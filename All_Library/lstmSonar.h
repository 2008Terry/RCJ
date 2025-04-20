#pragma once

#include "lstm15_weights_0blocks.h" //改成当前模型的参数库
#include <math.h>
#include <Arduino.h>
#include "sonar.h"

// 定义 LSTM 参数
#define input_size 6 // 输入特征数  
#define hidden_size 15 //隐藏单元数
#define output_size 2 //输出维度

// 加载权重
extern const double* weights[];

extern double hidden_state[hidden_size];
extern double cell_state[hidden_size];
extern double output[output_size];

double tanh_activation(double x);
double sigmoid(double x);
void lstm_step(double input[input_size]);
void getLocal(double input[input_size]);
#define radius 7
extern const double timeInterval;
void moveTo(float x,float y,float speed);
//void move(double theta);

