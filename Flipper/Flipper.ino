int pin3=3;
int pin10=10;
int pin5=5;
int i;
int j;
void setup() {
  // put your setup code here, to run once:
pinMode(pin3, OUTPUT);
pinMode(pin10, OUTPUT);
pinMode(pin5, OUTPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
for(i=0;i<=256;i++){
  analogWrite(pin3, i);
  delay(100);
  Serial.println(i);
}
for(j=255;j>=0;j--){
  analogWrite(pin10, j);
  delay(100);
  Serial.println(j);
}
delay(1000);
}
