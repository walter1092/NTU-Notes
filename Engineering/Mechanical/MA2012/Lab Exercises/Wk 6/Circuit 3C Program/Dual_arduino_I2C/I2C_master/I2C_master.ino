// I2C Master Arduino
// By ErJieKai for MA2012

// Include the required Wire library for I2C
#include <Wire.h>

int x = 0;

void setup() {
  // Start the I2C Bus as Master
  Wire.begin(); //include no input arguments to start arduino as master on i2c line
  Serial.begin(9600);
}

void loop() {
  Wire.beginTransmission(9); // transmit to device #9
  Wire.write("x is ");        // sends five bytes
  Wire.write(x);              // sends one byte
  Wire.endTransmission();    // stop transmitting
 
  x++; // Increment x
  if (x > 5) x = 0; // `reset x once it gets 6
  
  delay(200);

  Wire.requestFrom(9, 6);    // request 6 bytes from slave device #8

  while (Wire.available()) { // slave may send less than requested
    char c = Wire.read(); // receive a byte as character
    Serial.print(c);         // print the character
  }
  Serial.println();

  delay(500);
}

