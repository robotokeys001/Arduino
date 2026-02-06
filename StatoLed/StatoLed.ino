int ledBlue=10;
int ledYellow=6;
int pin_switch=2;
int stato=0;
//long senza segno
unsigned long t1;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledBlue, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(pin_switch, INPUT_PULLUP);

  //scrivo le "ore" di inizio
  t1= millis();
}


void loop() {
  if(!digitalRead(pin_switch)){
      stato= !stato;
      delay(300);
    }
    digitalWrite(ledYellow, stato);

  if((millis() - t1) >= 1000){
    digitalWrite(ledBlue, !digitalRead(ledBlue));
    t1 = millis();
  }

 

}
