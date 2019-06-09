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
  pinMode(LED_BUILTIN, OUTPUT);

  #ifdef DEBUG
  Serial.begin(SERIAL_BAUD);
  #endif
}

void loop() {
  // read PWM in value
  pwm_in_value = pulseIn(PWM_IN_PIN, HIGH);

  if (pwm_in_value == 0) {
    // input value was 0, sending 0 and disabling led
    digitalWrite(LED_BUILTIN, LOW);
    analogWrite(PWM_OUT_PIN, 0);
  } else {
    // input value was more than 0, mapping it to PWM_MIN_VALUE / PWM_MAX_VALUE
    pwm_out_value = map(pwm_in_value, 1, 255, PWM_MIN_VALUE, PWM_MAX_VALUE);
    // sending the calculated PWM value to the pin
    analogWrite(PWM_OUT_PIN, pwm_out_value);
    // and enabling the led with this value
    analogWrite(LED_BUILTIN, pwm_in_value - pwm_out_value);
  }

  DEBUG_PRINT(millis());
  DEBUG_PRINT(" ");
  DEBUG_PRINT(pwm_in_value);
  DEBUG_PRINT(" > ");
  DEBUG_PRINTLN(pwm_out_value);
}
