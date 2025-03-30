#include <LiquidCrystal.h>

// LCD pins
const int rs = 6, en = 7, d4 = 5, d5 = 4, d6 = 13, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Keypad pins
int KB_DataAvailable = A5;
int KB_A = A3;
int KB_B = A2;
int KB_C = A1;
int KB_D = A0;

// Keypad layout
char keys[] = {'1','2','3','F',
               '4','5','6','E',
               '7','8','9','D',
               'A','0','B','C'};

void setup() {
  pinMode(KB_DataAvailable, INPUT);
  pinMode(KB_A, INPUT);
  pinMode(KB_B, INPUT);
  pinMode(KB_C, INPUT);
  pinMode(KB_D, INPUT);

  lcd.begin(16, 2);
  lcd.print("hello, world!");
}

void loop() {
  if (digitalRead(KB_DataAvailable)) {
    char key = KB_Read();
    lcd.setCursor(0, 1);
    lcd.print("Key: ");
    lcd.print(key);
    delay(500);
    lcd.setCursor(5, 1);
    lcd.print("     ");
  }
}

char KB_Read() {
  int ka = digitalRead(KB_A);
  int kb = digitalRead(KB_B);
  int kc = digitalRead(KB_C);
  int kd = digitalRead(KB_D);
  int index = ka + kb * 2 + kc * 4 + kd * 8;
  return keys[index];
}
