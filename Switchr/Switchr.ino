int ledBlue= 10;
int ledYellow=6;
int ledGreen= 4;
int pinSwitch= 2;
int stato_led;

  void setup() {
    
    Serial.begin(9600);
    pinMode(ledBlue, OUTPUT);
    pinMode(ledYellow, OUTPUT);
    pinMode(ledGreen, OUTPUT);
    pinMode(pinSwitch, INPUT_PULLUP);
    stato_led= LOW;
  }

  void loop() {
    
    //Quando tocco il pulsante salvo la variabile controllando se accendo(vero) o spengo(falso) il pulsante
    if(!digitalRead(pinSwitch)){
      stato_led= !stato_led;
      delay(300);
    }
    digitalWrite(ledYellow, stato_led);


    digitalWrite(ledBlue, HIGH);
    delay(300);
    digitalWrite(ledBlue, LOW);
    delay(300);

      

   
  }
