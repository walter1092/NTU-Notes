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
int pushButtonState = 0;        // State of the pushbutton
int solenoidState = 0;          // State of the solenoid (Cutter)
int buzzerState = 0;            // State of the buzzer
int buttonPressCount = 0; // <-- Added semicolon here

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
  int toggleSwitchState = digitalRead(toggleSwitchPin);
  // Read the state of the limit switch
  int limitSwitchState = digitalRead(limitSwitchPin);

  // Turn the onboard LED ON or OFF based on the toggle switch state
  digitalWrite(onboardLedPin, toggleSwitchState); // <-- Changed ledPin to onboardLedPin
  
  if (toggleSwitchState == HIGH && limitSwitchState == HIGH) {
    // Door is closed and master switch is ON
    
    // Read the state of the push button
    int buttonState = digitalRead(pushButtonPin);
    static int buttonPressCount = 0; // Count of button presses
    
    // Check if the button is pressed
    if (buttonState == HIGH) {
      buttonPressCount++;
      
      // Perform 10 cycles of cutter actuation and de-actuation
      if (buttonPressCount == 1) {
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
            // Door is open, stop the cycle
            for (int j = 0; j < 3; j++) {
              tone(buzzerPin, 1000, 200);
              delay(300);
            break;
            }
            // De-actuate the cutter immediately
            digitalWrite(solenoidPin, LOW);
            break;
          }
        }
      }
    } else {
      // Reset button press count when button is not pressed
      buttonPressCount = 0;
    }
  } else {
    // Turn off the cutter and onboard LED if the master switch is OFF or door is open
    digitalWrite(solenoidPin, LOW);
    digitalWrite(onboardLedPin, LOW);
  }
}
