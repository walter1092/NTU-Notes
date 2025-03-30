/*
  Program for Exercise 2-3: calculator
  Cui Shuai
*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 6, en = 7, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


// Pins for 74C922 keypad encoder
int KB_DataAvailable=A5;//Data ready pin from Keyboard
int KB_A=10;
int KB_B=11;
int KB_C=12;
int KB_D=13;

int state = 0; // 0 for displaying entered keys, 1 for calculator
int start = 0; // global variable for knowing when to exit the welcome screen
int op = -1;   // global variable for storing the operator
char check = ' '; // global variable for changing the working mode 
int new_exp = 0;  // global variable for starting a new operation

// Declare keypad layout
char keys[] = {'1','2','3','F',
               '4','5','6','E',
               '7','8','9','D',
               'A','0','B','C'};
int calc[] = { 1,2,3,'F',
               4,5,6,'=',
               7,8,9,'/',
               '+',0,'-','*'};
               
#define NO_OF_COLS 16
char expression[NO_OF_COLS + 1];// array for the expression
 

#define NO_OF_DIGS 3
char result[NO_OF_DIGS*2 + 1]; // array for the calculation result
long cal_result;               // value of the calculation result

long num1 = 0;       // the first number
long num2 = 0;       // the second number

void setup(void) {
  int j, k;
  for(j = 0;j < NO_OF_COLS;j++) expression[j] = ' '; 
  for(k = 0;k < 2*NO_OF_DIGS;k++) result[k] = ' ';
  
  expression[NO_OF_COLS] = 0;
  result[2*NO_OF_DIGS] = 0;
  
  //initialize pins for keypad
  pinMode(KB_DataAvailable,INPUT);
  pinMode(KB_A,INPUT);
  pinMode(KB_B,INPUT);
  pinMode(KB_C,INPUT);
  pinMode(KB_D,INPUT);

  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("MA2012 Ex.2-3");
  Serial.begin(9600);
}

void loop(void) {
    //check if the keypad is hit
    if(digitalRead(KB_DataAvailable))
    { 
      if (start == 0) {  // exit the welcome screen
        lcd.clear();
        start = 1;
      }
      KB_Read(); //read the keypad
      delay(222);      // rebound
      if (state == 0) {     // displaying entered keys
          lcd.setCursor(0, 0);
          lcd.print(expression);
        } else {           // calculator
          lcd.setCursor(0, 0);
          lcd.print(expression);
          lcd.setCursor(NO_OF_COLS - NO_OF_DIGS*2, 1);
          lcd.print(result);
          }
    }
}
void KB_Read() {
  int ka,kb,kc,kd,i;
  char k;
  ka=digitalRead(KB_A); //read encoder output A
  kb=digitalRead(KB_B); //read encoder output B
  kc=digitalRead(KB_C); //read encoder output C
  kd=digitalRead(KB_D); //read encoder output D

  k=ka+kb*2+kc*4+kd*8; // combine the encoder outputs
  if (new_exp == 1) {
      resetExpression();
      new_exp = 0;
    }
  if (!(state == 1 && keys[k] == 'F')) {
    for(i=0;i<(NO_OF_COLS-1);i++) expression[i]=expression[i+1];//move displayed characters in FIFO queue forward discarding the first one
    expression[NO_OF_COLS-1] = keys[k]; // update the key into the queue
    expression[NO_OF_COLS] = 0; // end with NULL
    }
    
  if (keys[k] == 'F' && check == ' ') {
      check = 'F';
    } else if (keys[k] == 'F' && check == 'F') {
      state = 1;
      check = ' ';
      resetExpression();
      resetResult();
      num1 = 0;
      num2 = 0;
      op = -1;
      cal_result = 0;
      lcd.clear();
      } else if (keys[k] == 'E' && check == 'F') {
        state = 0;
        check = ' ';
        resetExpression();
        resetResult();
        lcd.clear();
        } else {
          check = ' ';
          }
          
   if (state == 1) {
        switch (calc[k]) { // check whitch operator was pressed
          case '+': 
              expression[NO_OF_COLS-1] = '+';
              op = '+';
              break;
          case '-':
              expression[NO_OF_COLS-1] = '-';
              op = '-';
              break;
          case '*':
              expression[NO_OF_COLS-1] = '*';
              op = '*';
              break;
          case '/':
              expression[NO_OF_COLS-1] = '/';
              op = '/';
              break;
          case '=':
              expression[NO_OF_COLS-1] = '=';
    }
    if (calc[k] < 10) {  // if digits are entered
      if (op == -1) {
          num1 = num1*10 + calc[k];
         } 
      else {
          num2 = num2*10 + calc[k];
      }
    }
    if (calc[k] == '=') { // if "=" is pressed
      if (op == '+')  cal_result = num1 + num2;
      if (op == '-')  cal_result = num1 - num2;
      if (op == '*')  cal_result = num1 * num2;
      if (op == '/')  cal_result = num1 / num2;
      num1 = 0;          // reset number 1
      num2 = 0;          // reset number 2
      op = -1;           // reset the operator
      new_exp = 1;       // ready to start a new operation
      resetResult();     
      intTochar(cal_result);
    }   
  }
} 

void resetExpression() {
  int l;
  for (l = 0;l<(NO_OF_COLS);l++) expression[l] = ' ';
  expression[NO_OF_COLS] = 0;
}

void resetResult() {
  int l;
  for (l = 0;l<(NO_OF_DIGS * 2);l++) result[l] = ' ';
  result[NO_OF_DIGS] = 0;
}
/*
  helper function for converting the integer to an anray of chars
*/
void intTochar(long n) { 
  long m = n;
  char s[2*NO_OF_DIGS+1];
  int i=0,j=0;
  if (n < 0)
    {
      m = 0 - m;
      j = 1;
      result[0] = '-';
    }    
   while (m>0)
    {
      s[i++] = m % 10 + '0';
      m /= 10;
    }
   s[i] = ' ';
   i = i - 1;
   while (i >= 0)
    {
      result[j++] = s[i--];
    }    
   result[j] = ' ';
   if (result[0] == ' ') result[0] = '0';
   lcd.clear();     
}
