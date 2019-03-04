#include "bluetooth.h"

// Connect CLK/MISO/MOSI to hardware SPI
// e.g. On UNO & compatible: CLK = 13, MISO = 12, MOSI = 11
#define ADAFRUITBLE_REQ 10
#define ADAFRUITBLE_RDY 2     // This should be an interrupt pin, on Uno thats #2 or #3
#define ADAFRUITBLE_RST 9

Adafruit_BLE_UART BTLEserial = Adafruit_BLE_UART(ADAFRUITBLE_REQ, ADAFRUITBLE_RDY, ADAFRUITBLE_RST);
aci_evt_opcode_t laststatus = ACI_EVT_DISCONNECTED;


Navigation *navo;

int force = 0;
bool motor_on = false;
bool steer_on = false; 
bool neg = false;

Bluetooth::Bluetooth(Navigation *navigation) {
  navo = navigation;
  BTLEserial.setDeviceName("Car_1"); /* 7 characters max! */
  BTLEserial.begin();
}

void Bluetooth::BLEscan() {
  // Tell the nRF8001 to do whatever it should be working on.
  BTLEserial.pollACI();

  aci_evt_opcode_t status = BTLEserial.getState();
  
  if (status == ACI_EVT_CONNECTED) {
    // Lets see if there's any data for us!
    /*
    if (BTLEserial.available()) {
      printer->print("* "); printer->print(BTLEserial.available()); printer->println(F(" bytes available from BTLE"));
    }
    */
    // OK while we still have something to read, get a character and print it out
    while (BTLEserial.available()) {
      char c = BTLEserial.read(); // read input from phone
      
      if (c == 0) {
        if (neg) { // direction
          force *= -1;
          neg = false;
        }
        if (motor_on) {
          navo->MotorSpeed(force);
          motor_on = false;
        }
        if (steer_on) {
          navo->SteerSpeed(force);
          steer_on = false;
        }
        force = 0;
      }
      else if (c == 'F') {
        motor_on = true;
      }
      else if (c == 'S') {
        steer_on = true;
      }
      else if (c == 'X') {
        navo->stopMotors();
      }
      else if (c == '-') {
        neg = true;
      }
      else {
        int x = c - '0'; // convert char to int
        force = force * 10 + x;
      }
    }
  }
}

void Bluetooth::sendDistance(String prefix, int distance){
    prefix.concat(String(distance));

    uint8_t sendbuffer[20];
    prefix.getBytes(sendbuffer, 20);
    char sendbuffersize = min(20, prefix.length());
    BTLEserial.write(sendbuffer, sendbuffersize);
}
