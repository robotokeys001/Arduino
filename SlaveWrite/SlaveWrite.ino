// Slave Sender
#include <Wire.h>
#define address 9
#define pinStatus 8
int status = 0;
void setup() {
  Wire.begin(address);                // join i2c bus with address "address"
  Wire.onRequest(requestEvent); // register event
}

void loop() {
  delay(100);
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  status = 10 * digitalRead(pinStatus) + 10;   
  byte valLow =  lowByte(status);
  byte valHigh = highByte(status);
  // Trasmette al Master i 2 byte della variabile status
  Wire.write(valHigh);
  Wire.write(valLow);
  // as expected by master
}