#ifndef _bluetooth_h_
#define _bluetooth_h_

#include <SPI.h>
#include "Adafruit_BLE_UART.h"
#include "move_motor.h"


class Bluetooth
{
  public:
    Bluetooth(Navigation *nav);
    void BLEscan();
    void sendDistance(String prefix, int distance);
};

#endif
