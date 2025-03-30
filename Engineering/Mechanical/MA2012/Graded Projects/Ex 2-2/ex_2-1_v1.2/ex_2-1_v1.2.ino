#include <Servo.h>
#include "UCN5804.h"

// Stepper motor setup
#define motorSteps 200
UCN5804 stepperMotor(motorSteps, 13, 12, 7, 6);

// Servo motor setup
Servo servoMotor;

// DC motor setup
const int motorPin1 = 5;
const int motorPin2 = 11;

// Encoder setup
const int encoderPinA = 2;
const int encoderPinB = 3;
volatile long encoderCount = 0;

// Other variables
int potValue;
int toggleSwitchState;
int pushButtonState;
int servoPosition = 90;
bool isServoInPosition = false;

void setup() {
  // Input setup
  pinMode(8, INPUT_PULLUP); // pushButtonPin
  pinMode(9, INPUT_PULLUP); // toggleSwitchPin
  pinMode(A0, INPUT);       // potentiometerPin

  // Servo setup
  servoMotor.attach(4);
  servoMotor.write(servoPosition);

  // Stepper setup
  stepperMotor.setSpeed(60);

  // DC motor setup
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);

  // Encoder setup
  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);
  attachInterrupt(digitalPinToInterrupt(encoderPinA), encoderInterrupt, RISING);

  // Serial setup
  Serial.begin(9600);
}

void loop() {
  // Read inputs
  potValue = analogRead(A0);
  toggleSwitchState = digitalRead(9);
  pushButtonState = digitalRead(8);

  // Update servo position
  servoPosition = map(potValue, 0, 1023, 45, 135);
  servoMotor.write(servoPosition);

  // Check if the servo is in the desired position
  isServoInPosition = (servoPosition >= 80 && servoPosition <= 100);

  // Stepper motor control
  if (pushButtonState == LOW && isServoInPosition && toggleSwitchState == HIGH) {
    stepperMotor.step(10);
  } else if (pushButtonState == LOW && isServoInPosition && toggleSwitchState == LOW) {
    stepperMotor.step(-10);
  }

  // DC motor control
  if (isServoInPosition) {
    analogWrite(motorPin1, 255);
    analogWrite(motorPin2, 0);
  } else {
    analogWrite(motorPin1, 0);
    analogWrite(motorPin2, 0);
  }

  // Debugging
  Serial.print("Potentiometer Value: ");
  Serial.println(potValue);
}

void encoderInterrupt() {
  if (digitalRead(encoderPinB) == HIGH) {
    encoderCount++;
  } else {
    encoderCount--;
  }
}
