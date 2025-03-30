//SoftSerial Communication between 2 arduino
//
//Program will send a "Hello" to slave arduino if a '1' is send to master arduino from PC serial monitor
//Program will blink the led once if a '1' is received from slave arduino
//
//Created by ErJieKai for MA2012


#include <SoftwareSerial.h>
#define RxD 5
#define TxD 6

char recvChar;                                        //variable to store character received
SoftwareSerial master(RxD, TxD);                      //Master Arduino acts as a serial communication device

void setup()
{
  Serial.begin(9600);                                 //start serial monitor, for communicating with the PC

  pinMode(RxD, INPUT);                                //set mode of receive pin (from slave arduino)
  pinMode(TxD, OUTPUT);                               //set mode of transmit pin (to slave arduino)
  master.begin(9600);                                 //start the master serial "port"

  pinMode(13, OUTPUT);                                //set led pin to output
}
void loop()
{

  if (Serial.available())
  {
    //if 1 is received from pc, send "Hello" to slave arduino
    if (Serial.read() == '1') {                      
      Serial.println("Sending Hello");
      master.write("Hello");                          //Send "Hello" to Slave arduino
    }
  }

  if (master.available())                             //if data is available from the slave arduino
  {
    recvChar = master.read();                         //store character received
    Serial.print(recvChar);                           //display character received on the serial monitor (PC)
    //if the received data from slave arduino is '1' then blink led
    if (recvChar == '1') 
    {
      digitalWrite(13, HIGH);                        //if received character is 1, turn on the led
      delay(1000);
      digitalWrite(13, LOW);
    }
  }

}

