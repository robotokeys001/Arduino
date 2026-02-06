
//Libreria per WiFi
#include <WiFi.h>

//Interroga per ottenere i dati dalle pagine
#include <HTTPClient.h>


void setup() {
  // put your setup code here, to run once:
  pinMode(15, OUTPUT);

  Serial.begin(115200);
  delay(300);
  Serial.print("WiFi Client");

  //Attende che il router accolga la richiesta
  
  //Nome rete e password
  WiFi.begin("IoT - WIFI", "03GDVBH223");

  //Verifica lo stato della rete
  //WL_CONNECTED :Costante
  while(WiFi.status()!= WL_CONNECTED) {
    delay(1000);
     digitalWrite(15, !digitalRead(15));
    Serial.print(".");
  }

  //Quando connesso il led si spegne
  digitalWrite(15, LOW);
  Serial.println("\nConnesso");

  Serial.print("IP: "); 
  //Ottengo l'indirizzo IP
  Serial.println(WiFi.localIP());
  
  //Richiesta
  HTTPClient http;
  //http.begin("http://www.google.com");
  http.begin("https://jsonplaceholder.typicode.com/posts/1");

  //Richiedo la pagina
  int httpcode = http.GET();

  //Controllo se mi arriva qualcosa
  if (httpcode >0) {

    Serial.print("HTTP code: "); 
    Serial.println(httpcode);
    String page = http.getString();
    Serial.println(page);

  }

  http.end();
  WiFi.disconnect();
}

void loop() {
  
  //Meglio non lasciare il loop vuoto!!
  
 
  delay(500);

}
