#ifndef ACTUATOR_H
#define ACTUATOR_H
#include "ServoClient.h"
#include "../MQTTClient.h"
#include "../WifiManager.h"

class Actuator {
  private:
    WifiManager wifiManager;
    MQTTClient mqttClient;
    ServoClient servo;
    byte initialAngle = 90;
    long delay = 15;
    const char* topic;
    void handleAction(const String& message) {
      if (message == "OPEN") {
        servo.open();
      } else if (message == "CLOSE") {
        servo.close();
      }
    }

  public:
    Actuator(const char* SSID, const char* password, const char* broker, int port, const char* clientId, const byte& pin, const char* topic)
      : wifiManager(SSID, password), mqttClient(broker, port, clientId), servo(pin, initialAngle, delay), topic(topic) {
    }

    void init() {
      Serial.begin(115200);
      wifiManager.connect();
      mqttClient.connect();
      servo.init();
      mqttClient.subscribe(topic);
      mqttClient.setCallback([this](char* topic, byte* payload, unsigned int length) {
        Serial.print("Message arrived on topic: ");
        Serial.print(topic);
        Serial.print(". Message: ");
        String message;
        for (unsigned int i = 0; i < length; i++) {
          message += (char)payload[i];
        }
        Serial.println(message);

        this->handleAction(message);
      });
    }

    void loop() {
      if (!mqttClient.isConnected()) {
        mqttClient.connect();
      }
      mqttClient.loop();
      servo.loop();
    }
};

#endif