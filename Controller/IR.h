#ifndef _IR_h_
#define _IR_h_

#include "move_motor.h"

class IR{
    public: 
    IR(Navigation *nav);
    void sensorLoop();
};

#endif