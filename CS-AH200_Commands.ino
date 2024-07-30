#include "SensorDataHandler.h"

// Define software serial pins
#define RX_PIN 10
#define TX_PIN 11

SensorDataHandler::SensorDataHandler() : mySerial(RX_PIN, TX_PIN) {
  // Constructor, initialize SoftwareSerial object
}

void SensorDataHandler::begin() {
  // Initialize Serial communication for debugging
  Serial.begin(115200); // Adjust baud rate as necessary

  // Initialize SoftwareSerial for sensor communication
  mySerial.begin(9600); // Adjust baud rate to match your sensor
  delay(100); // Ensure SoftwareSerial is ready
}

void SensorDataHandler::sensorStats() {
  String firmwareVersion = sendCommand("$nV*\r");
  String serialNumber = sendCommand("$nS*\r");
  String sensorType = sendCommand("$nST*\r");

  Serial.print("Firmware Version: ");
  Serial.println(firmwareVersion);
  Serial.print("Serial Number: ");
  Serial.println(serialNumber);
  Serial.print("Sensor Type: ");
  Serial.println(sensorType);
}

void SensorDataHandler::readSensorData() {
  String sensorDataMsg = sendCommand("$CSIMU*\r");

  // Parse sensor data message
  if (sensorDataMsg.startsWith("$CSIMU")) {
    sensorDataMsg.remove(0, 6); // Remove "$CSIMU," prefix

    // Split the response into individual data fields
    int dataIndex = 0;
    while (sensorDataMsg.length() > 0 && dataIndex < 10) { // Assuming 10 fields in $CSIMU message
      int commaIndex = sensorDataMsg.indexOf(',');
      if (commaIndex != -1) {
        String fieldValue = sensorDataMsg.substring(0, commaIndex);
        float value = fieldValue.toFloat(); // Convert String to float

        // Assign values to respective fields
        switch (dataIndex) {
          case 0: accelerationX = value; break;
          case 1: accelerationY = value; break;
          case 2: accelerationZ = value; break;
          case 3: gyroX = value; break;
          case 4: gyroY = value; break;
          case 5: gyroZ = value; break;
          case 6: magX = value; break;
          case 7: magY = value; break;
          case 8: magZ = value; break;
          case 9: temperature = value; break;
          default: break; // Handle unexpected data fields if necessary
        }

        sensorDataMsg.remove(0, commaIndex + 1);
      } else {
        // Last field
        float value = sensorDataMsg.toFloat(); // Convert String to float
        switch (dataIndex) {
          case 0: accelerationX = value; break;
          case 1: accelerationY = value; break;
          case 2: accelerationZ = value; break;
          case 3: gyroX = value; break;
          case 4: gyroY = value; break;
          case 5: gyroZ = value; break;
          case 6: magX = value; break;
          case 7: magY = value; break;
          case 8: magZ = value; break;
          case 9: temperature = value; break;
          default: break; // Handle unexpected data fields if necessary
        }
        
        sensorDataMsg = ""; // Clear response
      }
      dataIndex++;
    }
  } else {
    // Handle unexpected responses or errors
    Serial.println("Unexpected response: " + sensorDataMsg);
  }
}

String SensorDataHandler::sendCommand(String command) {
  mySerial.print(command);
  delay(100); // Adjust delay as needed based on sensor response time

  if (mySerial.available()) {
    String response = mySerial.readStringUntil('\n');
    return response;
  }

  return ""; // Return empty string if no response
}
