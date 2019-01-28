#ifndef _bluetooth_h_
#define _bluetooth_h_

class Bluetooth
{
  public:
    Bluetooth(HardwareSerial &p);
    void BLEscan();
    HardwareSerial * printer;
    
    
};

#endif
