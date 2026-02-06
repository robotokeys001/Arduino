
int pin13=13;
int pin9=9;

void setup() {
  // put your setup code here, to run once:

pinMode(pin13, OUTPUT);
pinMode(pin9, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(pin13, HIGH);
digitalWrite(pin9, HIGH);
delay(1000);
digitalWrite(pin9, LOW);
delay(1000);
}
