#include "Sensor.h"

Sensor photoresistor("DOCTORNUTRIA", "iloveiot", "broker.emqx.io", 1883, "fernando19garciag@gmail.com", 34, "grupo7/ucb2025/photoresistor");

void setup(){
  photoresistor.init();
}

void loop(){
  photoresistor.loop();
}