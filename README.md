💾 Arduino with 24C256 I²C EEPROM
📘 Overview

This project demonstrates how to use an Arduino UNO to read and write data to an AT24C256 EEPROM over the I²C (Inter-Integrated Circuit) bus.
EEPROMs like the 24C256 are used for storing data that must persist even when power is turned off — such as configuration settings, calibration values, or sensor logs.

🧩 Components Required

Arduino UNO

AT24C256 EEPROM IC

Breadboard and jumper wires

⚙️ Pin Connections
AT24C256 Pin	Function	Arduino UNO Pin
VCC	Power Supply	5V
GND	Ground	GND
SDA	Serial Data	A4
SCL	Serial Clock	A5
WP	Write Protect	GND (to enable write)
A0, A1, A2	Address Pins	GND (default I²C address = 0x50)

The 24C256 communicates using I²C, meaning it needs only two wires (SDA, SCL) plus power and ground.

💻 Arduino Code
```c
#include <Wire.h>

void WriteTo24C256(unsigned char addr, unsigned char data)
{
  Wire.beginTransmission(0x50); // Device I2C Address (A0,A1,A2 = GND)
  Wire.write(addr);             // Memory address (8-bit low byte)
  Wire.write(data);             // Data to write
  Wire.endTransmission();       // Stop condition
}

unsigned char readFrom24C256(unsigned char addr)
{
  byte data = 0x00;
  Wire.beginTransmission(0x50);
  Wire.write(addr);
  Wire.endTransmission();
  delay(5);                     // Small delay for EEPROM response
  Wire.requestFrom(0x50, 1);    // Request one byte
  delay(10);
  if (Wire.available())
  {
    data = Wire.read();
  }
  return data;
}

void setup()
{
  Serial.begin(9600);
  Wire.begin();

  WriteTo24C256(1, 0xAB);  // Write example data (0xAB) to address 1
  delay(100);
  Serial.print("Data read from address 0x01: ");
  Serial.println(readFrom24C256(1), HEX);
}

void loop()
{
}
```
🧠 Explanation

Wire.begin() initializes Arduino’s I²C communication.

Wire.beginTransmission(0x50) starts data transmission with the EEPROM at address 0x50.

The 24C256 requires a memory address followed by the data byte to be written.

Reading requires sending the memory address first, then a separate read request.

⚠️ Important Notes

The original version of your code used invalid data values:

Wire.write(addr); → for 24C256 (which has 16-bit memory addressing), you should send two bytes (high and low).

WriteTo24C256(1,256); → 256 exceeds an 8-bit value (max 255). Use something like 0xAB.

Use delay(5–10 ms) after each write operation — EEPROMs need time to store data physically.

Make sure WP (Write Protect) pin is grounded; otherwise, writes won’t work.

📊 Expected Serial Output
Data read from address 0x01: AB


This means data 0xAB was successfully written and read back.

🚀 Future Enhancements

Use 16-bit addressing to access the entire 32KB EEPROM.

Implement page writes to write multiple bytes efficiently.

Create a small EEPROM memory viewer via Serial Monitor.

Store sensor readings or configuration data permanently.
