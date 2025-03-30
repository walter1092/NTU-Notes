#include <SPI.h>
const int CS_Pin = 10;// set pin 10 as the chip select
SPISettings settingsA(2000000, MSBFIRST, SPI_MODE3); // set up the speed, data order and data mode
//SPI pin configuration: pin 11 as MOSI (SDI), pin 12 as MISO (SDO) , pin 13 as clock (SPC)

int range = 8; //measurement range, can be 2g, 4g, 8g, 16g

void setup() {
  Serial.begin(9600);
  
  pinMode (CS_Pin, OUTPUT);  //Chip Select pin to control SPI
  digitalWrite(CS_Pin, HIGH);//Disable SPI
  SPI.begin();
  SPI.beginTransaction(settingsA);

  //Read the ID, pg15
  digitalWrite(CS_Pin, LOW);//Enable SPI
  SPI.transfer(0x80);
  int id = SPI.transfer(0);
  digitalWrite(CS_Pin, HIGH);//Disable SPI

  Serial.println("ID: " + String(id));

  //Turn on the sensor, pg 16
  digitalWrite(CS_Pin, LOW);
  SPI.transfer(0x2D);
  SPI.transfer(0x08);
  digitalWrite(CS_Pin, HIGH);
  
  //Change measurement range, pg17
  digitalWrite(CS_Pin, LOW);//Enable SPI
  SPI.transfer(0x31);
  if (range == 2)
  {
    SPI.transfer(0x00);
  }
  else if (range == 4)
  {
    SPI.transfer(0x01);
  }
  else if (range == 8)
  {
    SPI.transfer(0x02);
  }
  else if (range == 16)
  {
    SPI.transfer(0x03);
  }
  digitalWrite(CS_Pin, HIGH);//Disable SPI
}

void loop() {
  //Read data, pg18
  digitalWrite(CS_Pin, LOW);//Enable SPI
  SPI.transfer(0xF2);//Send address of LSB of x. Set bit 6 for multi-byte reading pg15
  int x = SPI.transfer(0) | SPI.transfer(0)<<8; //x acceleration 
  int y = SPI.transfer(0) | SPI.transfer(0)<<8; //y acceleration
  int z = SPI.transfer(0) | SPI.transfer(0)<<8; //z acceleration
  digitalWrite(CS_Pin, HIGH);//Disable SPI

  float scale; //pg3
  if (range == 2)
  {
    scale = 0.0039;
  }
  else if (range == 4)
  {
    scale = 0.0078;
  }
  else if (range == 8)
  {
    scale = 0.0156;
  }
  else if (range == 16)
  {
    scale = 0.0312;
  }
  float accelX = x * scale;
  float accelY = y * scale;
  float accelZ = z * scale;
  
  Serial.print("X: "); Serial.print(accelX); Serial.print("  ");
  Serial.print("Y: "); Serial.print(accelY); Serial.print("  ");
  Serial.print("Z: "); Serial.print(accelZ); Serial.print("  ");
  Serial.println("g");

  delay(500);
}
