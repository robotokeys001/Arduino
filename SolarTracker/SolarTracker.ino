#include <Servo.h>

const int servoPin = 9;
Servo myServo;
int servov = 20;
const int servovLimitHigh = 160;
const int servovLimitLow = 20;

const int lightPinL = A0;
const int lightPinR = A1;
const int threshold = 10; // tolleranza per evitare micro-oscillazioni

void setup() {
  myServo.attach(servoPin);
  myServo.write(servov);
  Serial.begin(9600);
  delay(500);
}

void loop() {
  int lightValL = analogRead(lightPinL);
  int lightValR = analogRead(lightPinR);
  int diff = lightValL - lightValR;

  Serial.print("L: "); Serial.print(lightValL);
  Serial.print(" R: "); Serial.print(lightValR);
  Serial.print(" Servo: "); Serial.println(servov);

  if (diff > threshold) {          // più luce a sinistra → ruota a sinistra
    if (servov > servovLimitLow) {
      servov--;
      myServo.write(servov);
    }
  } else if (diff < -threshold) {  // più luce a destra → ruota a destra
    if (servov < servovLimitHigh) {
      servov++;
      myServo.write(servov);
    }
  }
  // se diff è dentro la tolleranza → fermo

  delay(15);
}