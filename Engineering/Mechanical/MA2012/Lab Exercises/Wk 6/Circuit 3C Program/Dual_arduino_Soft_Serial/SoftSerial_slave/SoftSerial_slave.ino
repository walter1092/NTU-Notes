//SoftSerial Communication between 2 arduino
//Includes blink without delay function. (Use boolean "blink" to start the blinking sequence)
//
//Program will blink led 3 times and send a '1' back to the master arduino once a "Hello" is received from master
//
//Created by ErJieKai for MA2012

#include <SoftwareSerial.h>
#define RxD 11
#define TxD 10

char recvChar;                                        //variable to store character received
String recvStr;                                       //variable to store the series of received character

boolean blink;

SoftwareSerial slave(RxD, TxD);                       //Slave arduino acts as a serial communication device

void setup()
{
  Serial.begin(9600);                                //start serial monitor, for communicating with the PC

  pinMode(RxD, INPUT);                               //set mode of receive pin (from bluetooth)
  pinMode(TxD, OUTPUT);                              //set mode of transmit pin (to bluetooth)
  slave.begin(9600);                                 //start the bluetooth serial "port"

  pinMode(13, OUTPUT);                               //set led pin to output

  recvStr = "";                                      //initialize the string to be empty
  blink = false;                                     //initialize the blink state to be false
}
void loop()
{
  if (slave.available())                            //if data is available from the master arduino
  {
    recvChar = slave.read();                        //store character received
    Serial.print(recvChar);                         //display character received on the serial monitor

    recvStr = String(recvStr + String(recvChar));   //concatenate the recvChar
  }
  else
  {
//    Serial.println(recvStr);
    //if the received string is "Hello", then blink led and send a '1' back to master arduino
    if (recvStr == "Hello")
    {
      Serial.println("Hello Received!");
      blink = true;                                //turn on the led when there is incoming data
      slave.write('1');                            //send a one back to master arduino
    }
    recvStr = "";                                  //clear the recvStr
  }

  if (blink == true)                              //blink led if blink==true
  {
    if (blinkWithoutDelay() == true)
      blink = false;
  }
}

boolean blinkWithoutDelay()
{
  unsigned long interval = 500; //ms
  unsigned long currentMillis = millis();         //store program runtime into currentMillis
  static unsigned long prevMillis;                //static variable to store the time instance when led state is toggled. static variable will self initialize to 0
  static int count;                               //static variable to store how many times the led has blink

  static boolean ledstate = LOW;                  //initialize ledstate to LOW

  if ((currentMillis - prevMillis) > interval)    //Toggle led state if the elapsed time between the last toggle time instance and current runtime is more than interval
  {
    ledstate = !ledstate;                         //toggle led state
    digitalWrite(13, ledstate);
    prevMillis = currentMillis;                   //update toggle time instance
    count++;                                      //update the number of times the led has toggle
  }

  if (count >= 6)                                 //return true when led has blinked 3 times (toggle on/off 6 times)
  {
    count = 0;
    return true;                                  //completed 3 blinks
  }
  else
  {
    return false;                                 //blinking has not been completed
  }


}

