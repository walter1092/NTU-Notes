//SoftSerial Communication between 2 arduino

//Ex.3-2


#include <SoftwareSerial.h>
#define RxD 5
#define TxD 6
int potential = A0;
int voltage;
String recvStr;
char recvChar;                                        //variable to store character received
SoftwareSerial master(RxD, TxD);                      //Master Arduino acts as a serial communication device
int temp;
void setup()
{
  Serial.begin(9600);                                 //start serial monitor, for communicating with the PC

  pinMode(RxD, INPUT);                                //set mode of receive pin (from slave arduino)
  pinMode(TxD, OUTPUT);                               //set mode of transmit pin (to slave arduino)
  master.begin(9600);                                 //start the master serial "port"
  recvStr = "";
  
  pinMode(13, OUTPUT);                                //set led pin to output
  pinMode(potential, INPUT);
}
void loop()
{
    voltage = analogRead(potential);
    // transfer the value of the integer digit by digit
    for (int i = 0; i<4; i++) {
      temp =  voltage % 10;
      voltage = voltage / 10;
      master.write(temp);
      }
    delay(200);

  if (master.available())                             //if data is available from the slave arduino
  {
    
    recvChar = master.read();                         //store character received
    recvStr = String(recvStr + String(recvChar));
  }
  else {
    if (recvStr == "BINGO") {
       Serial.println(recvStr);                           //display character received on the serial monitor (PC)
    }
    recvStr = "";
    }

}
