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

volatile long int encoder_pos = 0;
unsigned int setPos;    // variable for target position
float val; //DC position in degree
int motor_speed;
int pin1 = 9;   // motor pin1
int pin2 = 10;  // motor pin2
int encoderPinA = 2;
int encoderPinB = 3;
int error = 5; // permissible error

int button = 5;  // assigns pin 5 to pushbutton
int push = 0; // variable for button state

int pot = A0; // assigns pin A0 to potentiometer
int hoist = 0;  // variable for hoist input position

void encoder() {
  if (digitalRead(encoderPinB) == HIGH) {
    encoder_pos++;
  } else {
    encoder_pos--;
  }
}

void MotorClockwise(int power) {
  if (power > 60) {
    analogWrite(pin1, power);
    digitalWrite(pin2, LOW);
  } else {
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
  }
}

void MotorCounterClockwise(int power) {
  if (power > 60) {
    analogWrite(pin2, power);
    digitalWrite(pin1, LOW);
  } else {
    digitalWrite(pin2, LOW);
    digitalWrite(pin1, LOW);
  }
}

void MoveDCMotor(int setPos)
{
  if (abs(setPos - encoder_pos) > error && (setPos > encoder_pos)) {
    motor_speed = 100; // set the speed of the motor
  }
  else if (abs(setPos - encoder_pos) > error && (setPos < encoder_pos)) {
    motor_speed = -100;
  }
  else {
    motor_speed = 0;
  }
  
  if (motor_speed > 0)
  {
    MotorClockwise(motor_speed);
  }
  else
  {
    MotorCounterClockwise(abs(motor_speed));
  }
  delay(10);
}

void setup()  // setup loop
{
  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(encoderPinA), encoder, RISING); // Enable the external interrupt

  myStepper.setSpeed(60);

  pinMode(button, INPUT); // declares pin 5 as input
  pinMode(pot, INPUT);   // declares pin A0 as input

  Serial.begin(9600);
}

void loop()
{
  hoist = analogRead(pot);
  push = digitalRead(button);
  setPos = (long)hoist * 374 / 1023; // maps 0V to 5V to 0 to 374 PPR (1 revolution)
  
  MoveDCMotor(setPos);

  //Convert encoder reading to degrees
  val = encoder_pos * 360.0 / 374;
  if (val >= 80 & val <= 100) {
    if (push == 0) {
      Serial.println("Hoisting");
      myStepper.step(10); //move a little for this loop
      delay(50);
    }
  }
}
