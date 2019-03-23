#include "Ultrasonic.h"

#define SIDE_TRIG_PIN 5
#define SIDE_ECHO_PIN 6
#define FRONT_TRIG_PIN 4 // white is trig
#define FRONT_ECHO_PIN 8 // brown is echo
#define SIDE_THRESH_HIGH 70
#define SIDE_THRESH_LOW 45
#define FRONT_THRESH 50
#define SPEED 80

// defines distance variables

int tmp;
int wheel_speed;
int turn_speed;
int sideDist;
int frontDist;
Navigation *navi;


bool front = true;
bool side = true;




US::US(Navigation *navigation){
     // communication with sensors for debugging
    Serial.begin(9600);
    navi = navigation;
    sideDist = 0;
    frontDist = 0;
    wheel_speed = 60;
    turn_speed = 255;
    // set sensor pins accordingly
}

int readSensor(int trig_pin, int echo_pin) {    
    pinMode(trig_pin, OUTPUT);
    digitalWrite(trig_pin, LOW);
    delayMicroseconds(2);
    digitalWrite(trig_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig_pin, LOW);
    pinMode(echo_pin, INPUT);
    // read the echo pins, get the sound wave travel time in microseconds, calculate the distance
    return pulseIn(echo_pin, HIGH) * 0.034/2;
}


void US::sensorLoop(){
    if(front){
        frontDist = readSensor(FRONT_TRIG_PIN, FRONT_ECHO_PIN);
    }
    if(side){
        sideDist = readSensor(SIDE_TRIG_PIN, SIDE_ECHO_PIN);
    }
    
    // debug code block here
    //Serial.print("Front Distance: ");
    //Serial.print(frontDist);
    //Serial.print("\tSide Distance: ");
    //Serial.println(sideDist);

    if (frontDist < FRONT_THRESH) {
        if (sideDist < SIDE_THRESH_HIGH) {  // when encountering front and side walls, backup to the right
            navi->turnRight(turn_speed);
            navi->goBackward(wheel_speed);
            delay(1500);
        } else {                            // when encountering only the front wall, back up to the left
            navi->turnLeft(turn_speed);
            navi->goBackward(wheel_speed);
            delay(1500);
        }
    } else {    // when in a hallway, try to keep an equal distance between the walls
        if (sideDist < SIDE_THRESH_LOW) {
            navi->turnLeft(turn_speed);
            navi->goForward(wheel_speed);
        } else if (sideDist < SIDE_THRESH_HIGH){
            navi->straighten();
            navi->goForward(wheel_speed);
        } else {
            navi->turnRight(turn_speed);
            navi->goForward(wheel_speed);
        }
    }
    
}

int US::get_wheel_speed(){
    return wheel_speed;
}
int US::get_turn_speed(){
    return turn_speed;
}
int US::get_side_dist(){
    return sideDist;
}
int US::get_front_dist(){
    return frontDist;
}