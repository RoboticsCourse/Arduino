#ifndef _move_motor_h_
#define _move_motor_h_

#include <stdint.h>

#include <Wire.h>
#include <Adafruit_MotorShield.h>

class Navigation
{
  public:
    void move_forward(int force, int interval);
    // void setPrinter(Print & p);
    void MotorSpeed(int force);
    void SteerSpeed(int force);
    void stop_all();
    // Print *printer;
    uint8_t speed;
};

#endif
