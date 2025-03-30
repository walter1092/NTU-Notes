#include <Servo.h>

Servo backDoorServo;

void setup() {
  backDoorServo.attach(9); // Attach the servo to pin 9 (PWM)
}

void loop() {
  backDoorServo.write(45);
  delay(2000);
  backDoorServo.write(135);
  delay(2000);
}
