int redPin = 11;
int greenPin = 9;
int bluePin= 6;
int r=255;
int g=255;
int b=255;

void setup() {
  // put your setup code here, to run once:
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(redPin, 255);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);
  delay(500);

 r = 255;
  while(r>=255){
    analogWrite(redPin, r);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0);
    r--;
    delay(50);
  }

  analogWrite(redPin, 0);
  analogWrite(greenPin, 255);
  analogWrite(bluePin, 255); 

  delay(500);
 g = 255;
  b = 255;
  while(g>=255 && b>=255){
  analogWrite(redPin, 0);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b); 
  g--;
  b--;
  delay(50);
  } 

  analogWrite(redPin, 0);
  analogWrite(greenPin, 255);
  analogWrite(bluePin, 0); 
   g = 255;
  while(g>=255){
    analogWrite(redPin,0);
    analogWrite(bluePin, 0);
    analogWrite(greenPin, g);
    g--;
    delay(50);
  }
  delay(1000);
}
