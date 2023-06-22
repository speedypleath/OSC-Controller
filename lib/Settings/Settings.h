#pragma once

#include <LittleFS.h>
#include <ArduinoJson.h>

class Settings {
private:
    DynamicJsonDocument config = DynamicJsonDocument(1024);
public:
    Settings() {}
    Settings(Settings &other) = delete;
    void operator=(const Settings &) = delete;
    static Settings *getInstance();

    void setup();
    void loadConfig();
    void saveConfig();

    const char* getSSID();
    const char* getPassword();
    const char* getHostname();
    const char* getOSCAddress();
    void setSSID(const char* ssid);
    void setPassword(const char* password);
    void setHostname(const char* hostname);
    void setOSCAddress(const char* oscAddress);
};