void setup() {
  pinMode(10, OUTPUT); // Assuming the solenoid is connected to pin 10
}

void loop() {
  digitalWrite(10, HIGH); // Turn ON solenoid
  delay(1000);            // Wait for a second
  digitalWrite(10, LOW);  // Turn OFF solenoid
  delay(1000);            // Wait for a second
}
