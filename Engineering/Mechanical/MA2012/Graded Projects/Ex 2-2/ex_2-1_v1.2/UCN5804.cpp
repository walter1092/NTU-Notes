/*
  UCN5804.cpp - Library for Stepper Driver
  Pins (numbered anti-clockwise from upper left):
  1: OUTPUT_B
  2: K_BD
  3: OUTPUT_D
  4: GND
  5: GND
  6: OUTPUT_C
  7: K_AC
  8: OUTPUT_A
  9: ONE-PHASE
  10: HALF-STEP
  11: STEP INPUT
  12: GND
  13: GND
  14: DIRECTIOn
  15: OUTPUT ENABLE
  16: SUPPLY
  Created by Lim Zhen Yi
*/

#include "Arduino.h"
#include "UCN5804.h"

/******************************************************************************
   Constructors
 ******************************************************************************/

UCN5804::UCN5804(int numberOfSteps, int dirPin, int stepPin, int halfPin, int phasePin)
{
  this->_dirPin = dirPin;
  this->_stepPin = stepPin;
  this->_halfPin = halfPin;
  this->_phasePin = phasePin;

  pinMode(_dirPin, OUTPUT);
  pinMode(_stepPin, OUTPUT);
  pinMode(_halfPin, OUTPUT);
  pinMode(_phasePin, OUTPUT);

  this->setMode(1);
  this->setSpeed(0);

  this->_numberOfSteps = numberOfSteps * 2;
}

/******************************************************************************
   User API
 ******************************************************************************/
/*
  Sets the speed in revs per minute, time delay for full steps

*/
void UCN5804::setSpeed(long whatSpeed)
{
  if (whatSpeed == 0) //prevent division by 0
  {
    whatSpeed = 1;
  }
  this->_stepDelay = 60L * 1000L * 1000L * 2 / this->_numberOfSteps / whatSpeed;
}

/*
  Sets the mode of operation: 1-Single Phase Full Step, 2-Two Phase Full Step, 3-Half Step

*/
void UCN5804::setMode(int mode)
{
  switch (mode) {
    case 1:	 // wave-drive sequence
      digitalWrite(_halfPin, LOW);
      digitalWrite(_phasePin, HIGH);
      this->_mode = 1;
      break;
    case 2:    // two-phase drive sequence
      digitalWrite(_halfPin, LOW);
      digitalWrite(_phasePin, LOW);
      this->_mode = 2;
      break;
    case 3:    // half-step drive sequence
      // Student needs to complete this part
      break;
  }
}

/*
  Moves the motor steps_to_move steps.  If the number is negative,
   the motor moves in the reverse direction.
*/
void UCN5804::step(int steps_to_move)
{
  if (steps_to_move > 0) {
    digitalWrite(_dirPin, HIGH);
    delayMicroseconds(tA);
    this->_direction = 1;
  }
  if (steps_to_move < 0) {
    digitalWrite(_dirPin, LOW);
    delayMicroseconds(tA);
    this->_direction = 0;
  }

  steps_to_move = abs(steps_to_move);

  //Serial.println("Stepping in Progress...");
  for (int i = 0; i < steps_to_move; i++)
  {
    //Serial.print("Step Number: ");
    //Serial.println(i);
    digitalWrite(_stepPin, LOW);
    delayMicroseconds(tC * 2);
    digitalWrite(_stepPin, HIGH);   // Sets step pin back to high in preparation for next step
    // Determines the time between each step to determine speed of stepping
    if (this->_mode == 3) {
      delayMicroseconds(_stepDelay);  		// If half-step is being used, use the calculated delay.
    } else {
      delayMicroseconds(_stepDelay * 2);		// Otherwise, delay needs to be twice as long to keep the same speed.
    }
  }
}
