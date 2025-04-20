#ifndef MQTTCLIENT_H
#define MQTTCLIENT_H
#include <WiFi.h>
#include <PubSubClient.h>
class MQTTClient{
  private:
    PubSubClient psClient; 
    WiFiClient wifiClient; 
    const char* broker;
    int port;
    const char* clientId;
  public:
    MQTTClient(const char* broker, int port, const char* clientId)
    : broker(broker), port(port), clientId(clientId), psClient(wifiClient){
      psClient.setServer(broker, port);
    }

    void setCallback(MQTT_CALLBACK_SIGNATURE){
      psClient.setCallback(callback);
    }
    
    void connect() {
      while (!psClient.connected()) {
        Serial.print("Attempting MQTT connection...");
        if (psClient.connect(clientId)) {
          Serial.println("connected");
        } else {
          Serial.print("failed, rc=");
          Serial.print(psClient.state());
          Serial.println(" trying again in 5 seconds");
          delay(5000);
        }
      }
    }

    void subscribe(const char* topic) {
      if (psClient.connected()) {
        psClient.subscribe(topic);
        Serial.print("Subscribed to topic: ");
        Serial.println(topic);
      } else {
        Serial.println("Cannot subscribe, MQTT client not connected");
      }
    }

    void publish(const char* topic, const char* message) {
      if (psClient.connected()) {
        psClient.publish(topic, message);
        Serial.print("Published message: ");
        Serial.print(message);
        Serial.print(" to topic: ");
        Serial.println(topic);
      } else {
        Serial.println("Cannot publish, MQTT client not connected");
      }
    }

    void loop() {
      psClient.loop();
    }

    bool isConnected() {
      return psClient.connected();
    }
};
#endif