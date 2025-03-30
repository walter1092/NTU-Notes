const int limitSwitchPin = 4;  // Limit switch pin

void setup() {
  pinMode(limitSwitchPin, INPUT);  // Initialize limitSwitchPin as an input
  Serial.begin(9600);  // Start serial communication at 9600 bps
}

void loop() {
  int limitSwitchState = digitalRead(limitSwitchPin);  // Read the state of the limit switch
  Serial.println(limitSwitchState);  // Print the state to the Serial Monitor
  delay(1000);  // Wait for a second
}
