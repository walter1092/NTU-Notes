// General
#include "UCN5804.h"
#include <Servo.h>
const int baud = 9600;

// Servo
const int servoPin = 3;

// Stepper
const int stepperSteps = 200;     // steps per revolution
const int stepsToClose = 100;     // how many steps to take to close the door
const int dirPin = 13;
const int stepPin = 12;
const int halfPin = 11;
const int phasePin = 10;
const int stepperSpeed = 60;  // RPM

// Solenoid
const int solenoidPin = 5;
const int openState = 1;
const int closedState = 0;

// Motion sensor 
const int motionPin = 4;

// Distance sensor
const int trigPin = 6;
const int echoPin = 7 ;
const int triggerDistance = 20;   // cm

// Game variables
int hasPassedEntrance = 0;
int hasPassedTreasureRoom = 0;

Servo servo;
UCN5804 stepper(stepperSteps, dirPin, stepPin, halfPin, phasePin);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(baud);
  stepper.setSpeed(stepperSpeed);
  servo.attach(servoPin);

  pinMode(solenoidPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(motionPin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  digitalWrite(solenoidPin, openState);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {

  if (hasPassedEntrance == 0) {
    int motionState = digitalRead(motionPin);
    if (motionState == 1) {
      Serial.println("Motion sensor detected someone!");
      digitalWrite(solenoidPin, closedState);
      servoClose(45, 135);
      hasPassedEntrance = 1;
      delay(2000);
    }
  }

  else if (hasPassedEntrance == 1 && hasPassedTreasureRoom == 0) {
    float distance = getDistance();
    if (distance < triggerDistance) {
      Serial.println("Distance sensor detected someone!");
      stepper.step(stepsToClose);
      delay(100);
      hasPassedTreasureRoom = 1;
    }
  }
  delay(10);
}

float getDistance() {
  // return the distance in cm
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  long duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  float distance = duration * 0.034 / 2;
  Serial.println(distance);
  return distance;
}

void servoClose(int startPos, int endPos, unsigned long delayTime) {
  for (int pos = startPos; pos <= endPos; pos++) {
    servo.write(pos);
    delay(delayTime);
  }
}

void led_blink(int blinkCount, unsigned long delayTime) {
  for (int i = 0; i <= blinkCount; i++) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(delayTime);
    digitalWrite(LED_BUILTIN, LOW);
    delay(delayTime);
  }
}