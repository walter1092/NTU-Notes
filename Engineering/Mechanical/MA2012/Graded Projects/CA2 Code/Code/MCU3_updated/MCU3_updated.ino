#include <LiquidCrystal.h>
#include <Servo.h>
#include <SoftwareSerial.h>
#define baud 9600

// Bluetooth
// rx 19, tx 18

// Bluetooth 
const byte togglePin = 23;
const String toggleClosedSignal = "Toggle closed;";
const String bridgeClosedSignal = "Bridge closed;";
const String correctAnswerSignal = "Correct;";
const String wrongAnswerSignal = "Wrong;";
const String roomAlignedSignal = "Room aligned;";
const String passedRiddleRoomSignal = "Riddle room passed";
const String correctPassword = "we are here;";
const String password = "";

// Riddle room
const byte wrongButtonPin = 27, correctButtonPin = 25;

// Maze
const byte servoMaze1Pin = 5, servoMaze2Pin = 3;
Servo servoMaze1;
Servo servoMaze2;
const byte pot1Pin = A4, pot2Pin = A5;
const byte solenoidPin = 37;
const byte limitSwitchPin = 35;

// Library
const int rs = 6, en = 7, d4 = 5, d5 = 4, d6 = 13, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int KB_DataAvailable = A5, KB_A = A3, KB_B = A2, KB_C = A1, KB_D = A0;
char keys[] = {'1','2','3','F','4','5','6','E','7','8','9','D','A','0','B','C'};
const byte ledPin = 39;

// Game variables
bool hasPassedBridge = false;
bool hasPassedRiddleRoom = false;
bool hasPassedMaze = false;
bool hasPassedLibrary = false;

// Variables to control message sending frequency
bool toggleClosedSignal_ = false;
unsigned long answerSignal_ = 0;

void setup() 
{
  // General
  Serial.begin(baud);
  Serial1.begin(baud);

  // Bridge
  pinMode(togglePin, INPUT_PULLUP);

  // Riddle room
  pinMode(wrongButtonPin, INPUT_PULLUP);
  pinMode(correctButtonPin, INPUT_PULLUP);

  // Maze
  servoMaze1.attach(servoMaze1Pin);
  servoMaze2.attach(servoMaze2Pin);
  pinMode(pot1Pin, INPUT);
  pinMode(pot2Pin, INPUT);
  pinMode(solenoidPin, OUTPUT);
  pinMode(limitSwitchPin, INPUT_PULLUP);

  // Keypad and LCD
  pinMode(KB_DataAvailable, INPUT);
  pinMode(KB_A, INPUT);
  pinMode(KB_B, INPUT);
  pinMode(KB_C, INPUT);
  pinMode(KB_D, INPUT);
  lcd.begin(16, 2); 
  pinMode(ledPin, OUTPUT);

  digitalWrite(solenoidPin, HIGH);
  lcd.cursor();
}

void loop() 
{
  // Control MCU2 bridge
  if (!hasPassedBridge) Bridge();
  // Control MCU2 correct and wrong answer
  else if (hasPassedBridge && !hasPassedRiddleRoom) RiddleRoom();
  else if (hasPassedRiddleRoom && !hasPassedMaze) Maze();
  else if (hasPassedMaze && !hasPassedLibrary) Library();
  delay(50);
}

void Bridge() 
{
  int toggleState = digitalRead(togglePin);
  if (toggleState == LOW && toggleClosedSignal_ == false) 
  {
    Serial1.print(toggleClosedSignal);
    toggleClosedSignal_ = true;     // send only once
  }

  String msg = receiveSerial1();
  if (msg == bridgeClosedSignal) 
  {
    hasPassedBridge = true;
  }
}

void RiddleRoom()
{
  String msg = receiveSerial1();
  if (msg == roomAlignedSignal)
  {
    int correctButtonPressed = digitalRead(correctButtonPin);
    int wrongButtonPressed = digitalRead(wrongButtonPin);

    if (wrongButtonPressed == LOW && millis() - answerSignal_ > 1000) 
    {
      Serial1.print(wrongAnswerSignal); 
      Serial.println("Wrong");
      answerSignal_ = millis();
    }
    else if (correctButtonPressed == LOW && millis() - answerSignal_ > 1000) 
    {
      Serial1.print(correctAnswerSignal); 
      Serial.println("Correct");
      answerSignal_ = millis();
    }
  }
  else if (msg == passedRiddleRoomSignal) hasPassedRiddleRoom = true;
}

void Maze() 
{
  int pot1Value = analogRead(pot1Pin);
  int pot2Value = analogRead(pot2Pin);

  int servoMaze1Pos = map(pot1Value, 0, 1023, 0, 180);
  int servoMaze2Pos = map(pot2Value, 0, 1023, 0, 180);

  servoMaze1.write(servoMaze1Pos);
  servoMaze2.write(servoMaze2Pos);

  if (digitalRead(limitSwitchPin) == LOW) 
  {
    digitalWrite(solenoidPin, LOW);
    hasPassedMaze = true;
    servoMaze1.detach();
    servoMaze2.detach();
  }
}

void Library()
{
    // Receive the password from MCU2, display the received password, and display whether the password is correct
  String msg = receiveSerial1();
  lcd.setCursor(0, 0);
  lcd.print(msg);     // Print out the received password
  if (msg == correctPassword) 
  {
    // if it is correct, the cursor will move down 1 line
    // the librarian has to re-key the right password and press 0 to enter
    // the display will say whether the keyed password is correct
    // and ask the librarian to key in again if incorrect
    Serial.println("Correct password");
    lcd.setCursor(0, 1);
    lcd.autoscroll();
    while (true)
    {
      if (digitalRead(KB_DataAvailable)) 
      {
        char key = KB_Read();
        if (key != '0') 
        {
          password += key;
          lcd.print(key);
        }
        else
        {
          if (password == correctPassword) 
          {
            lcd.noDisplay();
            digitalWrite(ledPin, HIGH);
            delay(2000);
            digitalWrite(ledPin, LOW);
            hasPassedLibrary = true;
          }
          else
          {
            lcd.print("                "); 
            delay(100);
            lcd.print("Wrong password"); 
            delay(2000);
          }
        }
        delay(200); // Simple debounce
      } 
    }
  }
  else
  {
    // If the received password is incorrect, the lcd will display accordingly
    lcd.setCursor(0, 1);
    lcd.print("Wrong password!");
    delay(2000);
    lcd.clear();
  } 
}

String receiveSerial1() 
{
  String msg = "";
  while (Serial1.available() > 0) 
  {
    char data = char(Serial1.read());
    msg += data;
    if (data == ';') 
    {
      Serial.println(msg);
      return msg;
    }
  }
}

char KB_Read() 
{
  int ka = digitalRead(KB_A);
  int kb = digitalRead(KB_B);
  int kc = digitalRead(KB_C);
  int kd = digitalRead(KB_D);
  int k = ka + kb * 2 + kc * 4 + kd * 8;
  return keys[k];
}