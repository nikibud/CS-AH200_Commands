#include "arduino_secrets.h"
#include "thingProperties.h"
#include "SensorDataHandler.h"
#include <Arduino_LSM6DS3.h>

// Constants for pin definitions
const int GOOD = 3;
const int FU = 4;
const int FD = 5;
const int RU = 6;
const int RD = 7;
const int LU = 8;
const int LD = 9;

// Global variables
float pitchFilteredOld;
const float sensorRate = 104.00;
float roll, pitch, heading;
float roll_ZERO = 0;
float pitch_ZERO = 0;
float roll_MEAN = 0;
float pitch_MEAN = 0;
float yaw_MEAN = 0;
int MEAN_count = 0;

// Create an instance of SensorDataHandler
SensorDataHandler sensorHandler;

void setup() {
  Serial.begin(115200); // Start Serial communication with the PC
  
  sensorHandler.begin(); // Initialize sensor communication
  sensorHandler.sensorStats(); // Retrieve and print sensor stats
  
  // Set pin modes for outputs
  pinMode(GOOD, OUTPUT);
  pinMode(FU, OUTPUT);
  pinMode(FD, OUTPUT);
  pinMode(RU, OUTPUT);
  pinMode(RD, OUTPUT);
  pinMode(LU, OUTPUT);
  pinMode(LD, OUTPUT);
  
  // Initialize Arduino IoT Cloud properties
  initProperties();
  
  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2); // Set debug message level
  ArduinoCloud.printDebugInfo(); // Print debug information
}

void loop() {
  ArduinoCloud.update(); // Update cloud properties

  sensorHandler.readSensorData();
  pitch = sensorHandler.getPitch();
  roll = sensorHandler.getRoll();
  heading = sensorHandler.getHeading();
  delay(40);
  
  // Control output based on sensor data
  digitalWrite(GOOD, HIGH);
  digitalWrite(FU, LOW);
  digitalWrite(FD, LOW);
  digitalWrite(RD, LOW);
  digitalWrite(RU, LOW);
  digitalWrite(LD, LOW);
  digitalWrite(LU, LOW);

  if ((roll < roll_ZERO - resolution && AUTO_Roll) || FD_Override) {
    digitalWrite(FD, HIGH);
    digitalWrite(GOOD, LOW);
  }
  if ((roll > roll_ZERO + resolution && AUTO_Roll) || FU_Override) {
    digitalWrite(FU, HIGH);
    digitalWrite(GOOD, LOW);
  }
  
  if ((pitch < pitch_ZERO - resolution && AUTO_Pitch) || RD_Override) {
    digitalWrite(RD, HIGH);
    digitalWrite(GOOD, LOW);
  }
  if (RU_Override) {
    digitalWrite(RU, HIGH);
    digitalWrite(GOOD, LOW);
  }
  
  if ((pitch > pitch_ZERO + resolution && AUTO_Pitch) || LD_Override) {
    digitalWrite(LD, HIGH);
    digitalWrite(GOOD, LOW);
  }
  if (LU_Override) {
    digitalWrite(LU, HIGH);
    digitalWrite(GOOD, LOW);
  }

  // Read pin states
  GOOD_READ = digitalRead(GOOD);
  FU_READ = digitalRead(FU);
  FD_READ = digitalRead(FD);
  RU_READ = digitalRead(RU);
  RD_READ = digitalRead(RD);
  LU_READ = digitalRead(LU);
  LD_READ = digitalRead(LD);

  // Set zero points
  if (set_Roll_ZERO) {
    roll_ZERO = roll;
  }
  if (set_Pitch_ZERO) {
    pitch_ZERO = pitch;
  }
  
  // Print sensor data
  Serial.print("roll: ");
  Serial.print(roll);
  Serial.print(" pitch: ");
  Serial.print(pitch);
  Serial.print(" heading: ");
  Serial.println(heading);

  // Calculate mean values
  roll_READ = roll - roll_ZERO;
  pitch_READ = pitch - pitch_ZERO;
  yaw_READ = heading;
  
  roll_MEAN += roll_READ;
  pitch_MEAN += pitch_READ;
  yaw_MEAN += yaw_READ;
  MEAN_count++;

  if (MEAN_count > 0) {
    roll_MEAN_READ = roll_MEAN / MEAN_count;
    pitch_MEAN_READ = pitch_MEAN / MEAN_count;
    yaw_MEAN_READ = yaw_MEAN / MEAN_count;
  }

  if (MEAN_RESET) {
    roll_MEAN = 0;
    pitch_MEAN = 0;
    yaw_MEAN = 0;
    MEAN_count = 0;
  }
}



void onMEANRESETChange()  {
  // Add your code here to act upon MEANRESET change
}
/*
  Since Resolution is READ_WRITE variable, onResolutionChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onResolutionChange()  {
  // Add your code here to act upon Resolution change
}
/*
  Since AUTOPitch is READ_WRITE variable, onAUTOPitchChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onAUTOPitchChange()  {
  // Add your code here to act upon AUTOPitch change
}
/*
  Since AUTORoll is READ_WRITE variable, onAUTORollChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onAUTORollChange()  {
  // Add your code here to act upon AUTORoll change
}
/*
  Since FDOverride is READ_WRITE variable, onFDOverrideChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onFDOverrideChange()  {
  // Add your code here to act upon FDOverride change
}
/*
  Since FUOverride is READ_WRITE variable, onFUOverrideChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onFUOverrideChange()  {
  // Add your code here to act upon FUOverride change
}
/*
  Since LDOverride is READ_WRITE variable, onLDOverrideChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onLDOverrideChange()  {
  // Add your code here to act upon LDOverride change
}
/*
  Since LUOverride is READ_WRITE variable, onLUOverrideChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onLUOverrideChange()  {
  // Add your code here to act upon LUOverride change
}
/*
  Since RDOverride is READ_WRITE variable, onRDOverrideChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onRDOverrideChange()  {
  // Add your code here to act upon RDOverride change
}
/*
  Since RUOverride is READ_WRITE variable, onRUOverrideChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onRUOverrideChange()  {
  // Add your code here to act upon RUOverride change
}
/*
  Since SetPitchZERO is READ_WRITE variable, onSetPitchZEROChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onSetPitchZEROChange()  {
  // Add your code here to act upon SetPitchZERO change
}
/*
  Since SetRollZERO is READ_WRITE variable, onSetRollZEROChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onSetRollZEROChange()  {
  // Add your code here to act upon SetRollZERO change
}
