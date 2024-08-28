#include "SensorDataHandler.h"


// Define software serial pins
#define RX_PIN 0
#define TX_PIN 1
//SoftwareSerial mySerial(RX_PIN, TX_PIN);

SensorDataHandler::SensorDataHandler()   {
  // Constructor, initialize SoftwareSerial object
}

void SensorDataHandler::begin() {
  // Initialize Serial communication for debugging
  Serial.begin(115200); // Adjust baud rate as necessary

  // Initialize SoftwareSerial for sensor communication
  Serial1.begin(115200); // Adjust baud rate to match your sensor
  delay(100); // Ensure SoftwareSerial is ready
  String respondDataRate = sendCommand("$1D0025*\r"); // set the data rate to 25 hz
  String respondEuler = sendCommand("$1AES*/r"); // set the unit to work with Euler
  Serial.println(respondDataRate);
}

void SensorDataHandler::sensorStats() {
  String firmwareVersion = sendCommand("$1V*\r");
  String serialNumber = sendCommand("$1S*\r");
  String sensorType = sendCommand("$1ST*\r");

  Serial.print("Firmware Version: ");
  Serial.println(firmwareVersion);
  Serial.print("Serial Number: ");
  Serial.println(serialNumber);
  Serial.print("Sensor Type: ");
  Serial.println(sensorType);
}



void SensorDataHandler::readSensorData() {
  String sensorDataMsg = sendCommand("$CSPRA*\r");
  // Parse sensor data message
  int startMsg= sensorDataMsg.lastIndexOf('$');
  sensorDataMsg.remove(0, startMsg);
  Serial.println("real massage recived: " + sensorDataMsg);
  
  if (sensorDataMsg.startsWith("$CSRPY")) {
    // Split the response into individual data fields
    int dataIndex = -1;
    while (sensorDataMsg.length() > 0 && dataIndex < 5) { // Assuming 10 fields in $CSRPY message
      int commaIndex = sensorDataMsg.indexOf(',');
      if (commaIndex != -1) {
        String fieldValue = sensorDataMsg.substring(0, commaIndex);
        float value = fieldValue.toFloat(); // Convert String to float

        // Assign values to respective fields
        switch (dataIndex) {
          case 0: roll = value; break;
          case 1: pitch = value; break;
          case 2: heading = value; break;
          default: break; // Handle unexpected data fields if necessary
        }

        sensorDataMsg.remove(0, commaIndex + 1);
      } else {
        // Last field
        float value = sensorDataMsg.toFloat(); // Convert String to float
        temperature = value;
        sensorDataMsg = ""; // Clear response
      }
      dataIndex++;
    }
  } else {
    // Handle unexpected responses or errors
    Serial.println("Unexpected response: " + sensorDataMsg);
    sensorDataMsg="";
  }
}

String SensorDataHandler::sendCommand(String command) {
  Serial1.print(command);
  delay(200); // Adjust delay as needed based on sensor response time

  if(Serial1.available()) {
    String response = Serial1.readStringUntil('\n');
    return response;
  }

  return ""; // Return empty string if no response
}
