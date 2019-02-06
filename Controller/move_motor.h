#ifndef _move_motor_h_
#define _move_motor_h_

class Navigation
{
  public:
    Navigation();
    void move_forward(int force, int interval);
    void turn(int force, int interval);
    void queryCommand();
    void queueForward();
    void setPrinter(Print & p);
    void MotorSpeed(int force);
    void SteerSpeed(int force);
    void DecreaseSpeed();
    void stop_all();
    Print * printer;
    int speed;
};

#endif
