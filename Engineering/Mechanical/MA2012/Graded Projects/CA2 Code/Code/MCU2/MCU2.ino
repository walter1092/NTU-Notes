// General
#include <Servo.h>
#include <SoftwareSerial.h>
#define baud 9600

// Servo
const byte servoBridgePin = 9;
const byte servoRiddleRoomPin = 7;

// Solenoid
const byte solenoidEarthquakePin = 4;
const byte solenoidDoorPin = 5;

// Toggle switch
const byte togglePin = 11;

// Bluetooth
const byte rx = 2, tx = 3;
SoftwareSerial bt(rx, tx);
const String toggleClosedSignal = "Toggle closed;";
const String bridgeClosedSignal = "Bridge closed;";
const String correctAnswerSignal = "Correct;";
const String wrongAnswerSignal = "Wrong;";
const String roomAlignedSignal = "Room aligned;";
const String passedRiddleRoomSignal = "Riddle room passed";
const String password = "";

// Game variables
bool hasPassedBridge = false;
bool hasPassedRiddleRoom = false;
unsigned long responseTimeWindow = 3000;

Servo servoBridge;
Servo servoRiddleRoom;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(baud);
  bt.begin(baud);
  servoBridge.attach(servoBridgePin);
  servoRiddleRoom.attach(servoRiddleRoomPin);

  pinMode(togglePin, INPUT_PULLUP);
  pinMode(solenoidEarthquakePin, OUTPUT);
  pinMode(solenoidDoorPin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(solenoidDoorPin, LOW);
  servoBridge.write(135);
  servoRiddleRoom.write(135);
}

void loop() 
{
  if (!hasPassedBridge) Bridge();
  else if (hasPassedBridge && !hasPassedRiddleRoom) RiddleRoom();
  else if (hasPassedRiddleRoom)
  {
    while (Serial.available() > 0) {
      char data = char(Serial.read());
      password += data;
      if (data == ';') 
      {
        bt.print(password);
        Serial.println(password);
        password = "";
      }
    }
  }
  delay(50);
}

void Bridge()
{
  int toggleState = digitalRead(togglePin);   // toggle on MCU2
  String msg = receiveBT();         // check whether toggle on MCU3 is closed

  if (toggleState == LOW && msg == toggleClosedSignal) 
  {
    // Execute
    digitalWrite(LED_BUILTIN, HIGH);
    int startPos = 135, endPos = 65, delayTime = 30;
    servoTurn(startPos, endPos, delayTime, servoBridge);
    delay(1000);

    // Inform
    digitalWrite(LED_BUILTIN, LOW);
    bt.print(bridgeClosedSignal);
    hasPassedBridge = true;
    Serial.println("Bridge is closed");
    servoBridge.detach();
  }
}

void RiddleRoom()
{
  int startPos = 45, endPos = 135, delayTime = 50;
  servoTurn(startPos, endPos, delayTime, servoRiddleRoom); 

  startPos = 135, endPos = 45, delayTime = 50;
  servoTurn(startPos, endPos, delayTime, servoRiddleRoom);   
  bt.print(roomAlignedSignal);      // inform MCU3 that the room is aligned
  digitalWrite(LED_BUILTIN, HIGH);

  String msg = receiveBT();
  unsigned long currentTime = millis();
  while (millis() - currentTime < responseTimeWindow) 
  {    
    if (msg == wrongAnswerSignal) earthquakeEnable(200, 3000);
    else if (msg == correctAnswerSignal) 
    {
      digitalWrite(solenoidDoorPin, LOW);
      hasPassedRiddleRoom = true;
    }
  }  
  digitalWrite(LED_BUILTIN, LOW);
  //   if (msg == wrongAnswerSignal) earthquakeEnable(200, 3000);
  //   else if (msg == correctAnswerSignal) 
  //   {
  //     digitalWrite(solenoidDoorPin, HIGH);
  //     hasPassedRiddleRoom = true;
  //     bt.print(passedRiddleRoomSignal);
  //     delay(4000);
  //     digitalWrite(solenoidDoorPin, HIGH);
  //   }
  // }
}

void servoTurn(int startPos, int endPos, unsigned long delayTime, Servo servo) 
{
  if (startPos < endPos) 
  {
    for (int pos = startPos; pos <= endPos; pos++) 
    {
      servo.write(pos);
      delay(delayTime);
    }
  }
  else
  {
    for (int pos = startPos; pos >= endPos; pos--) 
    {
      servo.write(pos);
      delay(delayTime);
    }
  }
}

void earthquakeEnable(int delayTime, unsigned long duration) 
{
  int count = duration / (delayTime * 2);
  for (int i = 0; i <= count; i++) 
  {
    digitalWrite(solenoidEarthquakePin, HIGH);
    delay(delayTime);
    digitalWrite(solenoidEarthquakePin, LOW);
    delay(delayTime);    
  } 
}

String receiveBT() 
{
  String msg = "";
  while (bt.available() > 0) 
  {
    char data = char(bt.read());
    msg += data;
    if (data == ';') 
    {
      Serial.println(msg);
      return msg;
    }
  }
}

