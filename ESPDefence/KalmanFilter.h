#pragma once

class KalmanFilter {
public:
    /**
     * @brief 构造函数
     * @param q 过程噪声协方差（默认0.001） 调大：滤波器更信任新测量值（响应快但波动大） 调小：更平滑但响应延迟  典型初始值：0.001-0.1
     * @param r 测量噪声协方差（默认0.01）  调大：滤波器更信任预测值（更平滑）   调小：更信任测量值（响应快）  典型初始值：0.1-1.0
     * @param initial_value 初始状态值（默认0）
     */
    KalmanFilter(float q = 0.001f, float r = 0.01f, float initial_value = 0.0f);
    
    /**
     * @brief 更新滤波器状态
     * @param measurement 当前测量值
     * @return 滤波后的估计值
     */
    float update(float measurement);
    
    /**
     * @brief 设置过程噪声协方差
     * @param q 新的过程噪声值
     */
    void setQ(float q);
    
    /**
      * @brief 设置测量噪声协方差
      * @param r 新的测量噪声值
      */
    void setR(float r);
    
    /**
     * @brief 重置滤波器状态
     * @param initial_value 重置后的初始值（默认0）
     */
    void reset(float initial_value = 0.0f);

private:
    float x_est_last;  // 上一次的状态估计
    float P_last;      // 上一次的估计误差协方差
    float Q;           // 过程噪声协方差
    float R;           // 测量噪声协方差
};

extern KalmanFilter sonarFilter[4],localFilter[2],infraFilter[2];
