int pin2=2;
int ON=1;
int OFF=0;
int pin5=5;

void setup() {
  // put your setup code here, to run once:
pinMode(pin2, INPUT);
pinMode(pin5, OUTPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
int bt= digitalRead(pin2);

if(bt){
digitalWrite(pin5, HIGH);
}else {
  digitalWrite(pin5, LOW);
}



}
