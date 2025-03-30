/*
  Exercise 1-3;
*/
int potential = A0;
int led1 = 9;
int led2 = 10;
int led3 = 11;
double voltage;
int brightness;
int level;
void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(potential, INPUT);
  Serial.begin(9600);
  // put your setup code here, to run once:
  
}

void loop() {
  voltage = (double)analogRead(potential)/1023*5;
  brightness = (int)(voltage/5*255);
  delay(10);
  analogWrite(led1, brightness);
  analogWrite(led2, brightness);
  analogWrite(led3, brightness);

  level = (int)(voltage/1.25);
 /* switch(level) {
    case 0: {
             digitalWrite(led1, LOW);
             digitalWrite(led2, LOW);
             digitalWrite(led3, LOW);
             break;
    }
    case 1: {digitalWrite(led1, HIGH);
             digitalWrite(led2, LOW);
             digitalWrite(led3, LOW);
             break;
    }
    case 2: {digitalWrite(led1, HIGH);
             digitalWrite(led2, HIGH);
             digitalWrite(led3, LOW);
             break;
    }
    default: {digitalWrite(led1, HIGH);
             digitalWrite(led2, HIGH);
             digitalWrite(led3, HIGH);
             break;
    }    
    }*/
  // put your main code here, to run repeatedly:
}
