int pin1 = 9; // assigns pin 3 to variable pwm (motor pin)
int pin2 = 10;
int space;   // declares variable space
int mark= 200;   // declares variable mark


void setup()  // setup loop
{
   pinMode(pin1, OUTPUT);  // declares pin 3 as output
   pinMode(pin2, OUTPUT);  // declares pin 2 as output
   Serial.begin(9600);
}

void loop()
{
  direction(1);
  delay(5000);
  direction(2);
  delay(5000);
  direction(0);
  delay(5000);

}

void direction (int dir)
{
  //dir 1 = forward
  //    2 = reverse
  //    0 = stop

  switch (dir)
  {
    case (1):
    {
      analogWrite(pin1,200);
      digitalWrite(pin2,LOW);
      Serial.println("Forward");
      break;
    }
    case(2):
    {
      analogWrite(pin1,55);
      digitalWrite(pin2,HIGH);
      Serial.println("Backward");
      break;
    }
    case(0):
    {
      analogWrite(pin1,0);
      digitalWrite(pin2,LOW);
      Serial.println("Brake");
      break;
    }
    default: // also brake
     {
      analogWrite(pin1,0);
      digitalWrite(pin2,LOW);
      Serial.println("Brake");
      break;
    }
  }
  
}
