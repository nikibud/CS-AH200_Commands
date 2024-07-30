#include <Arduino.h>
#include "SensorDataHandler.h"

// Create an instance of SensorDataHandler
SensorDataHandler sensorHandler;

void setup() {
  Serial.begin(115200); // Start Serial communication with the PC
  sensorHandler.begin(); // Initialize sensor communication
}

void loop() {
  // Example: Retrieve and print sensor stats
  sensorHandler.sensorStats();
  
  // Example: Read sensor data and print individual fields
  sensorHandler.readSensorData();
  Serial.println("Sensor Data:");
  Serial.print("Acceleration X: "); Serial.println(sensorHandler.getAccelerationX());
  Serial.print("Acceleration Y: "); Serial.println(sensorHandler.getAccelerationY());
  Serial.print("Acceleration Z: "); Serial.println(sensorHandler.getAccelerationZ());
  Serial.print("Gyro X: "); Serial.println(sensorHandler.getGyroX());
  Serial.print("Gyro Y: "); Serial.println(sensorHandler.getGyroY());
  Serial.print("Gyro Z: "); Serial.println(sensorHandler.getGyroZ());
  Serial.print("Mag X: "); Serial.println(sensorHandler.getMagX());
  Serial.print("Mag Y: "); Serial.println(sensorHandler.getMagY());
  Serial.print("Mag Z: "); Serial.println(sensorHandler.getMagZ());
  Serial.print("Temperature: "); Serial.println(sensorHandler.getTemperature());

  delay(5000); // Delay between sensor data retrievals
}
