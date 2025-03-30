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
int servoMin = 80;      // Minimum servo position
int servoMax = 100;     // Maximum servo position
int motorSpeed = 150;   // DC motor speed

bool isButtonPressed = false;
bool isServoInPosition = false;

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
  servoPosition = map(potValue, 0, 1023, servoMin, servoMax);
  servoMotor.write(servoPosition);

  // Read toggle switch state for motor direction
  int toggleSwitchState = digitalRead(toggleSwitchPin);

  // Read push button state
  int pushButtonState = digitalRead(pushButtonPin);

  // Check if the servo is in the desired position
  isServoInPosition = (servoPosition >= servoMin && servoPosition <= servoMax);

  // If the button is pressed and the servo is in position, activate the motor
  if (pushButtonState == LOW && isServoInPosition) {
    isButtonPressed = true;

    // Set motor direction based on the toggle switch state
    if (toggleSwitchState == HIGH) {
      // Raise the cable
      digitalWrite(dcMotorA1, HIGH);
      digitalWrite(dcMotorA2, LOW);
    } else {
      // Lower the cable
      digitalWrite(dcMotorA1, LOW);
      digitalWrite(dcMotorA2, HIGH);
    }

    // Set motor speed
    analogWrite(dcMotorA1, motorSpeed);
  } else {
    // Release the button or servo is not in position, stop the motor
    if (isButtonPressed || !isServoInPosition) {
      // Stop the motor
      digitalWrite(dcMotorA1, LOW);
      digitalWrite(dcMotorA2, LOW);

      isButtonPressed = false;
    }
  }

  // Print potentiometer value to Serial Monitor
  Serial.print("Potentiometer Value: ");
  Serial.println(potValue);
}
