int sensorPin = 5;     // potentiometer wiper (middle terminal) connected to digital pin 6
                       // outside leads to ground and +5V
int sensorState = 0;   // initial start value of the sensor status

void setup()
{
  pinMode(sensorPin, INPUT);   // define pin as input
  Serial.begin(9600);          //  setup serial
}

void loop()
{
  sensorState = digitalRead(sensorPin);    // read the digital input pin and store status value
  Serial.println(sensorState);             // debug value
}


