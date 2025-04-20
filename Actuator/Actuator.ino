#include "Actuator.h"

Actuator actuator("DOCTORNUTRIA", "iloveiot", "broker.hivemq.com", 1883, "VACANUTRIA123123123", 25, "doctornutria/testing/servomotor");


void setup(){
  actuator.init();
}

void loop(){
  actuator.loop();
}