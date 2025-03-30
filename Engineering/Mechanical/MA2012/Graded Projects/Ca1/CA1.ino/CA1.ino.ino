#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

// LCD Setup
LiquidCrystal lcd(6, 7, 5, 4, 13, 12);  // RS, E, DB4, DB5, DB6, DB7

// Keypad Encoder Pins
const int KEYPAD_OUT_A = A3;
const int KEYPAD_OUT_B = A2;
const int KEYPAD_OUT_C = A1;
const int KEYPAD_OUT_D = A0;
const int KEYPAD_DATA_AVAIL = A5;

// Digital Distance Sensor
const int DISTANCE_SENSOR_SIG = A4;

// Motor Driver Pins
const int MOTOR_A2_IN = 11;
const int MOTOR_A1_IN = 10;

// DC Motor with Encoder Pins
const int MOTOR_A = 2;
const int MOTOR_B = 3;

// Software Serial for MCU1 to MCU2 communication
SoftwareSerial mySerial(9, 8);  // RX, TX

// System modes
enum Mode {NORMAL, LOCKED};
Mode systemMode = NORMAL;

void setup() {
  // LCD initialization
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("NORMAL");

  // Keypad Encoder Pin Setup
  pinMode(KEYPAD_OUT_A, INPUT);
  pinMode(KEYPAD_OUT_B, INPUT);
  pinMode(KEYPAD_OUT_C, INPUT);
  pinMode(KEYPAD_OUT_D, INPUT);
  pinMode(KEYPAD_DATA_AVAIL, INPUT);

  // Distance Sensor Setup
  pinMode(DISTANCE_SENSOR_SIG, INPUT);

  // Motor Pins Setup
  pinMode(MOTOR_A2_IN, OUTPUT);
  pinMode(MOTOR_A1_IN, OUTPUT);
  pinMode(MOTOR_A, INPUT);
  pinMode(MOTOR_B, INPUT);

  // Serial setup
  mySerial.begin(9600);
}

void loop() {
  if (systemMode == NORMAL) {
    // Check distance sensor
    if (digitalRead(DISTANCE_SENSOR_SIG) == HIGH) {
      openFrontDoor();
      delay(10000);  // Wait for 10 seconds
      closeFrontDoor();
    }
  }
  
  // Check keypad
  char keyPressed = readKeypad();
  if (keyPressed == 'D') {
    // Handle locked mode initiation
    systemMode = LOCKED;
    lcd.setCursor(0, 0);
    lcd.print("LOCKED  ");
    mySerial.write('L');  // Inform MCU2 about the lock
  } else if (keyPressed == 'E') {
    // Handle PIN entry for unlocking
    lcd.setCursor(0, 1);
    lcd.print("PIN: ");
    char pinEntered[4];
    for (int i = 0; i < 3; i++) {
      char digit = readKeypad();
      lcd.print(digit);
      pinEntered[i] = digit;
    }
    pinEntered[3] = '\0';  // End string

    if (strcmp(pinEntered, "123") == 0) {
      systemMode = NORMAL;
      lcd.setCursor(0, 0);
      lcd.print("NORMAL");
    } else {
      lcd.setCursor(0, 1);
      lcd.print("Wrong PIN   ");
      delay(2000);
      lcd.setCursor(0, 1);
      lcd.print("           ");
    }
  }
}

char readKeypad() {
  // Keypad reading function
  // ... (similar to what we've done before)
}

void openFrontDoor() {
  // Open door function
  // ... (control the motor as per requirement)
}

void closeFrontDoor() {
  // Close door function
  // ... (control the motor as per requirement)
}
