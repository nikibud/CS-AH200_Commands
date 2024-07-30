#ifndef SensorDataHandler_h
#define SensorDataHandler_h

#include <Arduino.h>
#include <SoftwareSerial.h>

class SensorDataHandler {
public:
  SensorDataHandler(); // Constructor
  void begin(); // Initialization function
  void sensorStats(); // Function to retrieve sensor stats
  void readSensorData(); // Function to read sensor data
  
  // Getter functions for individual sensor data fields
  float getAccelerationX() const { return accelerationX; }
  float getAccelerationY() const { return accelerationY; }
  float getAccelerationZ() const { return accelerationZ; }
  float getGyroX() const { return gyroX; }
  float getGyroY() const { return gyroY; }
  float getGyroZ() const { return gyroZ; }
  float getMagX() const { return magX; }
  float getMagY() const { return magY; }
  float getMagZ() const { return magZ; }
  float getTemperature() const { return temperature; }

private:
  String sendCommand(String command); // Private method for sending commands

  // Individual sensor data fields
  float accelerationX;
  float accelerationY;
  float accelerationZ;
  float gyroX;
  float gyroY;
  float gyroZ;
  float magX;
  float magY;
  float magZ;
  float temperature;

  SoftwareSerial mySerial; // SoftwareSerial object for sensor communication
};

#endif
