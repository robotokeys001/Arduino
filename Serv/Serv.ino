#include <Servo.h>

Servo myServo;
int potVal = A0;

void setup() {
  // put your setup code here, to run once:
myServo.attach(9);

}

void loop() {
  // put your main code here, to run repeatedly:
  int val = analogRead(potVal);
  int pos = map(val, 0, 1023, 0, 180);
  myServo.write(pos);
  delay(10);

}
