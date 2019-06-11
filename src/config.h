#ifndef __CONFIG_H
  #define __CONFIG_H

  // Development settings
  #define DEBUG
  #define SERIAL_BAUD     115200

  // Uno, Nano, Mini | PWM Pins: 3, 5, 6, 9, 10, 11 | PWM FREQUENCY: 490 Hz (pins 5 and 6: 980 Hz)
  #define PWM_IN_PIN      3
  //"PD3"
  #define PWM_OUT_PIN     11
  //"PD9"

  #define PWM_MIN_VALUE   10
  #define PWM_MAX_VALUE   255

#endif
