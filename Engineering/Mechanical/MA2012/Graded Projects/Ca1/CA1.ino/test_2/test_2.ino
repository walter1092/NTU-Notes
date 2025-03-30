#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

// Keypad and encoder pins
const int KB_DataAvailable = A5;
const int KB_A = A3;
const int KB_B = A2;
const int KB_C = A1;
const int KB_D = A0;
const int encoderPinA = 2;
const int encoderPinB = 3;

// Distance sensor pin
const int DIST_SENSOR = A4;

// Motor pins
const int MOTOR_A = 10;
const int MOTOR_B = 11;

// LCD setup
const int rs = 6, en = 7, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Keypad layout
char keys[] = {'1', '2', '3', 'F',
               '4', '5', '6', 'E',
               '7', '8', '9', 'D',
               'A', '0', 'B', 'C'};

// Software Serial setup for communication between MCU1 and MCU2
SoftwareSerial mySerial(8, 9); // RX, TX

volatile long int encoder_pos = 0; // Encoder position
char pinBuffer[4] = ""; // Store the PIN entered by the user
int bufferIndex = 0;

enum Mode { NORMAL, LOCKED, PIN_ENTRY };
Mode currentMode = NORMAL;

void setup() {
  // Initialize serial for debug and communication
  Serial.begin(9600);
  mySerial.begin(9600);

  // Keypad setup
  pinMode(KB_DataAvailable, INPUT);
  pinMode(KB_A, INPUT);
  pinMode(KB_B, INPUT);
  pinMode(KB_C, INPUT);
  pinMode(KB_D, INPUT);

  // Encoder setup
  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);
  attachInterrupt(digitalPinToInterrupt(encoderPinA), encoder, RISING);

  // LCD initialization
  lcd.begin(16, 2);
  lcd.print("NORMAL");
}

void loop() {
  // Check if there's a hand wave
  if (currentMode == NORMAL && analogRead(DIST_SENSOR) > 10 && analogRead(DIST_SENSOR) < 20) {
    openDoor();
    delay(10000); // Wait for 10 seconds
    closeDoor();
  }

  // Check for keypad input
  if (digitalRead(KB_DataAvailable)) {
    char key = readKeypad();
    handleKeyPress(key);
  }

  // TODO: Handle communication with MCU2 if needed
}

char readKeypad() {
  int ka = digitalRead(KB_A);
  int kb = digitalRead(KB_B);
  int kc = digitalRead(KB_C);
  int kd = digitalRead(KB_D);
  int index = ka + kb * 2 + kc * 4 + kd * 8;
  return keys[index];
}

void handleKeyPress(char key) {
  switch (currentMode) {
    case NORMAL:
      if (key == 'D') {
        currentMode = LOCKED;
        lcd.clear();
        lcd.print("LOCKED");
      }
      break;
    
    case LOCKED:
      if (key == 'E') {
        currentMode = PIN_ENTRY;
        lcd.setCursor(0, 1);
        lcd.print("PIN: ");
      }
      break;
    
    case PIN_ENTRY:
      if (bufferIndex < 3) {
        pinBuffer[bufferIndex] = key;
        lcd.print(key);
        bufferIndex++;
        if (bufferIndex == 3) {
          if (strcmp(pinBuffer, "123") == 0) {
            currentMode = NORMAL;
            lcd.clear();
            lcd.print("NORMAL");
          } else {
            lcd.setCursor(4, 1);
            lcd.print("   "); // Clear the PIN entry
            lcd.setCursor(4, 1);
            bufferIndex = 0; // Reset buffer index
          }
        }
      }
      break;
  }
}

void encoder() {
  if (digitalRead(encoderPinB) == HIGH) {
    encoder_pos++;
  } else {
    encoder_pos--;
  }
}

void openDoor() {
  // TODO: Implement motor control to open the door
}

void closeDoor() {
  // TODO: Implement motor control to close the door
}
