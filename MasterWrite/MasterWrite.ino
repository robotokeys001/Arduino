// Arduino Master Writer

#include <Wire.h>
#define pinStatus 8
#define address 9
word status = 0;
byte highB = 0;
byte lowB = 0;

void setup(){
  Wire.begin(); // join i2c bus (address optional for master)
  Serial.begin(9600);
}

void loop(){
  status = 10 * digitalRead(pinStatus) + 10;
  Wire.beginTransmission(address); // transmit to device #4
  byte valLow =  lowByte(status);
  byte valHigh = highByte(status);
  // Trasmette allo  Slave i 2 byte della variabile status
  Wire.write(valHigh);
  Wire.write(valLow);
  // as expected by master
  Wire.endTransmission();    // stop transmitting
  delay(500);
}
