
#define NOTE_C6  1047
#define NOTE_D6  1175
#define NOTE_E6  1319

//Set pin numbers:
const int buttonPin = 2; // push button pin
const int togglePin = 3; // toggle button pin
const int limitPin = 4; // limit pin
const int ledPin =  13; // LED pin
const int solenoidPin = 9; // solenoid pin

//Variables will change:
int buttonState = 0; // push button status
int doorState = 0; // door status
int switchState = 0; // switch status

int previousButtonState = -1;
int cutCount=0; //number of cuts performed
int cutState=0; //determine if it is cutting now
int isDepressedOnce = 0; //determine if button is depressed

void setup()
{
  //Initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  pinMode(solenoidPin, OUTPUT);
  //Initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  pinMode(togglePin, INPUT);
  pinMode(limitPin, INPUT);
}

void loop()
{
  //Read the states
  buttonState = digitalRead(buttonPin);
  doorState = digitalRead(limitPin);
  switchState = digitalRead(togglePin);

  digitalWrite(ledPin, switchState); //toggle LED according to switch state

  //Check if button is pressed and released
  if (previousButtonState == LOW && buttonState == HIGH)
  {
    isDepressedOnce = 1;
  }
  previousButtonState = buttonState;

  //Move the solenoid if all conditions are satisfied
  if (switchState == HIGH && isDepressedOnce == 1 && doorState == HIGH && cutCount<10)
  {
    digitalWrite(solenoidPin, LOW);
    delay(200);
    digitalWrite(solenoidPin, HIGH);
    delay(200);
    cutCount++;
    cutState=1;
  }
  if(cutCount>=10) cutState=0;
  
  if (doorState == LOW) //door open
  {
    //Sound buzzer if it was cutting
    if(cutState==1)
    {
      tone(8, NOTE_E6, 250);
      delay(250);
      noTone(8);delay(100);
      tone(8, NOTE_D6, 250);
      delay(250);
      noTone(8);delay(100);
      tone(8, NOTE_C6, 250);
      delay(250);
      noTone(8);delay(100);
    }
    cutState=0;
    cutCount=0;
  }
  
  //Reset it when finished running or main switch is off
  if ((cutState == 0 && isDepressedOnce == 1) || switchState == LOW)
  {
    isDepressedOnce = 0;
    cutState=0;
    cutCount=0;
  }
}
