#include <Servo.h>

Servo backDoorServo;
const int redLED = 6;
const int greenLED = 5;
const int pushButton = 4;
const int solenoidPin = 2;
const int communicationPin1 = 8; // Connected to MCU1
const int communicationPin2 = 7; // Connected to MCU1

bool backDoorOpen = false; // Track if the back door is open
bool lockedMode = false;   // Track if the system is in locked mode

void setup() {
  backDoorServo.attach(9); // Attach the servo to pin 9 (PWM)
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(pushButton, INPUT_PULLUP); // Use internal pull-up resistor
  pinMode(solenoidPin, OUTPUT);
  pinMode(communicationPin1, INPUT);
  pinMode(communicationPin2, INPUT);

  // Initialize the back door in the closed position
  closeBackDoor();
}

void openBackDoor() {
  backDoorServo.write(135); // Rotate servo to open the back door
  digitalWrite(greenLED, HIGH); // Turn on green LED
  digitalWrite(redLED, LOW); // Turn off red LED
  backDoorOpen = true;
}

void closeBackDoor() {
  backDoorServo.write(45); // Rotate servo to close the back door
  delay(10000); // Wait for 10 seconds
  digitalWrite(greenLED, LOW); // Turn off green LED
  backDoorOpen = false;
}

void loop() {
  // Check if the system is in locked mode
  if (digitalRead(communicationPin1) == LOW && digitalRead(communicationPin2) == LOW) {
    lockedMode = false;
  } else {
    lockedMode = true;
  }

  // Check if the system is not in locked mode
  if (!lockedMode) {
    // Check if the push button is pressed
    if (digitalRead(pushButton) == LOW) {
      if (!backDoorOpen) {
        openBackDoor(); // Open the back door
      } else {
        closeBackDoor(); // Close the back door
      }
    }
  } else {
    // Implement locked mode behavior (back door stays closed)
    // You may add additional actions or logic for locked mode here
  }
  
  // Implement any other tasks and communication with MCU1 here
  
  // Delay or use non-blocking techniques to avoid blocking the loop
}

