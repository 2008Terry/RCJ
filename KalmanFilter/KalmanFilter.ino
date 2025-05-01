#include "KalmanFilter.h"
#include "sonar.h"

// // 为不同传感器创建滤波器实例
// KalmanFilter tempFilter;       // 使用默认参数
// KalmanFilter distanceFilter(0.1f, 0.5f);  // 自定义参数

void setup() {
    Serial.begin(115200);
    setup_sonar();
    // // 可以动态调整参数
    // tempFilter.setQ(0.002f);
    // tempFilter.setR(0.1f);
    
    // Serial.println("Kalman Filter Class Example");
}

void loop() {



    getSonarData();
    // for (int i = 0;i < 1;i++){
    //     Serial.print(ultra.cm[i]);
    //     Serial.print(" ");
    // }
    // Serial.println("rawData");
    double filtered[4];
    for (int i = 0;i < 1;i++){
        filtered[i] = sonarFilter[i].update(ultra.cm[i]);
        // Serial.println(filtered[i]);
       // Serial.print(" ");
    }
    Serial.print(ultra.cm[0]);
    Serial.print(" ");
    Serial.println(filtered[0]);
    // Serial.println("1000");
   // Serial.println("filtered");
    // // 模拟传感器读数
    // float rawTemp = analogRead(34) * 0.1f;
    // float rawDist = analogRead(35);

    // // 应用卡尔曼滤波
    // float filteredTemp = tempFilter.update(rawTemp);
    // float filteredDist = distanceFilter.update(rawDist);

    // // 输出结果
    // Serial.print("Temperature: ");
    // Serial.print(rawTemp);
    // Serial.print(" -> ");
    // Serial.print(filteredTemp);

    // Serial.print(" | Distance: ");
    // Serial.print(rawDist);
    // Serial.print(" -> ");
    // Serial.println(filteredDist);

    // delay(100);
}