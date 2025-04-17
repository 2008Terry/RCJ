#include "lstmSonar.h"
#include "lstm15_weights_0blocks.h" //改成当前模型的参数库
#include <math.h>
#include <Arduino.h>
#include "sonar.h"


// 加载权重
const double* weights[] = {
    weight_0,  // 输入权重
    weight_1,  // 隐藏权重
    weight_2,  // 偏置
    weight_3,  // 输出权重
    weight_4   // 输出偏置
};

// 初始化隐藏状态和细胞状态
double hidden_state[hidden_size] = {0.0f};
double cell_state[hidden_size] = {0.0f};
double output[output_size];

// 定义激活函数
double tanh_activation(double x) {
    return tanh(x);
}

// 定义 sigmoid 函数
double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}


// LSTM 单步前向传播
void lstm_step(double input[input_size]) {
    // 提取权重
    const double* W_i = weights[0];  // 输入权重 (input_size, 4 * hidden_size)
    const double* W_h = weights[1];  // 隐藏权重 (hidden_size, 4 * hidden_size)
    const double* bias = weights[2]; // 偏置 (4 * hidden_size,)
    const double* W_o = weights[3];  // 输出权重 (hidden_size, output_size)
    const double* output_bias = weights[4];  // 输出偏置 (output_size,)

    // 临时变量
    double gates[4 * hidden_size] = {0.0f};

    // 计算输入部分
    for (int i = 0; i < 4 * hidden_size; i++) {
        for (int j = 0; j < input_size; j++) {
            gates[i] += input[j] * W_i[j * (4 * hidden_size) + i];
        }
    }

    // 计算隐藏部分
    for (int i = 0; i < 4 * hidden_size; i++) {
        for (int j = 0; j < hidden_size; j++) {
            gates[i] += hidden_state[j] * W_h[j * (4 * hidden_size) + i];
        }
        gates[i] += bias[i];  // 加偏置
    }

    // 分割门控信号
    double input_gate[hidden_size];
    double forget_gate[hidden_size];
    double cell_gate[hidden_size];
    double output_gate[hidden_size];

    for (int i = 0; i < hidden_size; i++) {
        input_gate[i] = sigmoid(gates[i]);
        forget_gate[i] = sigmoid(gates[hidden_size + i]);
        cell_gate[i] = tanh_activation(gates[2 * hidden_size + i]);
        output_gate[i] = sigmoid(gates[3 * hidden_size + i]);
    }

    // 更新细胞状态
    for (int i = 0; i < hidden_size; i++) {
        cell_state[i] = forget_gate[i] * cell_state[i] + input_gate[i] * cell_gate[i];
    }

    // 更新隐藏状态
    for (int i = 0; i < hidden_size; i++) {
        hidden_state[i] = output_gate[i] * tanh_activation(cell_state[i]);
    }

    // 计算输出
    for (int i = 0; i < output_size; i++) {
        output[i] = 0.0f;
        for (int j = 0; j < hidden_size; j++) {
            output[i] += hidden_state[j] * W_o[j * output_size + i];
        }
        output[i] += output_bias[i];  // 加输出偏置
    }
}

void getLocal(double input[input_size]){
  lstm_step(input);
  for (int i = 0;i < output_size;i++){
    Serial.print(output[i]);
  }
}

const int timeInterval = 1.5;
void moveTo(float x,float y,float speed,float dire){
  while(abs(output[0]-x) > radius || (output[1]-y) > radius){
    getSonarData();
    double input[input_size] = {ultra.cm[0]/10.0,ultra.cm[1]/10.0,ultra.cm[2]/10.0,ultra.cm[3]/10.0,speed*timeInterval*cos(dire),speed*timeInterval*sin(dire)};
    getLocal(input);
    bool add = (x <= output[0]);
    float ratio = 1.0*(-output[1]+y)/(-output[0]+x),theta = atan(ratio)/M_PI*180+(add?180:0);
    Serial.println(theta);
    delay(10);
    Serial.flush();
    //move(theta,speed);
  }
}

