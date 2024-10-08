// Code generated by Arduino IoT Cloud, DO NOT EDIT.

#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

const char SSID[]     = SECRET_SSID;    // Network SSID (name)
const char PASS[]     = SECRET_OPTIONAL_PASS;    // Network password (use for WPA, or use as key for WEP)

void onResolutionChange();
void onAUTOPitchChange();
void onAUTORollChange();
void onFDOverrideChange();
void onFUOverrideChange();
void onLDOverrideChange();
void onLUOverrideChange();
void onMEANRESETChange();
void onRDOverrideChange();
void onRUOverrideChange();
void onSetPitchZEROChange();
void onSetRollZEROChange();

float pitch_MEAN_READ;
float pitch_READ;
float resolution;
float roll_MEAN_READ;
float roll_READ;
float yaw_MEAN_READ;
float yaw_READ;
bool AUTO_Pitch;
bool AUTO_Roll;
bool FD_Override;
bool FD_READ;
bool FU_Override;
bool FU_READ;
bool GOOD_READ;
bool LD_Override;
bool LD_READ;
bool LU_Override;
bool LU_READ;
bool MEAN_RESET;
bool RD_Override;
bool RD_READ;
bool RU_Override;
bool RU_READ;
bool set_Pitch_ZERO;
bool set_Roll_ZERO;

void initProperties(){

  ArduinoCloud.addProperty(pitch_MEAN_READ, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(pitch_READ, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(resolution, READWRITE, ON_CHANGE, onResolutionChange);
  ArduinoCloud.addProperty(roll_MEAN_READ, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(roll_READ, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(yaw_MEAN_READ, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(yaw_READ, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(AUTO_Pitch, READWRITE, ON_CHANGE, onAUTOPitchChange);
  ArduinoCloud.addProperty(AUTO_Roll, READWRITE, ON_CHANGE, onAUTORollChange);
  ArduinoCloud.addProperty(FD_Override, READWRITE, ON_CHANGE, onFDOverrideChange);
  ArduinoCloud.addProperty(FD_READ, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(FU_Override, READWRITE, ON_CHANGE, onFUOverrideChange);
  ArduinoCloud.addProperty(FU_READ, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(GOOD_READ, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(LD_Override, READWRITE, ON_CHANGE, onLDOverrideChange);
  ArduinoCloud.addProperty(LD_READ, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(LU_Override, READWRITE, ON_CHANGE, onLUOverrideChange);
  ArduinoCloud.addProperty(LU_READ, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(MEAN_RESET, READWRITE, ON_CHANGE, onMEANRESETChange);
  ArduinoCloud.addProperty(RD_Override, READWRITE, ON_CHANGE, onRDOverrideChange);
  ArduinoCloud.addProperty(RD_READ, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(RU_Override, READWRITE, ON_CHANGE, onRUOverrideChange);
  ArduinoCloud.addProperty(RU_READ, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(set_Pitch_ZERO, READWRITE, ON_CHANGE, onSetPitchZEROChange);
  ArduinoCloud.addProperty(set_Roll_ZERO, READWRITE, ON_CHANGE, onSetRollZEROChange);

}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);
