#include <waterlevelsensor.h>

WaterLevelSensor sensor = WaterLevelSensor();

void setup() {
  Serial.begin(9600);
}

void loop() {
  //lesen des Grove Wasser Level Sensors
  int waterLevel = sensor.readPercentage();
  int waterLevelinCM = sensor.readCM();

  //Ausgeben des ermittelten Wertes
  Serial.print(waterLevel);
  Serial.println("%");
  Serial.print(waterLevelinCM);
  Serial.println(" cm");
  Serial.println("--------------------------");
  
  delay(500);
}