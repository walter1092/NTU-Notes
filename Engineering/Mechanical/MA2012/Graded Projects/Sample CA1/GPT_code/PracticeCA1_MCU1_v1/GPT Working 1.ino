#include <LiquidCrystal.h>

// LCD pins
const int rs = 6, en = 7, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Keypad pins
#define KB_DataAvailable A5
#define KB_A 10
#define KB_B 11
#define KB_C 12
#define KB_D 13

// Toggle switch pin
#define SWITCH_PIN A4    

// Declare keypad layout
char keys[] = {'1','2','3','F',
               '4','5','6','E',
               '7','8','9','D',
               'A','0','B','C'};

bool keypadActivated = false;
char lastSelection = '\0'; 

void setup(void) {
  pinMode(KB_DataAvailable, INPUT);
  pinMode(KB_A, INPUT);
  pinMode(KB_B, INPUT);
  pinMode(KB_C, INPUT);
  pinMode(KB_D, INPUT);
  pinMode(SWITCH_PIN, INPUT_PULLUP);
  
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Select 1 / 2");
  lcd.setCursor(0, 1);
  lcd.print(" ");

  Serial.begin(9600);
}

void loop(void) {
  // Check toggle switch
  if (digitalRead(SWITCH_PIN)) {
    keypadActivated = true;
  } else {
    keypadActivated = false;
    lcd.clear();
    return;
  }

  if (keypadActivated && digitalRead(KB_DataAvailable)) {
    char key = KB_Read();
    if (key == '1' || key == '2') {
      lcd.setCursor(0, 1);
      lcd.print(key);
      lastSelection = key;
    } else if (key == 'C' && (lastSelection == '1' || lastSelection == '2')) {
      Serial.println(lastSelection);
      lcd.setCursor(0, 1);
      lcd.print(" "); 
    }

    if (Serial.available() > 0) {
      char response = Serial.read();
      if (response == '0') {
        for (int i = 0; i < 5; i++) {
          lcd.setCursor(0, 1);
          lcd.print("Collect Item");
          delay(1000);
          lcd.setCursor(0, 1);
          lcd.print(" ");
          delay(500);
        }
        lcd.setCursor(0, 0);
        lcd.print("Select 1 / 2");
        lcd.setCursor(0, 1);
        lcd.print(" ");
      }
    }
  }
}

char KB_Read() {
  int ka, kb, kc, kd;
  ka = digitalRead(KB_A);
  kb = digitalRead(KB_B);
  kc = digitalRead(KB_C);
  kd = digitalRead(KB_D);

  int k = ka + kb * 2 + kc * 4 + kd * 8; 
  return keys[k];
}
