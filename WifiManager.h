#ifndef WIFIMANAGER_H
#define WIFIMANAGER_H
#include <WiFi.h>

class WifiManager{
  private:
    const char* password;
    const char* SSID;
  public:
    WifiManager(const char* SSID, const char* password)
    : password(password), SSID(SSID){
    }
    void connect(){
      Serial.print("Connecting to ");
      Serial.println(SSID);
      WiFi.mode(WIFI_STA);
      WiFi.begin(SSID, password);
      Serial.print("Connected to WiFi. IP address: ");
      Serial.println(WiFi.localIP());
    }
    bool isConected(){
        return (WiFi.status() == WL_CONNECTED);
    }
};

#endif