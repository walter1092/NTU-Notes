#include <SoftwareSerial.h>
#define RxD 2
#define TxD 3

char recvChar;                                        //variable to store character received
SoftwareSerial blueToothSerial(RxD,TxD);              //bluetooth device acts as a serial communication device
                                                      //receive and transmit with respect to the Arduino board
void setup()
{
    Serial.begin(9600);                               //start serial monitor, for communicating with the PC
    
    pinMode(RxD, INPUT);                              //set mode of receive pin (from bluetooth)
    pinMode(TxD, OUTPUT);                             //set mode of transmit pin (to bluetooth)
    blueToothSerial.begin(9600);                      //start the bluetooth serial "port"

    pinMode(13, OUTPUT);                              //set led pin to output
}
void loop()
{  
  if(blueToothSerial.available())                     //if data is available from the bluetooth device
  {
      recvChar = blueToothSerial.read();              //store character received
      Serial.print(recvChar);                         //display character received on the serial monitor
      if(recvChar == '1') digitalWrite(13, HIGH);     //if received character is 1, turn on the led
      else if(recvChar == '0') digitalWrite(13, LOW); //otherwise, if '0' is received, turn off the led
  }
  if(Serial.available())                              //if character is received from the serial monitor (PC)
  {
      recvChar  = Serial.read();                      //store character received
      blueToothSerial.print(recvChar);                //send character via bluetooth
  }
}

