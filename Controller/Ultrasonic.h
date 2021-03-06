#ifndef _Ultrasonic_h_
#define _Ultrasonic_h_

#include "move_motor.h"

class US{
    public: 
        US(Navigation *nav);
        void sensorLoop();
        int get_wheel_speed();
        int get_turn_speed();
        int get_side_dist();
        int get_front_dist();
};

#endif