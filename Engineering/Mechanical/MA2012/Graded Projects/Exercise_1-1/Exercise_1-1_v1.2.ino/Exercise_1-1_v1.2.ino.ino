// Pins
const int toggleSwitchPin = 3;  // Toggle switch (Master ON/OFF)
const int limitSwitchPin = 4;   // Limit switch (Safety door sensor)
const int pushButtonPin = 2;    // Pushbutton
const int solenoidPin = 10;     // Solenoid (Cutter)
const int buzzerPin = 8;        // Piezo Buzzer
const int onboardLedPin = 13;   // On-board LED

// Variables
int toggleSwitchState = 0;      // State of the toggle switch
int limitSwitchState = 0;       // State of the limit switch
int lastButtonState = LOW;      // Last state of the pushbutton
bool buttonPressed = false;     // Whether the button has been pressed

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
  // Read the state of the toggle and limit switches
  toggleSwitchState = digitalRead(toggleSwitchPin);
  limitSwitchState = digitalRead(limitSwitchPin);

  // Turn the onboard LED ON or OFF based on the toggle switch state
  digitalWrite(onboardLedPin, toggleSwitchState);

  // Read the current state of the push button
  int currentButtonState = digitalRead(pushButtonPin);

  // Check for button state change to HIGH (pressed)
  if (currentButtonState == HIGH && lastButtonState == LOW) {
    buttonPressed = true;
  }
  lastButtonState = currentButtonState;

  if (toggleSwitchState == HIGH && limitSwitchState == HIGH && buttonPressed) {
    // Door is closed, master switch is ON, and button has been pressed
    for (int i = 0; i < 10; i++) {
      // Actuate the cutter
      digitalWrite(solenoidPin, HIGH);
      delay(500);

      // De-actuate the cutter
      digitalWrite(solenoidPin, LOW);
      delay(500);

      // Check the safety door during the cycle
      limitSwitchState = digitalRead(limitSwitchPin);
      if (limitSwitchState == LOW) {
        // Door is open, stop the cycle and sound the buzzer
        for (int j = 0; j < 3; j++) {
          tone(buzzerPin, 1000, 200);
          delay(300);
        }
        // De-actuate the cutter immediately
        digitalWrite(solenoidPin, LOW);
        break;
      }
    }
    // Reset button pressed flag after completing the cycles
    buttonPressed = false;
  } else {
    // Turn off the cutter and onboard LED if the master switch is OFF or door is open
    digitalWrite(solenoidPin, LOW);
    digitalWrite(onboardLedPin, LOW);
  }
}
