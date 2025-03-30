#define baud 9600
#include <Servo.h>
#include <SoftwareSerial.h>
const int rx=7, tx=8;
SoftwareSerial mySerial(rx, tx);

Servo backDoorServo;
const int redLED = 6;
const int greenLED = 5;
const int pushButton = 4;
const int solenoidPin = 2;

bool backDoorOpen = false;
bool lockedMode = false;

unsigned long prev_time;
unsigned long current_time;

void setup() {
  backDoorServo.attach(9); // Attach the servo to pin 9 (PWM)
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(pushButton, INPUT); 
  pinMode(solenoidPin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  
  closeBackDoor();
  activateNormalMode();

  mySerial.begin(baud);
  Serial.begin(baud);  

  prev_time = millis();
  current_time = millis();
}
void loop() {
  current_time = millis();
  if (mySerial.available() && current_time - prev_time > 100) {
    int data = mySerial.read();
    if (data==2) activateLockedMode();
    else if (data==1) activateNormalMode();
    prev_time = current_time;
  }
}

void activateNormalMode() {
  digitalWrite(greenLED, HIGH);
  digitalWrite(redLED, LOW);

  if (digitalRead(pushButton)==LOW) {
    digitalWrite(solenoidPin, HIGH);
    delay(1000);
    openBackDoor();
    delay(5000);
    closeBackDoor();
    delay(1000);
    digitalWrite(solenoidPin, LOW);
  }
}

void activateLockedMode() {
  digitalWrite(greenLED, LOW);
  digitalWrite(redLED, HIGH);
  closeBackDoor();
}

void openBackDoor() {
  backDoorServo.write(135);
  backDoorOpen = true;
}

void closeBackDoor() {
  backDoorServo.write(45);
  backDoorOpen = false;
}




