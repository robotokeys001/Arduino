#include <HCSR04.h>
                                    
UltraSonicDistanceSensor distanceSensor(13, 12);  //TRIG  //ECHO

void setup () { 
    Serial.begin(9600);  // We initialize serial connection so that we could print values from sensor.
}

void loop () {
    int dist= distanceSensor.measureDistanceCm();
    Serial.println(distanceSensor.measureDistanceCm());
    delay(500);
}
