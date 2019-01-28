#ifndef _bluetooth_h_
#define _bluetooth_h_

#include "move_motor.h"

class Bluetooth
{
  public:
    Bluetooth(HardwareSerial &p, Navigation *nav);
    void BLEscan();
    HardwareSerial * printer;
    
    
};

#endif
