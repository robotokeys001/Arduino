//  Arduino Slave Reader
// Include the required Wire library for I2C
#include <Wire.h>
#define pinLED 5
#define address 9
word status = 0;
byte highB = 0;
byte lowB = 0;

void setup() {
  // Define the LED pin as Output
  Serial.begin(9600);
   pinMode (pinLED, OUTPUT);
   digitalWrite(pinLED,LOW);
  // Start the I2C Bus as Slave on address 9
  Wire.begin(9);   
  // Attach a function to trigger when something is received.
  Wire.onReceive(requestEvent);
}

void   requestEvent() {
       while(Wire.available() > 0) {
         highB = Wire.read();
         lowB = Wire.read();
      }
      status = word(highB,lowB); 
      Serial.print(" Status = ");
      Serial.print(status);         // print the character
      Serial.print("\n");
      if(status == 20){
         digitalWrite(pinLED,HIGH);
      }else if(status == 10){
         digitalWrite(pinLED,LOW);
      }
 }
void loop() {
 
}
