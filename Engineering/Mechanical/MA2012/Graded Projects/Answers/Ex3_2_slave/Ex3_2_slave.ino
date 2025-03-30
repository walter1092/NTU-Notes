//SoftSerial Communication between 2 arduino

//Ex.3-2

#include <SoftwareSerial.h>
#define RxD 11
#define TxD 10

char recvChar;                                        //variable to store character received
String recvStr;                                       //variable to store the series of received character
int potential_1 = 0;                                  //digital value of the voltage received from MCU1
double voltage_1;                                     //analog value of the voltage received from MCU1
double voltage_ref;                                   //analog value of the input voltage from the voltage divider circuit
int refV = A0;                                        //reference voltage from the voltage divider circuit
boolean range;                                        //a boolean variable to check whether the voltage is in the range

SoftwareSerial slave(RxD, TxD);                       //Slave arduino acts as a serial communication device

void setup()
{
  Serial.begin(9600);                                //start serial monitor, for communicating with the PC

  pinMode(RxD, INPUT);                               //set mode of receive pin
  pinMode(TxD, OUTPUT);                              //set mode of transmit pin
  slave.begin(9600);                                 //start the serial "port"

  pinMode(13, OUTPUT);                               //set led pin to output
  pinMode(refV, INPUT);                              //set the voltage divider circuit as the input
  recvStr = "";                                      //initialize the string to be empty
}
void loop()
{
  voltage_ref = (double)analogRead(refV)/1023*5;
  voltage_ref = 2.5;
  if (slave.available())                             //if data is available from the master arduino
  {
    for (int i = 0; i<4; i++) {                      // 4 digits are transmitted           
      recvChar = slave.read();
      potential_1 = potential_1 + recvChar * (int)pow(10,i);
      recvStr = String(recvStr + String(recvChar));   //concatenate the recvChar
      }
    voltage_1 = (double)potential_1/1023*5; 
    Serial.println(voltage_1); 
  }


  if (abs(voltage_1 - voltage_ref) <= 0.1) {
    blinkWithoutDelay();
    if (range == false) {
      slave.write("BINGO");
      range = true;
      }
    }
   else {
    range = false;
    digitalWrite(13, LOW);
    }
  potential_1 = 0;
}

void blinkWithoutDelay()
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
  }
}
