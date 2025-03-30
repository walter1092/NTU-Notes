int optoPin = 5;
int echoPin = 8;
int trigPin = 9;
int analogPin = A5;
int buzzerPin = 4;

bool runUSorAnalog = 0; //0 to run US, 1 to run Analog

float getUSDist()
{
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  long duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  float distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  
  return distance;
}

float getAnalogDist()
{
  int val = analogRead(analogPin);
  float voltage = val*5.0/1023;
  //From the datasheet plot, find the formula that relates distance and voltage
  float distance = 28.966*pow(val, -1.118);
  
  return distance;
}

void soundBuzzer(float dist)
{
  if (dist < 0) //off the buzzer
  {
    noTone(buzzerPin);
  }
  else //sound the buzzer
  {
    int duration = 0; //determine the frequency
    if (dist > 40)
    {
      duration = 1000;
      tone(buzzerPin, 262, duration);
    }
    else if (dist > 20 && dist <= 40)
    {
      duration = 500;
      tone(buzzerPin, 262, duration);
    }
    else
    {
      duration = 0;
      tone(buzzerPin, 262); //continuously
    }
    
    delay(duration * 2); //2 times because it includs the "no sound" period
  }
}

void setup()
{
  //Setup ultrasound sensor
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
}

void loop()
{
  if (digitalRead(optoPin) == HIGH) //opto switch is blocked
  {
    float dist;
    if (runUSorAnalog == 0)
    {
      dist = getUSDist();
    }
    else
    {
      dist = getAnalogDist();
    }

    soundBuzzer(dist);
  }
  else //off buzzer when opto switch is not blocked
  {
    soundBuzzer(-1);
  }
}
