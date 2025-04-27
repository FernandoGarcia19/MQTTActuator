#include "config.h"
#include "Actuator/Actuator.h"
#include "Sensor/Sensor.h"

Actuator actuator(SSID, password, broker, port, actuatorID, actuatorPin, actuatorTopic);
Sensor sensor(SSID, password, broker, port, sensorID, sensorPin, sensorTopic);

void setup(){
  sensor.init();
  actuator.init();
}

void loop(){
  sensor.loop();
  actuator.loop();
}