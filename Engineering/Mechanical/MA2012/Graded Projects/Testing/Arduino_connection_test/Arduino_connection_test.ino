// Pins
const int toggleSwitchPin = 3;  // Toggle switch (Master ON/OFF)
const int limitSwitchPin = 4;   // Limit switch (Safety door sensor)
const int pushButtonPin = 2;    // Pushbutton
const int onboardLedPin = 13;   // On-board LED

void setup() {
  // Initialize pins
  pinMode(toggleSwitchPin, INPUT);
  pinMode(limitSwitchPin, INPUT);
  pinMode(pushButtonPin, INPUT);
  pinMode(onboardLedPin, OUTPUT);
}

void loop() {
  // Read the state of the toggle switch
  int toggleSwitchState = digitalRead(toggleSwitchPin);
  int limitSwitchState = digitalRead(limitSwitchPin);
  int pushButtonState = digitalRead(pushButtonPin);

  // Turn the onboard LED ON or OFF based on the toggle switch state
  digitalWrite(onboardLedPin, toggleSwitchState);

  // For debugging purposes, we can turn on the LED when each switch is pressed
  if (toggleSwitchState == HIGH) {
    if (limitSwitchState == HIGH) {
      // Do something when the limit switch is pressed
      // For now, we will just blink the onboard LED quickly
      digitalWrite(onboardLedPin, HIGH);
      delay(100);
      digitalWrite(onboardLedPin, LOW);
      delay(100);
    }
    
    if (pushButtonState == HIGH) {
      // Do something when the push button is pressed
      // For now, we will just blink the onboard LED slowly
      digitalWrite(onboardLedPin, HIGH);
      delay(500);
      digitalWrite(onboardLedPin, LOW);
      delay(500);
    }
  }
  
  delay(100);  // Short delay to reduce CPU usage
}
