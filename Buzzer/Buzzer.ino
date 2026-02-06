void setup() {
  // put your setup code here, to run once:
  tone(6, 440, 500);
  delay(500);
  tone(6, 523, 500);
  delay(500);
  tone(6, 523, 500);

}

void loop() {
  // put your main code here, to run repeatedly:
int f = random(100, 800);
int d = 400;
tone(6, f, d);
delay(d*1.1);
}
