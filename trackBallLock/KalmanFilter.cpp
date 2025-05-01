#include "KalmanFilter.h"

KalmanFilter::KalmanFilter(float q, float r, float initial_value) 
    : Q(q), R(r), x_est_last(initial_value), P_last(1.0f) {
    // 初始化列表已完成所有初始化工作
}

float KalmanFilter::update(float measurement) {
    /* 预测阶段 */
    float x_temp_est = x_est_last;
    float P_temp = P_last + Q;
    
    /* 更新阶段 */
    float K = P_temp / (P_temp + R);  // 卡尔曼增益
    x_est_last = x_temp_est + K * (measurement - x_temp_est);
    P_last = (1.0f - K) * P_temp;
    
    return x_est_last;
}

void KalmanFilter::setQ(float q) {
    Q = q;
}

void KalmanFilter::setR(float r) {
    R = r;
}

void KalmanFilter::reset(float initial_value) {
    x_est_last = initial_value;
    P_last = 1.0f;
}

KalmanFilter sonarFilter[4],localFilter[2],infraFilter[2];