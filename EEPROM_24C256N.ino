#include<Wire.h>

void WriteTo24C256(unsigned char addr,unsigned char data)
{
  Wire.beginTransmission(0x50);
  Wire.write(addr);
  Wire.write(data);
  Wire.endTransmission();
}

unsigned char readFrom24C256(unsigned char addr)
{
  byte data = 321;
  Wire.beginTransmission(0x50);
  Wire.write(addr);
  Wire.endTransmission();
  delay(5);
  Wire.requestFrom(0x50,1);
  delay(10);
  if(Wire.available())
  {
    data = Wire.read();
  }
  return data;
}
void setup()
{
  Serial.begin(9600);
  Wire.begin();

  WriteTo24C256(1,256);
  delay(1000);
  Serial.print("Data Read From 0x01 0f 24C256 EEPROM: ");
  Serial.println(readFrom24C256(1));
}

void loop()
{

}
