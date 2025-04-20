#include <WiFi.h>
#include <PubSubClient.h>
#include "ServoClient.h"

ServoClient myServo(25, 90, 15);

const char* WIFI_SSID = "DOCTORNUTRIA";
const char* WIFI_PASS = "iloveiot";

// Replace with your MQTT broker details
const char* MQTT_BROKER = "broker.hivemq.com";
const int MQTT_PORT = 1883;
const char* CLIENT_ID = "doctornutria9416526"; // Change me

WiFiClient wiFiClient;
PubSubClient client(wiFiClient);

// Callback function to handle messages received from the subscribed topic
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String message;
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.print(message);
  Serial.print("\n");
  if (message == "OPEN") {
    myServo.open();
  }
  else {
    myServo.close();
  }
}

void setup() {
  myServo.init();
  Serial.begin(115200);
  setupWiFi();
  
  client.setServer(MQTT_BROKER, MQTT_PORT);
  client.setCallback(callback);
  
}

void setupWiFi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Connected to WiFi. IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(CLIENT_ID)) {
      Serial.println("connected");
      // Subscribe to a topic
      client.subscribe("doctornutria/testing/servomotor");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" trying again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  myServo.loop();
}