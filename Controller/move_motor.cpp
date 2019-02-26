#include "move_motor.h"


Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); //specific address
Adafruit_DCMotor *steer = AFMS.getMotor(3);
Adafruit_DCMotor *frontDrive = AFMS.getMotor(4);
Adafruit_DCMotor *rearDrive = AFMS.getMotor(2);


void Navigation::MotorSpeed(int force){
  if(force >= 200){
    force = 200;
  }
  else if(force <= -200){
    force =-200;
  }

  if(force > 0){
     frontDrive->run(FORWARD);
     rearDrive->run(FORWARD);
     
     frontDrive->setSpeed(force);
     rearDrive->setSpeed(force);
  }
  else{
    force *= -1;
     frontDrive->run(BACKWARD);
     rearDrive->run(BACKWARD);

      frontDrive->setSpeed(force);
      rearDrive->setSpeed(force);
  }
  

  
}

void Navigation::SteerSpeed(int force){
  if(force >= 200){
    force = 200;
  }
  else if(force <= -200){
    force =-200;
  }
  steer->setSpeed(force);

  if(force > 0){
     steer->run(FORWARD);
  }
  else{
     steer->run(BACKWARD);
  }
}


void Navigation::move_forward(int force, int interval) {
  
  // create with the default frequency 1.6KHz
  AFMS.begin(1600);  
  
  // Set the speed to start, from 0 (off) to 255 (max speed)
  
  frontDrive->setSpeed(force);
  rearDrive->setSpeed(force);
  steer->setSpeed(force);

  //start motors
  steer->run(FORWARD);
  frontDrive->run(FORWARD);
  rearDrive->run(FORWARD);

}

void Navigation::stop_all(){
  // halt robot
  frontDrive->setSpeed(0);
  rearDrive->setSpeed(0);
  steer->setSpeed(0);
  delay(100);
  //kill motors
  frontDrive->run(RELEASE);
  rearDrive->run(RELEASE);
  steer->run(RELEASE);
}


// void Navigation::setPrinter(Print &p) {
//   printer = &p;
// }
