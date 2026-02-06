#include <OneButton.h>

#define BUTTON_PIN 2

  OneButton btn = OneButton(
    BUTTON_PIN,  // Input pin for the button
    true,        // Button is active LOW
    true         // Enable internal pull-up resistor
  );


  void setup() {
    // put your setup code here, to run once:
      Serial.begin(9600);  
      Serial.println("Test OneButton");
      
      btn.attachClick(hello);
      btn.attachDoubleClick(hello2);

  }

  void loop() {
    btn.tick();
  }

  static void hello() {
    Serial.println("CLICK");
  }
  static void hello2() {
    Serial.println("Doppio CLICK");
  }