// Pins
const int limitSwitchPin = 4;   // Limit switch (Safety door sensor)
const int pushButtonPin = 2;    // Pushbutton
const int solenoidPin = 10;     // Solenoid (Cutter)
const int buzzerPin = 8;        // Piezo Buzzer
const int externalLedPin = 9;   // External LED

// Variables
int lastButtonState = HIGH;      // Previous state of the button
bool shouldPerformCycles = false;  // Whether to perform the 10 cycles
int cyclesCompleted = 0;        // Number of cycles completed

void setup() {
  // Initialize pins
  pinMode(limitSwitchPin, INPUT);
  pinMode(pushButtonPin, INPUT);
  pinMode(solenoidPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(externalLedPin, OUTPUT);
}

void loop() {
  // Read the current state of the push button
  int buttonState = digitalRead(pushButtonPin);

  // If button was just pressed and released and cycles not in progress, start cycles
  if (buttonState == LOW && lastButtonState == HIGH && !shouldPerformCycles && digitalRead(limitSwitchPin) == HIGH) {
    shouldPerformCycles = true;
    cyclesCompleted = 0;
  }
  lastButtonState = buttonState;

  if (shouldPerformCycles && cyclesCompleted < 10) {
    // If the safety door is closed
    if (digitalRead(limitSwitchPin) == HIGH) {
      // Actuate the cutter and light the LED
      digitalWrite(solenoidPin, HIGH);
      delay(250);  // Actuation time

      // De-actuate the cutter
      digitalWrite(solenoidPin, LOW);
      delay(250);  // Time before the next cycle

      cyclesCompleted++;
    } else {
      // Safety door is open, sound the buzzer and stop the cycle
      for (int i = 0; i < 3; i++) {
        tone(buzzerPin, 1000, 200);
        delay(300);
      }
      shouldPerformCycles = false;
    }
  }

  // Ensure everything is off after cycles
  if (cyclesCompleted >= 10) {
    shouldPerformCycles = false;
    digitalWrite(solenoidPin, LOW);
  }
}
