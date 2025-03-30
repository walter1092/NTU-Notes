#include <Servo.h>
#include "UCN5804.h"

// Pins
const int pushButtonPin = 8;
const int potentiometerPin = A0;
const int toggleSwitchPin = 9;
const int servoMotorPin = 4;
const int dirPin = 13;
const int stepPin = 12;
const int halfPin = 7;
const int phasePin = 6;

// Stepper
#define motorSteps 200 // Number of steps per revolution for the stepper motor
UCN5804 stepperMotor(motorSteps, dirPin, stepPin, halfPin, phasePin);

// Servo
Servo servoMotor;

// Variables
int servoPosition = 90; // Initial servo position
bool isServoInPosition = false;

void setup() {
  pinMode(pushButtonPin, INPUT_PULLUP);
  pinMode(toggleSwitchPin, INPUT_PULLUP);
  servoMotor.attach(servoMotorPin);
  stepperMotor.setSpeed(60); // Set the stepper motor speed

  // Move the servo to the initial position
  servoMotor.write(servoPosition);
  delay(500);

  // Start serial communication
  Serial.begin(9600);
}

void loop() {
  // Read potentiometer value to control servo position
  int potValue = analogRead(potentiometerPin);
  servoPosition = map(potValue, 0, 1023, 45, 135);
  servoMotor.write(servoPosition);

  // Read toggle switch state for motor direction
  int toggleSwitchState = digitalRead(toggleSwitchPin);

  // Read push button state
  int pushButtonState = digitalRead(pushButtonPin);

  // Check if the servo is in the desired position
  isServoInPosition = (servoPosition >= 80 && servoPosition <= 100);

  // If the button is pressed, the servo is in position, and the toggle switch is HIGH, activate the stepper motor
  if (pushButtonState == LOW && isServoInPosition && toggleSwitchState == HIGH) {
    stepperMotor.step(10); // Step forward 10 steps
  } else if (pushButtonState == LOW && isServoInPosition && toggleSwitchState == LOW) {
    stepperMotor.step(-10); // Step backward 10 steps
  } else {
    // Stepper motor should stop; the library handles this by not stepping further
  }

  // Print potentiometer value to Serial Monitor
  Serial.print("Potentiometer Value: ");
  Serial.println(potValue);
}
