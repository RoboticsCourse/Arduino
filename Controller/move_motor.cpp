#include "Arduino.h"
#include <Wire.h>
#include <Adafruit_MotorShield.h>

#include "QueueArray.h"
#include "move_motor.h"


Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); //specific address
Adafruit_DCMotor *steer = AFMS.getMotor(3);
Adafruit_DCMotor *frontDrive = AFMS.getMotor(4);
Adafruit_DCMotor *rearDrive = AFMS.getMotor(2);

int motors[4];
int moving;

struct action{
  int force;
  int type;
  int interval;
};

QueueArray <action *> queue;

Navigation::Navigation(){
  
  moving = 0; //not moving
}

void Navigation::queryCommand(){
  if(!moving){
    if(!queue.isEmpty()){
      action *movement = (action *) queue.dequeue();
      switch(movement->type){
        case 1:
          move_forward(movement->force, movement->interval);
          if (printer){
              printer->println("dequeued");
          }
          break;
      }
    }
  }
}

void Navigation::queueForward(){
  action *movement = (action *) malloc(sizeof(action));
  movement->type = 1;
  movement->interval = 1000;
  movement->force = 100;
  queue.enqueue(movement);
  
  if (printer){
    printer->println("enqueued");
  }
  
}

void Navigation::move_forward(int force, int interval) {
  
  moving = 1; //is moving now
  // create with the default frequency 1.6KHz
  AFMS.begin(1600);  
  
  // Set the speed to start, from 0 (off) to 255 (max speed)
  
  frontDrive->setSpeed(interval);
  rearDrive->setSpeed(interval);

  //start motors
  steer->run(FORWARD);
  frontDrive->run(FORWARD);
  rearDrive->run(FORWARD);

  // run for 1 second
  delay(interval);
  
  // halt robot
  frontDrive->setSpeed(0);
  rearDrive->setSpeed(0);
  delay(100);
  //kill motors
  frontDrive->run(RELEASE);
  rearDrive->run(RELEASE);
  moving = 0;
}

void Navigation::turn(int force, int interval) {
  
  moving = 1; //is moving now
  steer->setSpeed(force);

  delay(interval);
  
  //turn on steering motor
  steer->run(FORWARD);
  steer->run(RELEASE);

  steer->setSpeed(0);
  delay(100);
  steer->run(RELEASE);
  moving = 0;
}

void Navigation::setPrinter(Print & p) {
  printer = &p;
}
