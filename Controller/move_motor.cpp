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

int interval = 200;

struct action{
  int force;
  int type;
  int interval;
};

QueueArray <action *> queue;

Navigation::Navigation(){
  speed = 70;
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
  movement->interval = interval;
  movement->force = speed;
  queue.enqueue(movement);
  
  if (printer){
    printer->println("enqueued");
  }
  
}

void Navigation::IncreaseSpeed(){
  speed += 1;
  if(speed >= 200){
    speed = 200;
  }
  frontDrive->setSpeed(speed);
  rearDrive->setSpeed(speed);
}

void Navigation::DecreaseSpeed(){
  speed -= 1;
  if(speed <= 50){
    speed = 50;
  }
  frontDrive->setSpeed(speed);
  rearDrive->setSpeed(speed);
}


void Navigation::move_forward(int force, int interval) {
  
  moving = 1; //is moving now
  // create with the default frequency 1.6KHz
  AFMS.begin(1600);  
  
  // Set the speed to start, from 0 (off) to 255 (max speed)
  
  frontDrive->setSpeed(force);
  rearDrive->setSpeed(force);

  //start motors
  steer->run(FORWARD);
  frontDrive->run(FORWARD);
  rearDrive->run(FORWARD);
/*
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
  */
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
