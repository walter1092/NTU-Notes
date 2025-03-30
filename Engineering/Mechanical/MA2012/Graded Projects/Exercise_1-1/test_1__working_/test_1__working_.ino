// Pins
const int toggleSwitchPin = 3;  // Toggle switch (Master ON/OFF)
const int limitSwitchPin = 4;   // Limit switch (Safety door sensor)
const int pushButtonPin = 2;    // Pushbutton
const int solenoidPin = 10;     // Solenoid (Cutter)
const int buzzerPin = 8;        // Piezo Buzzer
const int onboardLedPin = 13;   // On-board LED
const int breadboardLedPin = 9; // Additional LED


// Variables
int toggleSwitchState = 0;  // State of the toggle switch
int limitSwitchState = 0;   // State of the limit switch
int lastButtonState = LOW;  // Previous state of the button
bool shouldPerformCycles = false;  // Whether to perform the 10 cycles
int cyclesCompleted = 0;  // Number of cycles completed

void setup() {
  pinMode(toggleSwitchPin, INPUT_PULLUP); // Enable internal pull-up resistor
  pinMode(limitSwitchPin, INPUT); // No pull-up or pull-down
  pinMode(pushButtonPin, INPUT_PULLUP); // Enable internal pull-up resistor
  pinMode(solenoidPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(onboardLedPin, OUTPUT);
  pinMode(breadboardLedPin, OUTPUT);
}


void loop() {
  toggleSwitchState = !digitalRead(toggleSwitchPin);
  limitSwitchState = digitalRead(limitSwitchPin);
  int buttonState = !digitalRead(pushButtonPin);
  
  // Update the onboard LED based on the toggleSwitchState
  digitalWrite(onboardLedPin, toggleSwitchState);
  digitalWrite(breadboardLedPin, shouldPerformCycles);

  
  if (toggleSwitchState == HIGH) {
    // Master switch is ON
    
    // Start the cycles with the push button and only if cycles are not already running
    if (buttonState == HIGH && !shouldPerformCycles) {
      shouldPerformCycles = true;
      cyclesCompleted = 0;
    }

    if (shouldPerformCycles && cyclesCompleted < 10) {
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
        }
      } else {
        // Safety door is open, stop the cycle
        tone(buzzerPin, 1000, 200);
        delay(300);

        // De-actuate the cutter immediately
        digitalWrite(solenoidPin, LOW);
        shouldPerformCycles = false;
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
