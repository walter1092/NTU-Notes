//This program reads a keypad and print out the key to serial output

// Pins for 74C922 keypad encoder
int KB_DataAvailable=A5;//Data ready pin from Keyboard
int KB_A=10; //Output A
int KB_B=11; //Output B
int KB_C=12; //Output C
int KB_D=13; //Output D

// Declare keypad layout
char keys[] = {'1','2','3','F',
               '4','5','6','E',
               '7','8','9','D',
               'A','0','B','C'};

void setup(void) {
  //initialize pins for keypad
  pinMode(KB_DataAvailable,INPUT);
  pinMode(KB_A,INPUT);
  pinMode(KB_B,INPUT);
  pinMode(KB_C,INPUT);
  pinMode(KB_D,INPUT);
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}
char c;
void loop(void) {  
    //check if the keypad is hit
    if(digitalRead(KB_DataAvailable)) {
      c=KB_Read(); //read the keypad      
      Serial.println(c);// print out the key
      delay(100);// debounce
    }
}
char KB_Read() {
  int ka,kb,kc,kd,k;
  ka=digitalRead(KB_A); //read encoder output A
  kb=digitalRead(KB_B); //read encoder output B
  kc=digitalRead(KB_C); //read encoder output C
  kd=digitalRead(KB_D); //read encoder output D
  k=ka+kb*2+kc*4+kd*8; // combine the encoder outputs 
  return keys[k];
}

