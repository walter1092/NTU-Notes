#include <Servo.h>

Servo backDoorServo;
const int redLED = 6;
const int greenLED = 5;
const int pushButton = 4;
const int solenoidPin = 2;

bool backDoorOpen = false;
bool lockedMode = false;
int lastButtonState = HIGH;
unsigned long solenoidActivatedTime = 0;
const unsigned long solenoidActiveDuration = 10000;  // 10 seconds
bool solenoidActive = false;
int prevButtonState = HIGH;  // Initially set to HIGH because the button uses a pull-up resistor


void setup() {
  backDoorServo.attach(9); // Attach the servo to pin 9 (PWM)
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(pushButton, INPUT); // Use internal pull-up resistor
  pinMode(solenoidPin, OUTPUT);
  
  closeBackDoor();
  updateLEDState();
    // Initialize LED states
  digitalWrite(greenLED, LOW); // Ensure green LED starts off
  digitalWrite(redLED, HIGH);  // Ensure red LED starts on (as locked)

}
void loop() {
  int currentButtonState = digitalRead(pushButton);
  
  // If button is pressed and was previously not pressed
  if (currentButtonState == LOW && prevButtonState == HIGH) { 
    solenoidActive = true;
    solenoidActivatedTime = millis(); // Record when the solenoid was activated
    digitalWrite(solenoidPin, HIGH); // Activate the solenoid
    digitalWrite(redLED, LOW); // Turn off red LED
    digitalWrite(greenLED, HIGH); // Turn on green LED
    delay(50);
  }
  
  // If solenoid is active and it's been more than 10 seconds since activation
  if (solenoidActive && (millis() - solenoidActivatedTime > solenoidActiveDuration)) {
    solenoidActive = false;
    digitalWrite(solenoidPin, LOW); // Deactivate the solenoid
    digitalWrite(greenLED, LOW); // Turn off green LED
    digitalWrite(redLED, HIGH); // Turn on red LED
  }

  prevButtonState = currentButtonState;
}


void handleButtonPress() {
  toggleSolenoid();
  toggleDoorState();
  updateLEDState();
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

void toggleSolenoid() {
  if (backDoorOpen) {
    digitalWrite(solenoidPin, LOW);
  } else {
    digitalWrite(solenoidPin, HIGH);
  }
}

void toggleDoorState() {
  if (backDoorOpen) {
    closeBackDoor();
  } else {
    openBackDoor();
  }
}

void openBackDoor() {
  backDoorServo.write(135);
  backDoorOpen = true;
}

void closeBackDoor() {
  backDoorServo.write(45);
  delay(10000); // Wait for 10 seconds
  backDoorOpen = false;
}
