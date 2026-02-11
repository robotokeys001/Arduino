#include <WiFi.h>
#include <WebServer.h>

  WebServer server(80);

  void setup() {
    
     pinMode(15, OUTPUT);

     Serial.begin(115200);
     delay(3000);
     Serial.print("Web Server ESP32");

    //Collegamento WiFi
     WiFi.begin("Pixel_8847", "xa53zw4yc7m6rnn");

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
     server.on("/", pageIndex);
     server.on("/home", pageHome);
     server.on("/ledon", ledOn);
     server.on("/ledoff", ledOff);
     server.on("/readsensor", readSensor);
     server.on("/saluta", saluta);
    //Gestione degli errori
     server.onNotFound(pageError);
    //Avvio il server
    server.begin();

  }

  void loop() {
    //Attende le richieste dal browser
    server.handleClient();
    delay(2);

  }
  //Viene evocata in base all'indirizzo dato 
  void pageIndex(){
    String str = "Hello!";
    //200 Codice di risposta dell'http
    //Manda una risposta positiva
    server.send(200, "text/plain", str);
  }

  void pageHome(){
    String str = "<html><body><h1>Hello World!</h1></body></html>";
    server.send(200, "text/html", str);
  }

  void pageError(){
    //Gestisco potenziali errori dando la possibilità di ritornare alla home
    String str = "<html><body><h1>Not Found!</h1><a href='/'>HOME</a></body></html>";
    server.send(200, "text/html", str);
  }

  void ledOn(){
    digitalWrite(15, HIGH);
     //Aggiungo un link che accende il led
    String str = "<html><body><a href='/ledoff'>OFF</a></body></html>";
    server.send(200, "text/html", str);
  }

  void ledOff(){
    digitalWrite(15, LOW);
    //Aggiungo un link che spegne il led
    String str = "<html><body><a href='/ledon'>ON</a></body></html>";
    server.send(200, "text/html", str);
  }

  void readSensor(){
    int val = analogRead(3);
    //Faccio ricaricare la pagina ogni 5 secondi
    //In questo modo la mia pagina aggiornera i dati del sensore ogni 5 secondi
    String str= "<html><head><meta http-equiv='refresh' content='5'</head><body>Sensor: "+String(val)+"</body></html>";
    server.send(200, "text/html", str);
  }

  void saluta(){
    //Controllo se c'è l'argomento
    String nome="";
    if (server.hasArg("nome")){
      nome= server.arg("nome");
    }
    //Una volta inviato verrà preso da "nome"
    String str = "<html><body>Ciao..." + nome +"</body></html>";
    server.send(200, "text/html", str);
  }
