// Arduino Master Reader

#include <Wire.h>
#define pinLED 5
#define address 9
word status = 0;
byte highB = 0;
byte lowB = 0;

void setup() {
  pinMode(pinLED,OUTPUT);
  digitalWrite(pinLED,LOW);
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
}

void loop() {
  Wire.requestFrom(address, 2);    // request 2 bytes from peripheral device address

// peripheral may send less than requested
      while(Wire.available() > 0) {
         highB = Wire.read();
         lowB = Wire.read();
      }
      status = word(highB,lowB); 
      Serial.print(" Status = ");Serial.print(status);         // print the character
      Serial.print("\n");
      if(status == 20){
         digitalWrite(pinLED,HIGH);
      }else if(status == 10){
         digitalWrite(pinLED,LOW);
      }
  delay(500);
}
