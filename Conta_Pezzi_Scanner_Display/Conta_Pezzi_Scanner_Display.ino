#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3c

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

  

const int switchPin = 2;
int counter = 0;
//Valore precedente del pulsante
int pv_bt;

    void setup() {
      // put your setup code here, to run once:
    Serial.begin(9600);  
    pinMode(switchPin, INPUT_PULLUP);
    Serial.println("Conta Pezzi");
    display.clearDisplay();
    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
      }
    }

    void loop() {

      int bt = !digitalRead(switchPin);
      // put your main code here, to run repeatedly:

      //Fronte di salita
      if (bt && !pv_bt){
        counter++;
        Serial.println(counter);
        display.setTextSize(1); // Draw 2X-scale text
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(0, 0);
        display.print(counter);
        display.display();
      }
      //Fronte di salita o di discesa
      pv_bt = bt;

    }
