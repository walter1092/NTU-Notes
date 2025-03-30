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
bool cyclesTriggered = false;   // Whether the cycles have been triggered

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

  // If the master switch is OFF, nothing should happen
  if (toggleSwitchState == LOW) {
    cyclesTriggered = false;
    return;
  }

  // Read the state of the limit switch
  limitSwitchState = digitalRead(limitSwitchPin);

  // Check if the push button is pressed
  if (digitalRead(pushButtonPin) == HIGH && limitSwitchState == HIGH) {
    cyclesTriggered = true;
  }

  if (cyclesTriggered) {
    // Door is closed, master switch is ON, and button has been pressed
    for (int i = 0; i < 10; i++) {
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
        cyclesTriggered = false;
        return;
      }
      // Actuate the cutter
      digitalWrite(solenoidPin, HIGH);
      delay(500);

      // De-actuate the cutter
      digitalWrite(solenoidPin, LOW);
      delay(500);
    }
    // Reset cycles triggered flag after completing the cycles
    cyclesTriggered = false;
  } else {
    // Turn off the cutter if the master switch is OFF or door is open
    digitalWrite(solenoidPin, LOW);
  }
}
