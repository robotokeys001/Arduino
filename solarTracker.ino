#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <ESP32Servo.h>

const char* ssid = "Pixel_8847";
const char* password = "xa53zw4yc7m6rnn";
// AGGIUNTO http://
const char* serverUrl = "http://172.16.0.164:3000/solartracker"; 

Servo mioServo;
const int servoPin = 18;

void setup() {
  Serial.begin(115200);

  //WiFi.begin(ssid, password);
  WiFi.begin("Siam-IoT-Net 2.4", "Siam1838");
  Serial.print("Connessione WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnesso!");

  ESP32PWM::allocateTimer(0);
  mioServo.setPeriodHertz(50);
  mioServo.attach(servoPin, 500, 2400);
}

void sendData(int servoPos) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    
    Serial.print("--- Tentativo invio a: ");
    Serial.println(serverUrl);

    if (http.begin(serverUrl)) { 
      http.addHeader("Content-Type", "application/json");

      StaticJsonDocument<64> doc;
      doc["valore"] = servoPos;

      String jsonStr;
      serializeJson(doc, jsonStr);
      Serial.print("Payload inviato: ");
      Serial.println(jsonStr);

      // POST e cattura del tempo di risposta
      long startTime = millis();
      int responseCode = http.POST(jsonStr);
      long duration = millis() - startTime;

      if (responseCode > 0) {
        Serial.printf("[SUCCESSO] Codice HTTP: %d | Tempo: %ldms\n", responseCode, duration);
        String responseBody = http.getString();
        Serial.println("Risposta Server: " + responseBody);
      } else {
        Serial.printf("[ERRORE] Invio fallito! Motivo: %s (Codice: %d)\n", http.errorToString(responseCode).c_str(), responseCode);
      }
      http.end();
    } else {
      Serial.println("[ERRORE] Impossibile inizializzare la connessione HTTP");
    }
  } else {
    Serial.println("[WIFI] Non connesso! Salto l'invio.");
  }
  Serial.println("------------------------------------");
}

void loop() {
  
  // Genera un numero casuale per simulare la posizione del servo
  int datoFittizio = random(0, 181); 
  
  Serial.print("Simulazione invio dato: ");
  Serial.println(datoFittizio);
  
  sendData(datoFittizio); // Usa la tua funzione sendData
  
  delay(5000); // Aspetta 5 secondi tra un invio e l'altro

 /*
  // Movimento in avanti
  for (int i = 0; i <= 180; i++) {
    mioServo.write(i);
    if (i % 30 == 0) sendData(i);
    delay(10000); 
  }

  // Movimento a ritroso
  for (int i = 180; i >= 0; i--) {
    mioServo.write(i);
    if (i % 30 == 0) sendData(i);
    delay(10000);
  }
  */
  
}