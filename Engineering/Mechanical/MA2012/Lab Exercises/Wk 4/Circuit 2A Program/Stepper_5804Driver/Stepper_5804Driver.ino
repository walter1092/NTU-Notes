#include "UCN5804.h"

#define motorSteps 200     // change this depending on the number of steps
                           // per revolution of your motor

// define the pins that the motor is attached to. You can use
// any digital I/O pins.
#define dirPin   13
#define stepPin  12
#define halfPin  7
#define phasePin 6

// initialize of the Stepper library:
UCN5804 myStepper(motorSteps, dirPin, stepPin, halfPin, phasePin);

void setup() {
  // set the motor speed at 60 RPMS:
  myStepper.setSpeed(60);
  
  // Initialize the Serial port:
  Serial.begin(9600);
}

void loop() {
  // Step forward 100 steps:
  Serial.println("Forward");
  myStepper.step(100);
  delay(500);

  // Step backward 100 steps:
  Serial.println("Backward");
  myStepper.step(-100);
  delay(500);
}
