const int switchPin = 2;
int counter = 0;
int pv_bt;
unsigned long t1, t2;

  void setup() {
    // put your setup code here, to run once:
  Serial.begin(9600);  
      pinMode(switchPin, INPUT_PULLUP);
      Serial.println("Conta Pezzi");
      
  }

  void loop() {
    int bt = !digitalRead(switchPin);

    //Fronte di salita
    if (bt && !pv_bt){
        counter++;
        Serial.println("FDS");
        t1= millis();
        }

    //Fronte di discesa
    if (!bt && pv_bt){
        counter++;
        Serial.println("FDD");
        t2 = millis();
        Serial.print("t:");
        Serial.println(t2-t1);
        }

      pv_bt = bt;
  }
