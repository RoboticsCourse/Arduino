#include "bluetooth.h"
#include "Ultrasonic.h"

Bluetooth* bluetooth;
US *us;
Navigation nav; // auto initializes it

void setup() {
  // Serial.begin(9600);           // set up Serial library at 9600 bps
  bluetooth = new Bluetooth(&nav);
  
  nav.setup();
  us = new US(&nav);

}

void loop() {
  us->sensorLoop();
  bluetooth->sendDistance("Front: ",us->get_front_dist());
  bluetooth->sendDistance("Side: ",us->get_side_dist());
  bluetooth->BLEscan(); // connects to new device; if it's connected, does nothing
}
