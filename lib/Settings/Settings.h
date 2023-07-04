#pragma once

#include <LittleFS.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>

class Settings {
private:
    DynamicJsonDocument config = DynamicJsonDocument(1024);

public:
    Settings();

    void loadConfig();
    void saveConfig();
    void configureWifi();
    void resetConfig();

    const char* getSSID();
    const char* getPassword();
    const char* getHostname();
    const char* getOSCAddress();
    void setSSID(const char* ssid);
    void setPassword(const char* password);
    void setHostname(const char* hostname);
    void setOSCAddress(const char* oscAddress);
};