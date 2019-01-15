/* 
This is a test sketch for the Adafruit assembled Motor Shield for Arduino v2
It won't work with v1.x motor shields! Only for the v2's with built in PWM
control

For use with the Adafruit Motor Shield v2 
---->	http://www.adafruit.com/products/1438
*/

#include <Wire.h>
#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *steer = AFMS.getMotor(3);
Adafruit_DCMotor *frontDrive = AFMS.getMotor(4);
Adafruit_DCMotor *rearDrive = AFMS.getMotor(2);
// You can also make another motor on port M2
//Adafruit_DCMotor *myOtherMotor = AFMS.getMotor(2);

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  // Set the speed to start, from 0 (off) to 255 (max speed)
  steer->setSpeed(255);
  frontDrive->setSpeed(255);
  rearDrive->setSpeed(255);

  // start motors
  steer->run(FORWARD);
  steer->run(RELEASE);
  frontDrive->run(FORWARD);
  frontDrive->run(RELEASE);
  rearDrive->run(FORWARD);
  rearDrive->run(RELEASE);

  // run for 1 second
  steer->run(FORWARD);
  frontDrive->run(FORWARD);
  rearDrive->run(FORWARD);
  
  delay(3000);
  //steer->run(BACKWARD);
  //delay(3000);


  // halt robot, kill motors
  steer->setSpeed(0);
  frontDrive->setSpeed(0);
  rearDrive->setSpeed(0);
  delay(100);  
  steer->run(RELEASE);
  frontDrive->run(RELEASE);
  rearDrive->run(RELEASE);
}

void loop() {
  delay(1000);
}
