int ledBlue=10;
int ledYellow=6;
int pin_switch=2;
int stato=0;
//long senza segno
unsigned long t1;
unsigned long t2;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledBlue, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(pin_switch, INPUT_PULLUP);

  //scrivo le "ore" di inizio
  t1= millis();
  t2= millis();
}


void loop() {
  

  if((millis() - t2) >= 1000){
    digitalWrite(ledBlue, !digitalRead(ledBlue));
    t2 = millis();
  }

  if((millis() - t1) >= 2000){
    digitalWrite(ledYellow, !digitalRead(ledYellow));
    t1 = millis();
  }

 

}
