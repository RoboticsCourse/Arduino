
#include "bluetooth.h"
#include "Ultrasonic.h"

Bluetooth* bluetooth;
US *us;
Navigation nav; // auto initializes it

int schedule = 0;

void setup() {
  // Serial.begin(9600);           // set up Serial library at 9600 bps
  bluetooth = new Bluetooth(&nav);
  
  nav.setup();
  us = new US(&nav);

}

void loop() {
  //if(schedule == 10){
    us->sensorLoop();
    //schedule = 0;
  //}
  /*
  else{
    schedule++;
    bluetooth->sendDistance("F ",us->get_front_dist());
    bluetooth->sendDistance("S ",us->get_side_dist());
    bluetooth->BLEscan(); // connects to new device; if it's connected, does nothing
  }
  */
}
