#include "IR.h"

#define SIDE_TRIG_PIN 5
#define SIDE_ECHO_PIN 6
#define FRONT_TRIG_PIN 3 // white is trig
#define FRONT_ECHO_PIN 8 // brown is echo
#define SIDE_THRESH_HIGH 70
#define SIDE_THRESH_LOW 45
#define FRONT_THRESH 50
#define SPEED 80

// defines distance variables
int sideDist;
int frontDist;
int tmp;

Navigation *navi;

IR::IR(Navigation *navigation){
     // communication with sensors for debugging
    Serial.begin(9600);
    navi = navigation;
    // set sensor pins accordingly
    pinMode(SIDE_TRIG_PIN, OUTPUT);
    pinMode(SIDE_ECHO_PIN, INPUT);
    pinMode(FRONT_TRIG_PIN, OUTPUT);
    pinMode(FRONT_ECHO_PIN, INPUT);
}

void readSensors() {
    
    // clear the trig pins
    digitalWrite(SIDE_TRIG_PIN, LOW);
    digitalWrite(FRONT_TRIG_PIN, LOW);
    delayMicroseconds(2);

    // set the trig pins on HIGH state for 10 micro seconds
    digitalWrite(SIDE_TRIG_PIN, HIGH);
    digitalWrite(FRONT_TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(SIDE_TRIG_PIN, LOW);
    digitalWrite(FRONT_TRIG_PIN, LOW);

    // read the echo pins, get the sound wave travel time in microseconds, calculate the distance
    tmp = pulseIn(SIDE_ECHO_PIN, HIGH) * 0.034/2;
    sideDist = (tmp != 0) ? tmp : sideDist;
    tmp = pulseIn(FRONT_ECHO_PIN, HIGH) * 0.034/2;
    frontDist = (tmp != 0) ? tmp : frontDist;
}


void IR::sensorLoop(){
    readSensors();

    // debug code block here
    Serial.print("Front Distance: ");
    Serial.print(frontDist);
    Serial.print("\tSide Distance: ");
    Serial.println(sideDist);

    if (frontDist < FRONT_THRESH) {
        if (sideDist < SIDE_THRESH_HIGH) {  // when encountering front and side walls, backup to the right
            navi->turnRight(255);
            navi->goBackward(80);
            delay(1500);
        } else {                            // when encountering only the front wall, back up to the left
            navi->turnLeft(255);
            navi->goBackward(80);
            delay(1500);
        }
    } else {    // when in a hallway, try to keep an equal distance between the walls
        if (sideDist < SIDE_THRESH_LOW) {
            navi->turnLeft(255);
            navi->goForward(80);
        } else if (sideDist < SIDE_THRESH_HIGH){
            navi->straighten();
            navi->goForward(80);
        } else {
            navi->turnRight(255);
            navi->goForward(80);
        }
    }
}


