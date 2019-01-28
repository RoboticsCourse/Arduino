#include <SPI.h>
#include "Adafruit_BLE_UART.h"

#include "bluetooth.h"
#include "move_motor.h"

// Connect CLK/MISO/MOSI to hardware SPI
// e.g. On UNO & compatible: CLK = 13, MISO = 12, MOSI = 11
#define ADAFRUITBLE_REQ 10
#define ADAFRUITBLE_RDY 2     // This should be an interrupt pin, on Uno thats #2 or #3
#define ADAFRUITBLE_RST 9

Adafruit_BLE_UART BTLEserial = Adafruit_BLE_UART(ADAFRUITBLE_REQ, ADAFRUITBLE_RDY, ADAFRUITBLE_RST);
aci_evt_opcode_t laststatus = ACI_EVT_DISCONNECTED;

Navigation *navo;

Bluetooth::Bluetooth(HardwareSerial & p, Navigation *navigation){
    navo = navigation;
    printer = &p;
    BTLEserial.setDeviceName("Car_1"); /* 7 characters max! */
    BTLEserial.begin();
    printer->println(F("Adafruit Bluefruit Low Energy nRF8001 Print echo demo"));
    if(BTLEserial.available()){
        printer->println(F("Available"));
    }
    else{
        printer->println(F("Unavailable"));
    }
}

void Bluetooth::BLEscan(){
  // Tell the nRF8001 to do whatever it should be working on.
  BTLEserial.pollACI();
  // Ask what is our current status
  aci_evt_opcode_t status = BTLEserial.getState();
  // If the status changed....
  if (status != laststatus) {
    // print it out!
    if (status == ACI_EVT_DEVICE_STARTED) {
        printer->println(F("* Advertising started"));
    }
    if (status == ACI_EVT_CONNECTED) {
        printer->println(F("* Connected!"));
    }
    if (status == ACI_EVT_DISCONNECTED) {
        printer->println(F("* Disconnected or advertising timed out"));
    }
    // OK set the last status change to this one
    laststatus = status;
  }

  if (status == ACI_EVT_CONNECTED) {
    // Lets see if there's any data for us!
    if (BTLEserial.available()) {
      printer->print("* "); printer->print(BTLEserial.available()); printer->println(F(" bytes available from BTLE"));
    }
    // OK while we still have something to read, get a character and print it out
    while (BTLEserial.available()) {
      char c = BTLEserial.read();
      printer->print(c);
      if(c == 'a'){
        navo->queueForward();
      }
    }

    // Next up, see if we have any data to get from the Serial console

    if (printer->available()) {
      // Read a line from Serial
      printer->setTimeout(100); // 100 millisecond timeout
      String s = printer->readString();

      // We need to convert the line to bytes, no more than 20 at this time
      uint8_t sendbuffer[20];
      s.getBytes(sendbuffer, 20);
      char sendbuffersize = min(20, s.length());

      printer->print(F("\n* Sending -> \"")); printer->print((char *)sendbuffer); printer->println("\"");

      // write the data
      BTLEserial.write(sendbuffer, sendbuffersize);
    }
  }
}
