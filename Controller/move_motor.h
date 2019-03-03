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
  	void stopMotors();
	void goForward(int speed);
	void goBackward(int speed); 
	void straighten();
	void turnLeft(int speed);
	void turnRight(int speed); 
};

#endif
