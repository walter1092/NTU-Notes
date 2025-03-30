#include <Servo.h>

Servo myServo;  // create servo object to control a servo

int val;    // variable for servo position

int pwm = 3; // assigns pin 3 to variable pwm (motor pin)
int space;   // declares variable space
int mark= 800;   // declares variable mark

int button = 5;  // assigns pin 5 to pushbutton
int push = 0; // variable for button state

int pot = A0; // assigns pin A0 to potentiometer
int hoist = 0;  // variable for hoist input position

void setup()  // setup loop
{
   myServo.attach(4);  // attaches the servo on pin 4 to the servo object

   pinMode(pwm, OUTPUT);  // declares pin 3 as output
   pinMode(button,INPUT); // declares pin 5 as input
   pinMode(pot,INPUT);    // declares pin A0 as input
   
   Serial.begin(9600);
}

void loop()
{
  hoist = analogRead(pot);
  push = digitalRead(button);
  val = 45 + (long)hoist*(135-45)/1023; // maps 0V to 5V to 45 to 135 degrees
  myServo.write(val);
  delay(15);
  
  if (val >= 80 & val <= 100) {
  if (push == 0) {
          Serial.println("Hoisting");
    space = 1000-mark; // subtracts mark from 1000 ans saves the result in space
          for (int i = 0; i < 500; i++){
    {digitalWrite(pwm, HIGH); // sets pin 3 HIGH
    delayMicroseconds(mark);   // waits for t1 uS (high time)
    digitalWrite(pwm, LOW);  // sets pin 3 LOW
    delayMicroseconds(space);   // waits for t2 uS (low time)
          }
    }
  }
  }
}
