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
int buttonPressCount = 0;   // Count of button presses
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

  // Turn the onboard LED ON or OFF based on the toggle switch state
  digitalWrite(onboardLedPin, toggleSwitchState);

  if (toggleSwitchState == HIGH) {  // Master switch is ON
    int buttonState = digitalRead(pushButtonPin);  // Read the state of the push button

    if (buttonState != lastButtonState) {  // Check for button state change
      delay(50); // Debounce delay
      if (buttonState == HIGH && cyclesCompleted == 0) {
        buttonPressCount += 1;
      }
      lastButtonState = buttonState;
    }

    if (buttonPressCount > 0 && cyclesCompleted < 10) {  // Check if should perform cycles and not completed yet
      limitSwitchState = digitalRead(limitSwitchPin);  // Check the safety door before each cycle
      if (limitSwitchState == HIGH) {  // Safety door is closed, proceed with actuation
        digitalWrite(solenoidPin, HIGH);
        delay(500);
        digitalWrite(solenoidPin, LOW);  // De-actuate the cutter
        delay(500);
        cyclesCompleted += 1;  // Increment cycles
        if (cyclesCompleted >= 10) {  // Reset after 10 cycles
          cyclesCompleted = 0;
          buttonPressCount = 0;
        }
      } else {  // Door is open, stop the cycle
        for (int j = 0; j < 3; j++) {
          tone(buzzerPin, 1000, 200);
          delay(300);
        }
        digitalWrite(solenoidPin, LOW);  // De-actuate the cutter immediately
        cyclesCompleted = 0;  // Reset the counter
        buttonPressCount = 0;  // Reset button press count
      }
    }
  } else {  // Master switch is OFF, turn off all other components
    cyclesCompleted = 0;
    buttonPressCount = 0;
    digitalWrite(solenoidPin, LOW);
    digitalWrite(buzzerPin, LOW);
  }
  delay(5000);
}
