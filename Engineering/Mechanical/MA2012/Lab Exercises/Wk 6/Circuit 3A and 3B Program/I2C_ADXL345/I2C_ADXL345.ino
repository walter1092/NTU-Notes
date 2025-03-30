#include <Wire.h>
int accelAddress = 0x1D;

int range = 8; //measurement range, can be 2g, 4g, 8g, 16g

void setup()
{
  Serial.begin(9600);

  Wire.begin();        // join i2c bus (address optional for master)

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

void loop()
{
  //Read data, pg 18
  Wire.beginTransmission(accelAddress);
  Wire.write(0x32);//Send address of LSB of x. Address is auto-increased after each reading.
  Wire.endTransmission(false);
  Wire.requestFrom(accelAddress, 6, true);
  int x = Wire.read() | Wire.read() << 8; //x acceleration
  int y = Wire.read() | Wire.read() << 8; //y acceleration
  int z = Wire.read() | Wire.read() << 8; //z acceleration

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
