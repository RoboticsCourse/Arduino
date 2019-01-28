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
    Print * printer;
};

#endif
