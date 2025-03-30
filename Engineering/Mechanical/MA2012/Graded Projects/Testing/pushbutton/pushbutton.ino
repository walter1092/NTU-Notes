const int pushButtonPin = 2;  // Pin number for the push button

void setup() {
  Serial.begin(9600);           // Initialize serial communication
  pinMode(pushButtonPin, INPUT);  // Set the push button pin as an input
}

void loop() {
  int buttonState = digitalRead(pushButtonPin);  // Read the state of the push button
  Serial.print("Button state: ");
  Serial.println(buttonState);  // Print the state to the Serial Monitor
  delay(500);  // Add a small delay to make it easier to read
}
