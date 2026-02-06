int ledBlue=10;
int pin_switch=2;
int stato=0;
unsigned long t1;


void setup() {
  // put your setup code here, to run once:
  pinMode(ledBlue, OUTPUT);
  pinMode(pin_switch, INPUT_PULLUP);
  t1 = millis();
}

void loop() {
  switch(stato){
    //Accesa a meta
    case 0:
      stato_0();
      break;
    case 1:
    //Accesa Piena
      stato_1();
      break;
    case 2:
    //Lampeggia
      stato_2();
      break;
      //Ricomincia
    case 3:
      stato_3();
      break;
   }
}

void stato_0(){
  analogWrite(ledBlue, 127);
  if(!digitalRead(pin_switch)){
      stato=1;
      delay(300);
    }
}
void stato_1(){
  analogWrite(ledBlue, 255);
  if(!digitalRead(pin_switch)){
      stato=2;
      delay(300);
    }
}

void stato_2(){
   if((millis() - t1) >= 1000){
    digitalWrite(ledBlue, !digitalRead(ledBlue));
    t1 = millis();
  }
  if(!digitalRead(pin_switch)){
    stato=3;
    delay(300);
  }
}
void stato_3(){
  digitalWrite(ledBlue, LOW);
  if(!digitalRead(pin_switch)){
    stato=0;
    delay(300);
  }

}