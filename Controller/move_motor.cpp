#include "move_motor.h"


Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *frontMotor = AFMS.getMotor(4);
Adafruit_DCMotor *rearMotor = AFMS.getMotor(2);
Adafruit_DCMotor *turnMotor = AFMS.getMotor(3);

int limitSpeed(int force, int lower_limit, int upper_limit){
  if(force >= upper_limit){
    force = upper_limit;
  }
  else if(force <= lower_limit){
    force = lower_limit;
  }
  return force;
}

void Navigation::goForward(int speed) {
    frontMotor->setSpeed(speed);
    frontMotor->run(FORWARD);
    rearMotor->setSpeed(speed);
    rearMotor->run(FORWARD);
}

void Navigation::goBackward(int speed) {
    frontMotor->setSpeed(speed);
    frontMotor->run(BACKWARD);
    rearMotor->setSpeed(speed);
    rearMotor->run(BACKWARD);   
}

void Navigation::straighten() {
    turnMotor->setSpeed(0);
    delay(1);
    turnMotor->run(RELEASE);
}

void Navigation::turnLeft(int speed) {
    turnMotor->setSpeed(speed);
    turnMotor->run(FORWARD);
}

void Navigation::turnRight(int speed) {
    turnMotor->setSpeed(speed);
    turnMotor->run(BACKWARD);
}


void Navigation::MotorSpeed(int speed){
  //speed = limitSpeed(speed, -200,200);
  if(speed > 0) goForward(speed);
  else{
    speed *= -1;
    goBackward(speed);
  }
}

void Navigation::SteerSpeed(int speed){
  //speed = limitSpeed(speed, -200,200);
  if(speed > 0) {
    turnMotor->run(FORWARD);
  }
  else {
    speed *= -1;
    turnMotor->run(BACKWARD);
  }
  turnMotor->setSpeed(speed);
}


void Navigation::setup(){
  // create with the defalt frequency 1.6KHz
  AFMS.begin(1600);
}

void Navigation::stopMotors(){
  // halt robot
  frontMotor->setSpeed(0);
  rearMotor->setSpeed(0);
  turnMotor->setSpeed(0);
  delay(100);
  //kill motors
  frontMotor->run(RELEASE);
  rearMotor->run(RELEASE);
  turnMotor->run(RELEASE);
}
