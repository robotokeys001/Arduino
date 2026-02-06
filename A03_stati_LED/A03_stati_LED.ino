int ledBlue= 10;
int ledYellow=6;
int ledGreen= 4;
int pin_switch=2;
int stato=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
 pinMode(ledBlue, OUTPUT);
  pinMode(ledYellow, OUTPUT);
    pinMode(ledGreen, OUTPUT);
     pinMode(pin_switch, INPUT_PULLUP);
}

void loop() {
   switch(stato){
    case 0:
      stato_0();
      break;
    case 1:
      stato_1();
      break;
    case 2:
      stato_2();
      break;
    case 3:
      stato_3();
      break;
   }
  
}


   void stato_0(){
  //Loop stato 0
    digitalWrite(ledBlue, HIGH);
    digitalWrite(ledYellow, LOW);
    digitalWrite(ledGreen, LOW);
    if(!digitalRead(pin_switch)){
      stato=1;
      delay(300);
    }
  }

    void stato_1(){
  //Loop stato 1
  digitalWrite(ledBlue, LOW);
  digitalWrite(ledYellow, HIGH);
  digitalWrite(ledGreen, LOW);
  if(!digitalRead(pin_switch)){
      stato=2;
      delay(300);
    }
  }

    void stato_2(){ 
    //Loop stato 2
    digitalWrite(ledBlue, LOW);
    digitalWrite(ledYellow, LOW);
    digitalWrite(ledGreen, HIGH);
    if(!digitalRead(pin_switch)){
      stato=3;
      delay(300);
      }
    }
      void stato_3(){ 
      //Loop stato 2
      digitalWrite(ledBlue, LOW);
      digitalWrite(ledYellow, LOW);
      digitalWrite(ledGreen, LOW);
      if(!digitalRead(pin_switch)){
        stato=0;
        delay(300);
      }
    }
    