#define baud 9600

#include <SoftwareSerial.h>
const int rx=9, tx=8;
SoftwareSerial mySerial(rx, tx);

int pin1 = 10;   // motor pin1
int pin2 = 11;  // motor pin2
int encoderPinA = 2;
int encoderPinB = 3;
int distanceSensorPin = A4;
volatile long int encoder_pos = 0; 
const int one_revolution_80 = 220;
const int one_revolution_30 = 250;
const int error = 10;

unsigned long prev_time = 0;
unsigned long current_time;

#include <LiquidCrystal.h>

// LCD and Keypad Pins
const int rs = 6, en = 7, d4 = 5, d5 = 4, d6 = 13, d7 = 12;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int KB_DataAvailable = A5, KB_A = A3, KB_B = A2, KB_C = A1, KB_D = A0;
int kb_timeout = 300;
char keys[] = {'1','2','3','F','4','5','6','E','7','8','9','D','A','0','B','C'};

// State management
bool lockedMode = false; 
bool prevLockedMode;
bool acceptPinInput = false;
String passwordInput = "";
int dPressCount = 0;
int ePressCount = 0;

void setup() {
  // put your setup code here, to run once:
  mySerial.begin(baud);
  Serial.begin(baud);
  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(encoderPinA), encoder, RISING); // Enable the external interrupt
  pinMode(distanceSensorPin, INPUT);

  pinMode(KB_DataAvailable, INPUT);
  pinMode(KB_A, INPUT);
  pinMode(KB_B, INPUT);
  pinMode(KB_C, INPUT);
  pinMode(KB_D, INPUT);
  lcd.begin(16, 2);
  showNormalMode();
  ePressCount = 0;
  dPressCount = 0;
  lockedMode = false;
  prevLockedMode = lockedMode;
  passwordInput = "";
}

void loop() {
  current_time = millis();
  if (digitalRead(KB_DataAvailable) && (current_time - prev_time > kb_timeout)) {
    char key = KB_Read();
    handleKeyPress(key);
    prev_time = current_time;
  }

  if (lockedMode == true) {
    // moveDC(1, 0, 0);
    mySerial.write(2);
  }
  else {
    mySerial.write(1);
    // if (digitalRead(distanceSensorPin) == 0) {    // if close enough to the sensor
    //   open();
    //   delay(5000);
    //   close();
    // }
  }
}


void encoder(){
  if(digitalRead(encoderPinB) == HIGH){
    encoder_pos++;
  }else{
    encoder_pos--;
  }
} 

int dutyCycle_to_pwm(float dutyCycle) {return 255*dutyCycle;}

void moveDC(int dir, float dutyCycle, int revolutions) {
  int setPos;
  int pwm = dutyCycle_to_pwm(dutyCycle);
  if (dutyCycle == 0.8) setPos = dir * one_revolution_80 * revolutions + encoder_pos;
  else setPos = dir * one_revolution_30 * revolutions + encoder_pos;

  while (abs(setPos - encoder_pos)> error) {
    if (setPos > encoder_pos) {
      analogWrite(pin1, pwm);
      digitalWrite(pin2, LOW);
    }
    else {
      analogWrite(pin2, pwm);
      digitalWrite(pin1, LOW);      
    }
  } 
  // stop the motor after done
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
  // }
}

void open() {
  moveDC(1, 0.8, 2);
}

void close() {
  moveDC(-1, 0.8, 1);
  delay(500);
  moveDC(-1, 0.3, 1);
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
}

void handleKeyPress(char key) {
    if (!lockedMode) {    // if NORMAL
        if (key == 'D') {
            dPressCount++;
            if (dPressCount >= 2) {
                lockedMode = true;
                dPressCount = 0;
                showLockedMode();
                acceptPinInput = false;  // Ensure we don't accept PIN immediately after locking
            }
        } else {
            dPressCount = 0;
        }
    } else {    // if LOCKED
        if (key == 'E') {
            ePressCount++;
            if (ePressCount >= 2) {   // Press E two times to return to NORMAL
                ePressCount = 0;
                acceptPinInput = true;  // We can now accept PIN input
                lcd.setCursor(0, 1);
                lcd.print("PIN:   ");  // Prompt for PIN
                passwordInput = "";  // Reset PIN input
            }
        } else if (acceptPinInput && key >= '0' && key <= '9' && passwordInput.length() < 3) {
            passwordInput += key;
            lcd.setCursor(4 + passwordInput.length(), 1);
            lcd.print(key);
            if (passwordInput.length() == 3) {
                checkPassword();
            }
        } else {
            ePressCount = 0;
        }
    }
}


void checkPassword() {
  if (passwordInput == "123") {
    lockedMode = false;
    ePressCount = 0;
    showNormalMode();
  } else {
    lcd.setCursor(4, 1);
    lcd.print("    ");  // Clear all three entered digits
    passwordInput = "";
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