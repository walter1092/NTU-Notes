// Pins
const int toggleSwitchPin = 3;  // Toggle switch (Master ON/OFF)
const int limitSwitchPin = 4;   // Limit switch (Safety door sensor)
const int pushButtonPin = 2;    // Pushbutton
const int solenoidPin = 10;     // Solenoid (Cutter)
const int buzzerPin = 8;        // Piezo Buzzer
const int onboardLedPin = 13;   // On-board LED

// Variables
int toggleSwitchState = 0;  // State of the toggle switch
int limitSwitchState = 0;   // State of the limit switch
int lastButtonState = LOW;  // Previous state of the button
bool shouldPerformCycles = false;  // Whether to perform the 10 cycles
int cyclesCompleted = 0;  // Number of cycles completed

void setup() {
  // Initialize pins
  pinMode(toggleSwitchPin, INPUT);
  pinMode(limitSwitchPin, INPUT);
  pinMode(pushButtonPin, INPUT);
  pinMode(solenoidPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(onboardLedPin, OUTPUT);
}

void loop() {
  // Read the state of the toggle switch
  toggleSwitchState = digitalRead(toggleSwitchPin);

  // Read the current state of the push button
  int buttonState = digitalRead(pushButtonPin);

  if (buttonState != lastButtonState) {
    delay(50);  // Debounce delay
    if (buttonState == HIGH) {
      shouldPerformCycles = !shouldPerformCycles;  // Toggle the flag
    }
    lastButtonState = buttonState;  // Save the current state as the last state for the next loop
  }

  // Update the onboard LED based on the shouldPerformCycles flag
  digitalWrite(onboardLedPin, shouldPerformCycles);

  if (toggleSwitchState == HIGH) {
    // Master switch is ON

    if (shouldPerformCycles && cyclesCompleted < 10) {
      // Check the safety door before each cycle
      limitSwitchState = digitalRead(limitSwitchPin);
      if (limitSwitchState == HIGH) {
        // Safety door is closed, proceed with actuation
        digitalWrite(solenoidPin, HIGH);
        delay(500);
  
        // De-actuate the cutter
        digitalWrite(solenoidPin, LOW);
        delay(500);
  
        cyclesCompleted++;
        if (cyclesCompleted >= 10) {
          // Reset after 10 cycles
          shouldPerformCycles = false;
          cyclesCompleted = 0;
        }
      } else {
        // Safety door is open, stop the cycle
        tone(buzzerPin, 1000, 200);
        delay(300);
  
        // De-actuate the cutter immediately
        digitalWrite(solenoidPin, LOW);
        shouldPerformCycles = false;  // Reset the flag
        cyclesCompleted = 0;  // Reset the counter
      }
    }
  } else {
    // Master switch is OFF, reset all states
    shouldPerformCycles = false;
    cyclesCompleted = 0;
    digitalWrite(solenoidPin, LOW);
    digitalWrite(buzzerPin, LOW);
  }
}
