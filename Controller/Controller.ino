/* 
This is a test sketch for the Adafruit assembled Motor Shield for Arduino v2
It won't work with v1.x motor shields! Only for the v2's with built in PWM
control

For use with the Adafruit Motor Shield v2 
---->	http://www.adafruit.com/products/1438
*/

// #include "bluetooth.h"
#include "move_motor.h"

// Bluetooth* bluetooth;

Navigation nav; // auto initializes it

void setup() {
  // Serial.begin(9600);           // set up Serial library at 9600 bps
  // Serial.println("Adafruit Motorshield v2 - DC Motor test!");
  
  //bluetooth = new Bluetooth(&nav);
  
  // nav.setPrinter(Serial);
  nav.move_forward(0, 200);
  //nav.queueForward();
  //nav.queueForward();
  //nav.queueForward();
}

void loop() {
  //delay(1000);
  // bluetooth->BLEscan(); // connects to new device; if it's connected, does nothing
}
