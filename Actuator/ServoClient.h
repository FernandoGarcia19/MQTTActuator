#ifndef SERVOCLIENT_H
#define SERVOCLIENT_H
#include <ESP32Servo.h>

class ServoClient {
  private:
    Servo servo;
    byte pin;
    byte currentAngle;
    byte targetAngle;
    long delayDuration;
  public:
    ServoClient(byte pin, byte initialAngle, long delayDuration)
    : pin(pin), currentAngle(initialAngle), targetAngle(initialAngle), delayDuration(delayDuration){
    }
    void init(){
      servo.attach(pin);
      servo.write(targetAngle);
    }
    void moveToTarget(){
      servo.write(currentAngle);
      delay(delayDuration);
    }
    void loop(){
      if (currentAngle < targetAngle){
        currentAngle++;
        moveToTarget();
      }
      else if (currentAngle > targetAngle){
        currentAngle--;
        moveToTarget();
      }
      
    }
    void setTarget(const byte& target){
      this->targetAngle = target;
    }
    void open(){
      targetAngle = 90; 
    }
    void close(){
      targetAngle = 180;
    }
};

#endif 