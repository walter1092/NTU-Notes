#include <Servo.h>

Servo backDoorServo;
const int redLED = 6;
const int greenLED = 5;
const int pushButton = 4;
const int solenoidPin = 2;
const int communicationPin1 = 8; 
const int communicationPin2 = 7; 

bool backDoorOpen = false; 
bool lockedMode = false;
unsigned long previousMillis = 0; 
const long interval = 10000; 
const long debounceDelay = 50; 
unsigned long lastDebounceTime = 0; 
int lastButtonState = HIGH; 

void setup() {
  backDoorServo.attach(9); 
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(pushButton, INPUT_PULLUP); 
  pinMode(solenoidPin, OUTPUT);
  pinMode(communicationPin1, INPUT);
  pinMode(communicationPin2, INPUT);
  closeBackDoor();
}

void openBackDoor() {
  digitalWrite(solenoidPin, HIGH); 
  backDoorServo.write(135);
  digitalWrite(greenLED, HIGH); 
  digitalWrite(redLED, LOW); 
  backDoorOpen = true;
}

void closeBackDoor() {
  backDoorServo.write(45);
  digitalWrite(solenoidPin, LOW); 
  digitalWrite(greenLED, LOW);
  backDoorOpen = false;
}

void loop() {
  int reading = digitalRead(pushButton);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading == LOW) {
      handleButtonPress();
    }
  }
  
  lastButtonState = reading;

  handleLockedMode();
}

void handleButtonPress() {
  if (!lockedMode) {
    if (!backDoorOpen) {
      openBackDoor();
      previousMillis = millis();
    } else if (millis() - previousMillis >= interval) {
      closeBackDoor();
    }
  }
}

void handleLockedMode() {
  if (digitalRead(communicationPin1) == LOW && digitalRead(communicationPin2) == LOW) {
    lockedMode = false;
    digitalWrite(redLED, LOW);
  } else {
    lockedMode = true;
    digitalWrite(redLED, (millis() / 500) % 2); 
  }
}
