#include <LiquidCrystal.h>

// LCD and Keypad Pins
const int rs = 6, en = 7, d4 = 5, d5 = 4, d6 = 13, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int KB_DataAvailable = A5, KB_A = A3, KB_B = A2, KB_C = A1, KB_D = A0;
char keys[] = {'1','2','3','F','4','5','6','E','7','8','9','D','A','0','B','C'};

// State management
bool lockedMode = false;
String pinInput = "";
int dPressCount = 0;
int ePressCount = 0;

void setup() {
  pinMode(KB_DataAvailable, INPUT);
  pinMode(KB_A, INPUT);
  pinMode(KB_B, INPUT);
  pinMode(KB_C, INPUT);
  pinMode(KB_D, INPUT);
  lcd.begin(16, 2);
  showNormalMode();
}

void loop() {
  if (digitalRead(KB_DataAvailable)) {
    char key = KB_Read();
    handleKeyPress(key);
    delay(200); // Simple debounce
  }
}

void showNormalMode() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("NORMAL");
  lcd.setCursor(0, 1);
  lcd.print(" ");
}

void showLockedMode() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("LOCKED");
  lcd.setCursor(0, 1);
  lcd.print("PIN:");
}

void handleKeyPress(char key) {
  if (!lockedMode) {
    if (key == 'D') {
      dPressCount++;
      if (dPressCount == 2) {
        lockedMode = true;
        dPressCount = 0;
        showLockedMode();
      }
    } else {
      dPressCount = 0;
    }
  } else {
    if (key == 'E') {
      ePressCount++;
      if (ePressCount == 2) {
        lcd.setCursor(0, 1);
        lcd.print("PIN:   ");  // Clear previous PIN
        pinInput = "";  // Reset PIN input
      }
    } else if (key >= '0' && key <= '9' && pinInput.length() < 3) {
      pinInput += key;
      lcd.setCursor(4 + pinInput.length(), 1);
      lcd.print(key);
      if (pinInput.length() == 3) {
        checkPin();
      }
    } else {
      ePressCount = 0;
    }
  }
}

void checkPin() {
  if (pinInput == "123") {
    lockedMode = false;
    ePressCount = 0;
    showNormalMode();
  } else {
    lcd.setCursor(4, 1);
    lcd.print("   ");  // Clear the entered PIN
    pinInput = "";
  }
}

char KB_Read() {
  int ka = digitalRead(KB_A);
  int kb = digitalRead(KB_B);
  int kc = digitalRead(KB_C);
  int kd = digitalRead(KB_D);
  int k = ka + kb * 2 + kc * 4 + kd * 8;
  return keys[k];
}
