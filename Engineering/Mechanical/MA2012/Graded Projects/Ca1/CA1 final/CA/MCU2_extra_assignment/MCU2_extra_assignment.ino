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
const int trigPin = 12;
const int echoPin = 11;
const int orangeLED = 10;
const int buzzerPin = 3;
const int buzzerFreq = 100;

bool backDoorOpen = false;
bool lockedMode = false;
bool allowOpen = true;

unsigned long prev_time;
unsigned long current_time;

void setup() {
  backDoorServo.attach(9); // Attach the servo to pin 9 (PWM)
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(orangeLED, OUTPUT);
  pinMode(pushButton, INPUT); 
  pinMode(solenoidPin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  pinMode(buzzerPin, OUTPUT); 
  
  closeBackDoor();
  activateNormalMode();

  mySerial.begin(baud);
  Serial.begin(baud);  

  prev_time = millis();
  current_time = millis();

  digitalWrite(orangeLED, HIGH);
}
void loop() {
  current_time = millis();
  if (mySerial.available() && current_time - prev_time > 100) {
    int data = mySerial.read();
    if (data==2) activateLockedMode();
    else if (data==1) activateNormalMode();
    prev_time = current_time;
  }
  float distance = getDistance();
  Serial.println(distance);
  delay(10);

  if (distance > 1.2) digitalWrite(orangeLED, HIGH);
  else {
    digitalWrite(orangeLED, LOW);
    if (distance < 0.6) {
      allowOpen = false;
      tone(buzzerPin, buzzerFreq);
      delay(3000);
      noTone(buzzerPin);
    }
    else allowOpen =true;
  }


}

float getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  float m = (duration/2) * 0.00343;     // Divide by 29.1 or multiply by 0.0343
  return m;
}

void activateNormalMode() {
  digitalWrite(greenLED, HIGH);
  digitalWrite(redLED, LOW);

  if (digitalRead(pushButton)==LOW && allowOpen == true) {
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
