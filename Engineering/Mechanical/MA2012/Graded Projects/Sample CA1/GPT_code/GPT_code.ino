#include <LiquidCrystal.h>

// Define Pins and Constants
const int SWITCH_PIN = A4;
const int ONBOARD_LED = 13;
const int DATA_PIN = A3;
const int OUT_A = 12;
const int OUT_B = A5;
const int OUT_C = A3;
const int OUT_D = 10;
const int SERIAL_SPEED = 9600;

#define DATA_PIN A5      // Data Available pin for the 74C922 Keypad Encoder (connected to A5 on Arduino)
#define OUT_A 10         // Out A pin for the 74C922 Keypad Encoder (connected to ~10 on Arduino)
#define OUT_B 11         // Out B pin for the 74C922 Keypad Encoder (connected to ~11 on Arduino)
#define OUT_C 12         // Out C pin for the 74C922 Keypad Encoder (connected to 12 on Arduino)
#define OUT_D A3         // Out D pin for the 74C922 Keypad Encoder (connected to A3 on Arduino)

// Initialize LCD
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

char selectedKey = '\0';

void setup() {
  pinMode(SWITCH_PIN, INPUT_PULLUP);
  pinMode(ONBOARD_LED, OUTPUT);
  pinMode(DATA_PIN, INPUT);
  pinMode(OUT_A, INPUT_PULLUP);
  pinMode(OUT_B, INPUT_PULLUP);
  pinMode(OUT_C, INPUT_PULLUP);
  pinMode(OUT_D, INPUT_PULLUP);
  
  Serial.begin(SERIAL_SPEED);

  lcd.begin(16, 2);
  delay(500);
  standbyMode();
}

void loop() {
  // Check Toggle Switch
  if (digitalRead(SWITCH_PIN)) {
    digitalWrite(ONBOARD_LED, HIGH); // Turn ON the onboard LED
    if (Serial.available()) {
      char received = Serial.read();
      if (received == '0') {
        collectItemAnimation();
        standbyMode();
      }
    }
    
    char key = readKeypad();
    if (key == '1' || key == '2') {
      selectedKey = key;
      lcd.setCursor(0, 1);
      lcd.print(key);
    } else if (key == 'C' && (selectedKey == '1' || selectedKey == '2')) {
      Serial.write(selectedKey);
      lcd.setCursor(0, 1);
      lcd.print(" ");
    }
  } else {
    digitalWrite(ONBOARD_LED, LOW); // Turn OFF the onboard LED
    lcd.clear();
  }
}

void standbyMode() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Select 1 / 2");
  selectedKey = '\0';
}

void collectItemAnimation() {
  for (int i = 0; i < 5; i++) {
    lcd.setCursor(0, 1);
    lcd.print("Collect Item");
    delay(1000);
    lcd.setCursor(0, 1);
    lcd.print(" ");
    delay(500);
  }
}

char readKeypad() {
  if (digitalRead(DATA_PIN)) {
    Serial.println("DATA_PIN is HIGH");
    uint8_t keyData = 0;
    keyData |= digitalRead(OUT_A) << 0;
    keyData |= digitalRead(OUT_B) << 1;
    keyData |= digitalRead(OUT_C) << 2;
    keyData |= digitalRead(OUT_D) << 3;
    
    Serial.print("KeyData: ");
    Serial.println(keyData, BIN);
    
    switch (keyData) {
      case 0x0: return '1';
      case 0x1: return '2';
      // ... (Add other cases if necessary)
      default: return '\0';
    }
  }
  return '\0';
}
