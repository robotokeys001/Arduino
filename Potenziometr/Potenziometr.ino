int redPin = 11;
int greenPin = 9;
int bluePin= 6;
int pot=A0;


void setup() {
  // put your setup code here, to run once:
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(pot, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int potVal= analogRead(pot);
  Serial.println(potVal);

  if (potVal>=1000){
    analogWrite(redPin, 255);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0);
  }
  
  else if (potVal<1000 && potVal>=500){
    analogWrite(redPin, 0);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 255);
  }

  else if(potVal<500 && potVal>=0){
    analogWrite(redPin, 0);
    analogWrite(greenPin, 255);
    analogWrite(bluePin, 0);
  }
  delay(200);
}
