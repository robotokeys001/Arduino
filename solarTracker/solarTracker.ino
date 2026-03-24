#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <ESP32Servo.h> // Libreria specifica per ESP32

// Credenziali WiFi
const char* ssid = "TuaRete";
const char* password = "TuaPassword";
const char* serverUrl = "http://192.168.1.X:3000/solarTracker"; // Usa l'IP reale del PC, non 127.0.0.1

// Configurazione Servo
Servo mioServo;
const int servoPin = 18; // Pin consigliato per ESP32
int posizione = 0;

void setup() {
  Serial.begin(115200); // ESP32 usa solitamente 115200

  // Connessione WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connessione in corso");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnesso!");

  // Configurazione Servo
  ESP32PWM::allocateTimer(0); // Necessario per ESP32Servo
  mioServo.setPeriodHertz(50); // Standard 50hz
  mioServo.attach(servoPin, 500, 2400); // Attach con range impulsi tipico
}

void sendData(int servoPos) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");

    StaticJsonDocument<100> doc;
    doc["servoPos"] = servoPos;

    String jsonStr;
    serializeJson(doc, jsonStr);

    int responseCode = http.POST(jsonStr);
    
    // Utile per debug
    if (responseCode > 0) {
      Serial.printf("Dati inviati, risposta: %d\n", responseCode);
    } else {
      Serial.printf("Errore nell'invio: %s\n", http.errorToString(responseCode).c_str());
    }
    
    http.end();
  }
}

void loop() {
  // Rotazione da 0 a 180
  for (posizione = 0; posizione <= 180; posizione += 1) {
    mioServo.write(posizione);
    if (posizione % 30 == 0) sendData(posizione); // Invia dati ogni 30 gradi per non intasare il server
    delay(20);
  }

  // Rotazione da 180 a 0
  for (posizione = 180; posizione >= 0; posizione -= 1) {
    mioServo.write(posizione);
    if (posizione % 30 == 0) sendData(posizione);
    delay(20);
  }
}