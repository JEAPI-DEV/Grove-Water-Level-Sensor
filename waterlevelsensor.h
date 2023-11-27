#include "Arduino.h"
#include <Wire.h>

class WaterLevelSensor {
  public:

  WaterLevelSensor();

  int readPercentage();
  double WaterLevelSensor::readCM(double maxCM = 10);
  
  private:
  
};