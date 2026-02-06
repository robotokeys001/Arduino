/*
  Plottaggio tensione di carica del condensatore

                  interruttore di carica
  +5V ---/\/\/\--/  -------------A0
             R1      |      |
                   =====    |
                 C   |      /  interruttore di scarica
                     |      |
                     |      /
                     |      \ R2
                     |      /
                     |      \
                    GND    GND

      R1 = 1.5 k  C = 47 uF  Tao = 0.07
      R2 =  120 k C = 47 uF  Tao = R*C = 5.6 s
 Il tempo si misura da quando si chiude l'interr. di scarica 
 fino a quando la curva si incrocia con 0.632*1023 
*/
float a = 0;  // Tensione ai capi del condensatore
float b = 5.0;  
float c = 0.0;
float d = 0.632*5.0;

void setup() {
  Serial.begin(9600);

}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  a = float(sensorValue)*5.0/1023.0;
  // print out the value you read:
  Serial.print("Condensatore:");
  Serial.print(a);
  Serial.print(",");
  Serial.print("5V:");
  Serial.print(b);
  Serial.print(",");
  Serial.print("0:");
  Serial.print(c);
  Serial.print(",");
  Serial.print("dopoTao:");
  Serial.print(d);
  Serial.println();
  delay(20);        // delay in between reads for stability
}
