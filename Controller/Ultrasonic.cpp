#include "Ultrasonic.h"

#define LEFT_TRIG_PIN 5
#define LEFT_ECHO_PIN 6
#define RIGHT_TRIG_PIN 4 // white is trig
#define RIGHT_ECHO_PIN 8 // brown is echo
#define HIGH_THRESH 100
#define LOW_THRESH 70
#define SPEED 80

// defines distance variables

int tmp;
int wheel_speed;
int turn_speed;
int leftDist;
int rightDist;
Navigation *navi;


bool right = true;
bool left = true;




US::US(Navigation *navigation){
     // communication with sensors for debugging
    Serial.begin(9600);
    navi = navigation;
    leftDist = 0;
    rightDist = 0;
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
    if(right){
        rightDist = readSensor(RIGHT_TRIG_PIN, RIGHT_ECHO_PIN);
    }
    if(left){
        leftDist = readSensor(LEFT_TRIG_PIN, LEFT_ECHO_PIN);
    }
    
    // debug code block here
    Serial.print("Left Distance: ");
    Serial.print(leftDist);
    Serial.print("\tRight Distance: ");
    Serial.println(rightDist);

    if (rightDist < LOW_THRESH) {
        if (leftDist < LOW_THRESH) {
            navi->turnLeft(turn_speed);
            navi->goBackward(wheel_speed);
            delay(1500);
        } else {
            navi->turnLeft(turn_speed);
            navi->goForward(wheel_speed);
        }
    } else if (rightDist < HIGH_THRESH) {
        if (leftDist < LOW_THRESH) {
            navi->turnRight(turn_speed);
            navi->goForward(wheel_speed);
        }
    } else {
        navi->turnRight(turn_speed);
        navi->goForward(wheel_speed);
    }
}

int US::get_wheel_speed(){
    return wheel_speed;
}
int US::get_turn_speed(){
    return turn_speed;
}
int US::get_left_dist(){
    return leftDist;
}
int US::get_right_dist(){
    return rightDist;
}