#include <Servo.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "TuaRete";
const char* password = "TuaPassword";
const char* serverUrl = "http://192.168.1.100:3000/data"; // IP del PC

void sendData(int lightL, int lightR, int servoPos) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");

    // Crea il JSON
    StaticJsonDocument<100> doc;
    doc["lightL"] = lightL;
    doc["lightR"] = lightR;
    doc["servoPos"] = servoPos;

    String jsonStr;
    serializeJson(doc, jsonStr);

    int responseCode = http.POST(jsonStr);
    http.end();
  }
}

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