#include <Servo.h>

Servo backDoorServo;
const int redLED = 6;
const int greenLED = 5;
const int pushButton = 4;
const int solenoidPin = 2;

bool backDoorOpen = false;
int prevButtonState = HIGH;  // Initially set to HIGH because the button uses a pull-up resistor

void setup() {
  backDoorServo.attach(9); // Attach the servo to pin 9 (PWM)
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(pushButton, INPUT); // Use internal pull-up resistor
  pinMode(solenoidPin, OUTPUT);
  
  closeBackDoor();
  updateLEDState();
}

void loop() {
  int currentButtonState = digitalRead(pushButton);
  
  // If button is pressed and was previously not pressed
  if (currentButtonState == LOW && prevButtonState == HIGH) {
    openBackDoor();
    delay(1000); // Allow some time for door to open fully
    closeBackDoor();
  }

  prevButtonState = currentButtonState;
}

void updateLEDState() {
  if (backDoorOpen) {
    digitalWrite(greenLED, HIGH);
    digitalWrite(redLED, LOW);
  } else {
    digitalWrite(greenLED, LOW);
    digitalWrite(redLED, HIGH);
  }
}

void openBackDoor() {
  backDoorServo.write(135);
  backDoorOpen = true;
}

void closeBackDoor() {
  backDoorServo.write(45);
  delay(1000); // Wait for the door to fully close
  digitalWrite(solenoidPin, HIGH); // Lock the door with the solenoid
  backDoorOpen = false;
}
