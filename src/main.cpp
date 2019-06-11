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

int pwm_out_value;
volatile int pwm_in_value = 0;
volatile int prev_time = 0;

void rising();
void falling();

void setup() {
  // configure PWM output
  pinMode(PWM_OUT_PIN, OUTPUT);
  TCCR2A = _BV(COM2A1) | _BV(WGM20);

  // configure LED
  pinMode(LED_BUILTIN, OUTPUT);

  // configure PWM input
  attachInterrupt(0, rising, RISING);

  #ifdef DEBUG
  Serial.begin(SERIAL_BAUD);
  #endif
}

void rising() {
  attachInterrupt(digitalPinToInterrupt(PWM_IN_PIN), falling, FALLING);
  prev_time = micros();
}

void falling() {
  attachInterrupt(digitalPinToInterrupt(PWM_IN_PIN), rising, RISING);
  pwm_in_value = micros()-prev_time;

  DEBUG_PRINT("In value: ");
  DEBUG_PRINTLN(pwm_in_value);

  if (pwm_in_value == 0) {
    pwm_out_value = 150;
    // input value was 0, sending 0 and disabling led
    digitalWrite(LED_BUILTIN, LOW);
    //analogWrite(PWM_OUT_PIN, 0);
  } else {
    // input value was more than 0, mapping it to PWM_MIN_VALUE / PWM_MAX_VALUE
    pwm_out_value = map(pwm_in_value, 1, 255, PWM_MIN_VALUE, PWM_MAX_VALUE);
    // and enabling the led with this value
    analogWrite(LED_BUILTIN, pwm_in_value - pwm_out_value);
  }

  // sending the calculated PWM value to the pin
  //analogWrite(PWM_OUT_PIN, pwm_out_value);
  //OCR1A = pwm_out_value;
  OCR2A = pwm_out_value;

  DEBUG_PRINT(millis());
  DEBUG_PRINT(" ");
  DEBUG_PRINT(pwm_in_value);
  DEBUG_PRINT(" > ");
  DEBUG_PRINTLN(pwm_out_value);
}

void loop() {}
