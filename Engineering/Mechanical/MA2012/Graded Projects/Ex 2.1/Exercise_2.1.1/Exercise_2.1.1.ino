#include <Servo.h>

// Pins
const int pushButtonPin = 8;
const int potentiometerPin = A0;
const int toggleSwitchPin = 9;
const int servoMotorPin = 4;
const int dcMotorA1 = 5;
const int dcMotorA2 = 11;

// Servo
Servo servoMotor;

// Variables
int servoPosition = 90; // Initial servo position
int motorSpeed = 255;   // DC motor speed (0-255)

void setup() {
  pinMode(pushButtonPin, INPUT_PULLUP); // Internal pull-up resistor
  pinMode(toggleSwitchPin, INPUT_PULLUP); // Internal pull-up resistor
  servoMotor.attach(servoMotorPin);
  pinMode(dcMotorA1, OUTPUT);
  pinMode(dcMotorA2, OUTPUT);

  // Move the servo to the initial position
  servoMotor.write(servoPosition);
  delay(500); // Allow time for the servo to move

  // Start serial communication
  Serial.begin(9600);
}

void loop() {
  // Read potentiometer value to control servo position
  int potValue = analogRead(potentiometerPin);
  servoPosition = map(potValue, 0, 1023, 45, 135);
  servoMotor.write(servoPosition);

  // Check if the servo is in the desired position
  bool isServoInPosition = (servoPosition >= 80 && servoPosition <= 100);

  // Read toggle switch state for motor direction
  int toggleSwitchState = digitalRead(toggleSwitchPin);

  // Read push button state
  int pushButtonState = digitalRead(pushButtonPin);

  if (isServoInPosition && pushButtonState == LOW) {
    if (toggleSwitchState == HIGH) {
      // Raise the cable
      analogWrite(dcMotorA1, motorSpeed);
      analogWrite(dcMotorA2, 0);
    } else {
      // Lower the cable
      analogWrite(dcMotorA1, 0);
      analogWrite(dcMotorA2, motorSpeed);
    }
  } else {
    // Stop the motor
    analogWrite(dcMotorA1, 0);
    analogWrite(dcMotorA2, 0);
  }

  // Print potentiometer value to Serial Monitor
  Serial.print("Potentiometer Value: ");
  Serial.println(potValue);
}
