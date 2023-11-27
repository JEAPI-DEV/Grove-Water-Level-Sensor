#include "waterlevelsensor.h"
#include "Arduino.h"
#include <Wire.h>

// Define I2C addresses
#define ATTINY1_HIGH_ADDR 0x78
#define ATTINY2_LOW_ADDR 0x77

// Define touch sensor threshold and special value for no touch
#define THRESHOLD 100
#define NO_TOUCH 0xFE

// Initialize arrays for data from different sections
unsigned char lowData[8] = {0};
unsigned char highData[12] = {0};

// Constructor for WaterLevelSensor class
WaterLevelSensor::WaterLevelSensor(){
  Wire.begin();
}

// Function to read water level percentage
int WaterLevelSensor::readPercentage(){
  // Define sensor value range for touch detection
  int sensorValueMin = 250;
  int sensorValueMax = 255;
  
  // Variables to count the number of touches in low and high sections
  int lowCount = 0;
  int highCount = 0;

  // Variable to store combined touch values
  uint32_t touchValue = 0;

  // Variable to store the triggered section
  uint8_t triggeredSection = 0;

  // Initialize arrays to zeros
  memset(lowData, 0, sizeof(lowData));

  // Request data from the low address section
  Wire.requestFrom(ATTINY2_LOW_ADDR, 8);
  while (8 != Wire.available());
  for (int i = 0; i < 8; i++) { lowData[i] = Wire.read(); }

  // Initialize arrays to zeros
  memset(highData, 0, sizeof(highData));

  // Request data from the high address section
  Wire.requestFrom(ATTINY1_HIGH_ADDR, 12);
  while (12 != Wire.available());
  for (int i = 0; i < 12; i++) { highData[i] = Wire.read(); }

  // Check for touches in the low section
  for (int i = 0; i < 8; i++){
    if (lowData[i] >= sensorValueMin && lowData[i] <= sensorValueMax){
      lowCount++;
    }
  }

  // Check for touches in the high section
  for (int i = 0; i < 12; i++){
    if (highData[i] >= sensorValueMin && highData[i] <= sensorValueMax){
      highCount++;
    }
  }

  // Combine low and high data into a single value for touch sensitivity
  for (int i = 0 ; i < 8; i++) {
    if (lowData[i] > THRESHOLD) {
      touchValue |= 1 << i;
    }
  }

  for (int i = 0 ; i < 12; i++) {
    if (highData[i] > THRESHOLD) {
      touchValue |= (uint32_t)1 << (8 + i);
    }
  }

  // Determine the triggered section based on touch values
  while (touchValue & 0x01){
    triggeredSection++;
    touchValue >>= 1;
  }

  // Return the water level percentage for the triggered section
  return triggeredSection * 5;
}

// read in cm input use readPercentage() function
double WaterLevelSensor::readCM(double maxCM = 10){
    int percentage = readPercentage();
    return (percentage * maxCM) / 100;
}