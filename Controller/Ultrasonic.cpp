#include "Ultrasonic.h"

#define SIDE_TRIG_PIN 5
#define SIDE_ECHO_PIN 6
#define FRONT_TRIG_PIN 4
#define FRONT_ECHO_PIN 8
#define SIDE_THRESH_HIGH 300
#define SIDE_THRESH_MED 70
#define SIDE_THRESH_LOW 45
#define FRONT_THRESH 30
#define SPEED 80

#define FRONT_ENABLED true
#define SIDE_ENABLED true

// defines distance variables

int tmp;
int wheel_speed;
int turn_speed;
int sideDist;
int frontDist;
Navigation *navi;

long timestamp;
enum states {hallway, leftTurn, overshoot, backRight, continueForward};
states state;

US::US(Navigation *navigation){
    // communication with sensors for debugging
    // Serial.begin(9600);
    navi = navigation;
    sideDist = 0;
    frontDist = 0;
    wheel_speed = 60;
    turn_speed = 255;
    timestamp = 0;
    state = hallway;

    // set sensor pins accordingly
    pinMode(SIDE_TRIG_PIN, OUTPUT);
    pinMode(SIDE_ECHO_PIN, INPUT);
    pinMode(FRONT_TRIG_PIN, OUTPUT);
    pinMode(FRONT_ECHO_PIN, INPUT);
}

int readSensor(int trig_pin, int echo_pin) {    
    digitalWrite(trig_pin, LOW);
    delayMicroseconds(2);
    digitalWrite(trig_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig_pin, LOW);
    // read the echo pins, get the sound wave travel time in microseconds, calculate the distance
    return pulseIn(echo_pin, HIGH) * 0.017;
}


void US::sensorLoop() {

    if(FRONT_ENABLED) frontDist = readSensor(FRONT_TRIG_PIN, FRONT_ECHO_PIN);
    if(SIDE_ENABLED) sideDist = readSensor(SIDE_TRIG_PIN, SIDE_ECHO_PIN);
    
    // debug code block here
    //Serial.print("Front Distance: ");
    //Serial.print(frontDist);
    //Serial.print("\tSide Distance: ");
    //Serial.println(sideDist);

    switch(state) {
        case hallway:

            // if about to crash, don't
            if (frontDist < FRONT_THRESH) {
                state = leftTurn;
                timestamp = millis() + 4000;
                break;
            }

            // keep going straight otherwise
            if (sideDist < SIDE_THRESH_LOW) {
                navi->turnLeft(turn_speed);
                navi->goForward(wheel_speed);
            } else if (sideDist < SIDE_THRESH_MED){
                navi->straighten();
                navi->goForward(wheel_speed);
            } else if (sideDist < SIDE_THRESH_HIGH){
                if (millis() > timestamp) {
                    navi->turnRight(turn_speed);
                    navi->goForward(wheel_speed);
                    timestamp = millis() + 100;
                } else{
                    navi->straighten();
                    navi->goForward(wheel_speed);
                }
            } else {
                state = overshoot;
                timestamp = millis() + 2500;
            }

            break;

        case leftTurn:

            navi->turnRight(turn_speed);
            navi->goBackward(wheel_speed);
            
            if (millis() > timestamp) {
                state = continueForward;
                timestamp = millis() + 3000;
            }
            break;

        case overshoot:

            // if about to crash, don't
            if (frontDist < FRONT_THRESH) {
                state = leftTurn;
                timestamp = millis() + 4000;
                break;
            }

            navi->straighten();
            navi->goForward(wheel_speed);

            if (millis() > timestamp) {
                state = backRight;
                timestamp = millis() + 4000;
            }

            break;

        case backRight:

            navi->turnLeft(turn_speed * 0.8);
            navi->goBackward(wheel_speed);

            if (millis() > timestamp) {
                state = continueForward;
                timestamp = millis() + 5000;
            }

            break;

        case continueForward:

            // if about to crash, don't
            if (frontDist < FRONT_THRESH) {
                state = leftTurn;
                timestamp = millis() + 4000;
                break;
            }

            navi->straighten();
            navi->goForward(wheel_speed);

            if (millis() > timestamp) state = hallway;
            break;
    }
    
}

int US::get_wheel_speed() { return wheel_speed; }
int US::get_turn_speed() { return turn_speed; }
int US::get_side_dist() { return sideDist; }
int US::get_front_dist() { return frontDist; }