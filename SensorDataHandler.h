#ifndef SensorDataHandler_h
#define SensorDataHandler_h

#include <Arduino.h>


class SensorDataHandler {
public:
  SensorDataHandler(); // Constructor
  void begin(); // Initialization function
  void sensorStats(); // Function to retrieve sensor stats
  void readSensorData(); // Function to read sensor data
  
  // Getter functions for individual sensor data fields
  float getRoll() const { return roll; }
  float getPitch() const { return pitch; }
  float getHeading() const { return heading; }
  float getTemperature() const { return temperature; }

private:
  String sendCommand(String command); // Private method for sending commands

  // Individual sensor data fields
  float roll;
  float pitch;
  float heading;
  float temperature;

 
};

#endif
