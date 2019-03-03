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

  if (status != laststatus) {
    // OK set the last status change to this one
    laststatus = status;
  }

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

    // Next up, see if we have any data to get from the Serial console

    // if (printer->available()) {
    //   // Read a line from Serial
    //   printer->setTimeout(100); // 100 millisecond timeout
    //   String s = printer->readString();

    //   // We need to convert the line to bytes, no more than 20 at this time
    //   uint8_t sendbuffer[20];
    //   s.getBytes(sendbuffer, 20);
    //   char sendbuffersize = min(20, s.length());

    //   printer->print(F("\n* Sending -> \"")); printer->print((char *)sendbuffer); printer->println("\"");

    //   // write the data
    //   BTLEserial.write(sendbuffer, sendbuffersize);
    // }
  }
}
