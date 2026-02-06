#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const int switchPin = 2;
int counter = 0;
//Valore precedente del pulsante
int pv_bt;

    void setup() {
      // put your setup code here, to run once:
    Serial.begin(9600);  
    pinMode(switchPin, INPUT_PULLUP);
    Serial.println("Conta Pezzi");
    }

    void loop() {

      int bt = !digitalRead(switchPin);
      // put your main code here, to run repeatedly:
      if (bt && !pv_bt){
        counter++;
        Serial.println(counter);
      }
      //Fronte di salita o di discesa
      pv_bt = bt;

    }
