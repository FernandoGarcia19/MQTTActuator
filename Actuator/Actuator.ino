#include "Actuator.h"

Actuator actuator("DOCTORNUTRIA", "iloveiot", "broker.emqx.io", 1883, "fernando19garciag@gmail.com", 25, "grupo7/ucb2025/servomotor");


void setup(){
  actuator.init();
}

void loop(){
  actuator.loop();
}