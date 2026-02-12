#include <WiFi.h>
#include <WebServer.h>

const int pinR = 13;
const int pinG = 12;
const int pinB = 14;
  WebServer server(81);

  void setup() {
    
     pinMode(redLed, OUTPUT);
     pinMode(blueLed, OUTPUT);
     pinMode(greenLed, OUTPUT);

     Serial.begin(115200);
     delay(3000);
     Serial.print("Web Server ESP32");

    //Collegamento WiFi
     WiFi.begin("IoT - WIFI", "03GDVBH223");

    //Verifico la connessione
     while(WiFi.status() != WL_CONNECTED){
        Serial.print(".");
        delay(500);
     }

     //Connessione avvenuta \°o°/
     Serial.println("\nConnesso");

     Serial.println(WiFi.localIP());

     //Crea delle funzioni per le richieste server
     //A fronte di
     //Configuro i PATH
     server.on("/", handleRoot);
    server.on("/set", handleSet);
    //Avvio il server
    server.begin();

  }

  void loop() {
    //Attende le richieste dal browser
    server.handleClient();
    delay(2);

  }
 
  void handleRoot() {
  String html = "<html><head><title>ESP32 RGB Control</title>";
  html += "<style>body{font-family:sans-serif; text-align:center; padding:50px;} input{margin:10px;}</style></head><body>";
  html += "<h1>Controllo LED RGB</h1>";
  html += "<form action='/set' method='GET'>"; // La form invia i dati alla rotta /set
  html += "Rosso (0-255): <input type='number' name='r' min='0' max='255' value='0'><br>";
  html += "Verde (0-255): <input type='number' name='g' min='0' max='255' value='0'><br>";
  html += "Blu   (0-255): <input type='number' name='b' min='0' max='255' value='0'><br>";
  html += "<input type='submit' value='Aggiorna Colore'>";
  html += "</form></body></html>";
  
  server.send(200, "text/html", html);
}
// Funzione per gestire l'aggiornamento del colore
void handleSet() {
  if (server.hasArg("r") && server.hasArg("g") && server.hasArg("b")) {
    int r = server.arg("r").toInt();
    int g = server.arg("g").toInt();
    int b = server.arg("b").toInt();

    analogWrite(pinR, r);
    analogWrite(pinG, g);
    analogWrite(pinB, b);
  }
  
  // Dopo aver aggiornato il LED, torna alla pagina principale
  server.sendHeader("Location", "/");
  server.send(303);
}
 
