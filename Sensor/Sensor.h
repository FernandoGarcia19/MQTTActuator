#ifndef SENSOR_H
#define SENSOR_H
#define DELAY_TIME 500
#include "../MQTTClient.h"
#include "../WifiManager.h"

class Sensor {
private:
    WifiManager wifiManager;
    MQTTClient mqttClient;
    const char* topic;
    byte pin;
    int state;
    unsigned long lastPublishTime; 

public:
    Sensor(const char* SSID, const char* password, const char* broker, int port, const char* clientId, const byte& pin, const char* topic)
        : wifiManager(SSID, password), mqttClient(broker, port, clientId), pin(pin), topic(topic), state(0), lastPublishTime(0) {
    }

    void init() {
        Serial.begin(115200);
        pinMode(pin, INPUT);
        wifiManager.connect();
        mqttClient.connect();
    }

    void readSensor() {
        state = analogRead(pin);
    }

    int getState() {
        return state;
    }

    void loop() {
        if (!mqttClient.isConnected()) {
            mqttClient.connect();
        }
        mqttClient.loop();
        
        unsigned long currentMillis = millis();
        if (currentMillis - lastPublishTime >= DELAY_TIME) {
            lastPublishTime = currentMillis; 
            readSensor();

            char buffer[10];
            snprintf(buffer, sizeof(buffer), "%d", state);
            mqttClient.publish(topic, buffer);
        }
    }
};

#endif