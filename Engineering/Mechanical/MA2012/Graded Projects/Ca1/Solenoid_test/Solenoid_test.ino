const int solenoidPin = 2;

void setup() {
  pinMode(solenoidPin, OUTPUT);
}

void loop() {
  digitalWrite(solenoidPin, HIGH);
  delay(2000);
  digitalWrite(solenoidPin, LOW);
  delay(2000);
}
