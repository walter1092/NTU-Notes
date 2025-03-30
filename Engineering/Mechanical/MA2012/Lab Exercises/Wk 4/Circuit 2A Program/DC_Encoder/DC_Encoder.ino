/*
 Example for the encoded DC motor (MA2012)
 
 Please open the serial monitor and type in an integer, 
 which indicates the desired position for the DC motor (11*34.02 pulses per revolution)
 
*/
volatile long int encoder_pos = 0; 
int motor_speed;
int pin1 = 9;   // motor pin1
int pin2 = 10;  // motor pin2
int encoderPinA = 2;
int encoderPinB = 3;
int error = 10; // permissible error
int setPos = 0;   // Max value is 65535
char incomingByte;
void setup() {

  Serial.begin(9600);
  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(encoderPinA), encoder, RISING); // Enable the external interrupt

}

void loop() {
  if (Serial.available() > 0) {  
      setPos = 0; 
      bool movingBackward = 0;    
      while(1) {
        // read the content from the serial monitor and convert it from character to the integer          
        incomingByte = Serial.read();
        if (incomingByte == '\n') break; 
        if (incomingByte == '\r') continue;  
        if (incomingByte == '-') {
          movingBackward = 1;
          continue;
        }
        
        if((incomingByte - 48) >= 0 && (incomingByte - 48) < 10) {
          setPos *= 10; 
          setPos = ((incomingByte - 48) + setPos);
        }  
      }
      if (movingBackward == 1) {
        setPos = -setPos;
     }
  }
  Serial.print("Target Postion: ");
  Serial.println(setPos);
  
  if (abs(setPos - encoder_pos)> error && (setPos > encoder_pos)) {
    motor_speed = 100; // set the speed of the motor
  } 
  else if (abs(setPos - encoder_pos)> error && (setPos < encoder_pos)){
    motor_speed = -100;
    }
  else {
    motor_speed = 0;
    }
    
  if(motor_speed > 0){
    MotorClockwise(motor_speed);
  }else{
    MotorCounterClockwise(abs(motor_speed));
  }
    Serial.print("Current Position: ");  
    Serial.println(encoder_pos);
    delay(10);
  }


void encoder(){
  if(digitalRead(encoderPinB) == HIGH){
    encoder_pos++;
  }else{
    encoder_pos--;
  }
}

void MotorClockwise(int power){
  if(power >60){  // set the min value as 60 because of the motor inertia
  analogWrite(pin1, power);
  digitalWrite(pin2, LOW);
  }else{
    digitalWrite(pin1, LOW);
    digitalWrite(pin2, LOW);
  }
}

void MotorCounterClockwise(int power){
  if(power > 60){
  analogWrite(pin2, power);
  digitalWrite(pin1, LOW);
  }else{
    digitalWrite(pin2, LOW);
    digitalWrite(pin1, LOW);
  }
}
