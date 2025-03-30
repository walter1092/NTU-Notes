// I2C Slave Arduino
// By ErJieKai for MA2012


// Include the required Wire library for I2C
#include <Wire.h>

int LED = 13;
int x = 0;

void setup() {
  pinMode (LED, OUTPUT); // Define the LED pin as Output
  Wire.begin(9); // Start the I2C Bus as Slave on address 9
  Wire.onReceive(receiveEvent); // Attach a function to trigger when some data is received.
  Wire.onRequest(requestEvent); // Attach a function to trigger when a request is received
  Serial.begin(9600);
}

void receiveEvent(int bytes) {
  while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  Serial.print(" : ");
  x = Wire.read();    // receive byte as an integer
  Serial.println(x);
}

void requestEvent() {
  Wire.write("hello "); // respond with message of 6 bytes
  // as expected by master
}

void loop() {
  //why does the LED blink twice when x==0 but only once when x==3?

  
  //If value received is 0 blink LED for 200 ms
  if (x == 0) {
    Serial.println("Inside x==0");
    digitalWrite(LED, HIGH);
    delay(200);
    digitalWrite(LED, LOW);
    delay(200);
  }
  //If value received is 3 blink LED for 400 ms
  if (x == 3) {
    Serial.println("Inside x==3");
    digitalWrite(LED, HIGH);
    delay(400);
    digitalWrite(LED, LOW);
    delay(400);
  }
}

