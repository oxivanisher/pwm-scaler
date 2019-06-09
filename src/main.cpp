#include <Arduino.h>

// Read settingd from config.h
#include "config.h"

#ifdef DEBUG
  #define DEBUG_PRINT(x) Serial.print (x)
  #define DEBUG_PRINTLN(x) Serial.println (x)
#else
  #define DEBUG_PRINT(x)
  #define DEBUG_PRINTLN(x)
#endif

int pwm_in_value;
int pwm_out_value;

void setup() {
  pinMode(PWM_IN_PIN, INPUT);
  pinMode(PWM_OUT_PIN, OUTPUT);

  #ifdef DEBUG
  Serial.begin(SERIAL_BAUD);
  #endif
}

void loop() {
  pwm_in_value = pulseIn(PWM_IN_PIN, HIGH);

  if (pwm_in_value == 0) {
    pwm_out_value = 0;
  } else {
    pwm_out_value = map(pwm_in_value, 1, 255, PWM_MIN_VALUE, PWM_MAX_VALUE);
  }

  DEBUG_PRINT(pwm_in_value);
  DEBUG_PRINT(" > ");
  DEBUG_PRINTLN(pwm_out_value);
}
