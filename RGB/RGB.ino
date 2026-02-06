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
  randomSeed(analogRead(0));
}

void loop() {
  // put your main code here, to run repeatedly:
  int potVal=analogRead(pot);

  int r=random(0,256);
  int g=random(0,256);
  int b=random(0,256);

  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
  delay(500);
}
