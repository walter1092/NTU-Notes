// Pins
const int toggleSwitchPin = 3;  // Toggle switch (Master ON/OFF)
const int onboardLedPin = 13;   // On-board LED

void setup() {
  // Initialize pins
  pinMode(toggleSwitchPin, INPUT);
  pinMode(onboardLedPin, OUTPUT);
}

void loop() {
  // Read the state of the toggle switch
  int toggleSwitchState = digitalRead(toggleSwitchPin);
  
  // Turn the onboard LED ON or OFF based on the toggle switch state
  digitalWrite(onboardLedPin, toggleSwitchState);
  
  if (toggleSwitchState == HIGH) {
    // The master switch is ON
    
    // Rest of the logic will go here
    
  } else {
    // The master switch is OFF, ensure everything else is off as well
    // This part will be filled in later
  }
}
