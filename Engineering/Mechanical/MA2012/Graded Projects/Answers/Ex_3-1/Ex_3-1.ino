#include <SPI.h>
#include <Wire.h>

//SPI
const int CS_Pin = 10;// set pin 10 as the chip select
SPISettings settingsA(2000000, MSBFIRST, SPI_MODE3); // set up the speed, data order and data mode

//I2C
unsigned char accelAddress = 0x1D;

const int range = 8; //measurement range, can be 2g, 4g, 8g, 16g
float scale; //pg3
bool spii2c = 0; //0 = spi, 1 = i2c

const int ledPin = 3; //use external LED instead of on-board LED because it interferes with SPI

float FindTiltDegree(float x, float y, float z)
{
  if (z > 1) //when measurement is inaccurate such that the z > 1
  {
    return 0;
  }
  else
  {
    //Check which side it tilts to
    int sign = 0;
    if (abs(x) > abs(y)) //tilts more towards x
    {
      if (x > 0)
      {
        sign = 1;
      }
      else
      {
        sign = -1;
      }
    }
    else //tilts more towards y
    {
      if (y > 0)
      {
        sign = 1;
      }
      else
      {
        sign = -1;
      }
    }
    float tiltRadian = acos(z);
    float tiltDegree = tiltRadian * 180.0 / 3.14159;
    return tiltDegree * sign;
  }
}

void setup()
{
  Serial.begin(9600);

  if (spii2c == 0) //spi
  {
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
  else //i2c
  {
    Wire.begin();

    //Turn on the sensor, pg 16
    Wire.beginTransmission(accelAddress);
    Wire.write(0x2D);
    Wire.write(0x08);
    Wire.endTransmission();

    //Change measurement range, pg17
    Wire.beginTransmission(accelAddress);
    Wire.write(0x31);
    if (range == 2)
    {
      Wire.write(0x00);
    }
    else if (range == 4)
    {
      Wire.write(0x01);
    }
    else if (range == 8)
    {
      Wire.write(0x02);
    }
    else if (range == 16)
    {
      Wire.write(0x03);
    }
    Wire.endTransmission();
  }

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

  pinMode(ledPin, OUTPUT);
}

void loop()
{
  //Read data, pg18
  //***You may need to do the calibration (e.g. offset) yourself
  // In this code, it is assumed that the data stored is the actual acceleration
  float acc[3]; //xyz
  if (spii2c == 0) //spi
  {
    digitalWrite(CS_Pin, LOW);//Enable SPI
    SPI.transfer(0xF2);//Send address of LSB of x. Set bit 6 for multi-byte reading pg15
    int x = SPI.transfer(0) | SPI.transfer(0) << 8; //x acceleration
    int y = SPI.transfer(0) | SPI.transfer(0) << 8; //y acceleration
    int z = SPI.transfer(0) | SPI.transfer(0) << 8; //z acceleration
    digitalWrite(CS_Pin, HIGH);//Disable SPI

    acc[0] = x * scale;
    acc[1] = y * scale;
    acc[2] = z * scale;
  }
  else //i2c
  {
    Wire.beginTransmission(accelAddress);
    Wire.write(0x32);//Send address of LSB of x. Address is auto-increased after each reading.
    Wire.endTransmission(false);
    Wire.requestFrom(accelAddress, 6, true);
    int x = Wire.read() | Wire.read() << 8; //x acceleration
    int y = Wire.read() | Wire.read() << 8; //y acceleration
    int z = Wire.read() | Wire.read() << 8; //z acceleration

    acc[0] = x * scale;
    acc[1] = y * scale;
    acc[2] = z * scale;
  }

  static bool ledState = 0;
  float tilt = FindTiltDegree(acc[0], acc[1], acc[2]);

  if (abs(tilt) > 10)
  {
    ledState = 0;
    float roundedTilt = round(tilt * 2) * 0.5; //round to nearest 0.5
    Serial.println(String(roundedTilt) + " degrees");
  }
  else
  {
    ledState = !ledState; //toggle for blinking
    Serial.println("0 degree");
  }
  
  digitalWrite(ledPin, ledState);
  delay(300);
}
