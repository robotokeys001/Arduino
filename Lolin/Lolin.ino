
//Libreria per WiFi
#include <WiFi.h>



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(300);
  Serial.print("WiFi Connect");

  //Attende che il router accolga la richiesta
  
  //Nome rete e password
  WiFi.begin("IoT - WIFI", "03GDVBH223");

  //Verifica lo stato della rete
  //WL_CONNECTED :Costante
  while(WiFi.status()!= WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nConnesso");

  Serial.print("IP: "); 
  //Ottengo l'indirizzo IP
  Serial.println(WiFi.localIP());
  delay(5000);
  //Mi scollego
  WiFi.disconnect();
  Serial.println("Disconnesso!!");
}

void loop() {
  
  //Meglio non lasciare il loop vuoto!!

  delay(100);
}
