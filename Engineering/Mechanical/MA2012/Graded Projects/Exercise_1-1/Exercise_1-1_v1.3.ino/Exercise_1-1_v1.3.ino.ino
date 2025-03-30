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
bool buttonWasPressed = false;  // State of the button in the last loop

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
  // Read the state of the limit switch
  limitSwitchState = digitalRead(limitSwitchPin);
  // Read the state of the push button
  int buttonState = digitalRead(pushButtonPin);

  // Turn the onboard LED ON or OFF based on the toggle switch state
  digitalWrite(onboardLedPin, toggleSwitchState);

  // Check for button press
  if (buttonState == HIGH && !buttonWasPressed && limitSwitchState == HIGH) {
    cyclesTriggered = true;
  }
  buttonWasPressed = (buttonState == HIGH); // Update button state

  if (cyclesTriggered && limitSwitchState == HIGH) {
    // Perform 10 cycles
    for (int i = 0; i < 10; i++) {
      // Check the safety door during the cycle
      if (digitalRead(limitSwitchPin) == LOW) {
        // Door is opened, stop the cycle and sound the buzzer
        for (int j = 0; j < 3; j++) {
          tone(buzzerPin, 1000, 200);
          delay(300);
        }
        // De-actuate the cutter
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
    cyclesTriggered = false;  // Reset after 10 cycles
  } else {
    // De-actuate the cutter if the master switch is OFF or door is opened
    digitalWrite(solenoidPin, LOW);
  }
}
