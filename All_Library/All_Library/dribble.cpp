#include <Arduino.h>
#include "dribble.h"

void PWM(int PWMPin, int PWMValue){  // 模拟PWM；频率100Hz
  PWMValue += 1000;
  digitalWrite(PWMPin, HIGH);
  delayMicroseconds(PWMValue);
  digitalWrite(PWMPin, LOW);
  delayMicroseconds(10000 - PWMValue);
}