const int pushButtonPin = 2;    // Pushbutton
const int onboardLedPin = 13;   // On-board LED

int lastButtonState = LOW;  // Previous state of the button
bool shouldPerformCycles = false;  // Whether to perform the 10 cycles

void setup() {
  pinMode(pushButtonPin, INPUT);
  pinMode(onboardLedPin, OUTPUT);
}

void loop() {
  int buttonState = digitalRead(pushButtonPin);  // Read the state of the push button
  
  // Check for button state change
  if (buttonState != lastButtonState) {
    delay(50);  // Debounce delay
    if (buttonState == HIGH) {
      shouldPerformCycles = !shouldPerformCycles;  // Toggle the flag
      digitalWrite(onboardLedPin, shouldPerformCycles);  // Update LED based on flag
    }
    lastButtonState = buttonState;
  }
  
  // This is where you would put the solenoid control logic, but for now, it's omitted to focus on the button press.
}
