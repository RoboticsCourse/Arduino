#ifndef _move_motor_h_
#define _move_motor_h_

#include <Wire.h>
#include <Adafruit_MotorShield.h>

class Navigation
{
  public:
  	void setup();
  	void MotorSpeed(int force);
  	void SteerSpeed(int force);
  	void stop_all();
};

#endif
