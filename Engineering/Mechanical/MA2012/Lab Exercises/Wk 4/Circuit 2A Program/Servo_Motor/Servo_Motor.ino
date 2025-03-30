#include <Servo.h>

Servo myServo;  // Create servo object to control a servo

void setup() {
  myServo.attach(3);  // Attaches the servo on pin 4 to the servo object
  myServo.write(90);  // Sets the servo to the neutral position of 90 degrees
}

void loop() {
  // The loop function is empty if you just want to set the servo to 90 degrees and do nothing else
}
