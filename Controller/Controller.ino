#include "bluetooth.h"

Bluetooth* bluetooth;

Navigation nav; // auto initializes it

void setup() {
  // Serial.begin(9600);           // set up Serial library at 9600 bps
  bluetooth = new Bluetooth(&nav);
  nav.setup();
}

void loop() {
  bluetooth->BLEscan(); // connects to new device; if it's connected, does nothing
}
