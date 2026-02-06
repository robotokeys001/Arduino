
//Libreria per WiFi
#include <WiFi.h>



void setup() {
  // put your setup code here, to run once:
  pinMode(15, OUTPUT);
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
  
}

void loop() {
  
  //Meglio non lasciare il loop vuoto!!
  if(WiFi.status() != WL_CONNECTED) {

    //Se la scheda si scollega, cerco di ricollegarmi
    WiFi.disconnect();
    delay(1000);
    WiFi.reconnect();
  }

  digitalWrite(15, !digitalRead(15));
  delay(500);

}
