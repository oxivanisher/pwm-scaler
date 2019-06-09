# Why?

I use a woodpecker based Mini CNC with a attached laser for some engraving.
Sadly, the supplied laser does not start to burn at PWM signal strength 1. This
resulted in missing laser marks at the beginning of line when using the `M4`
G-Code in [GRBL laser mode](https://github.com/gnea/grbl/wiki/Grbl-v1.1-Laser-Mode).
This would be fixable in [GRBL](https://github.com/gnea/grbl/) itself by
changing values in a file but since it is not so trivial to flash your own GRBL
to the woodpecker boards, it seemed easier to just manipulate the PWM signal
going to the laser.

# Usage

Configure `PWM_MIN_VALUE` and `PWM_MAX_VALUE` in `config.h`. It defaults to use
pin 3 and 9 with 490 Hz. You can use pin 5 and 6 for 980 Hz if required.

To do this, enable `DEBUG` and view the serial console output. Then slowly
increase the PWM value (how strong the laser shoots) and note when it starts
to leave a mark. Now you can set the `PWM_MIN_VALUE` to this number.

# Attention

Please be aware, that this system has some minimal delay, since the new PWM
value can only be calculated, once the incoming signal is finished reading.
For my usage, "fixing" the PWM signal for a diode laser, this is no issue,
since my Mini CNC is very slow anyways.

# Sources

Collection of useful links:
* [Three Ways To Read A PWM Signal With Arduino](http://www.benripley.com/diy/arduino/three-ways-to-read-a-pwm-signal-with-arduino/)
* [Arduino reference - analogWrite()](https://www.arduino.cc/reference/en/language/functions/analog-io/analogwrite/)
