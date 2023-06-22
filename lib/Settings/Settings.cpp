#include <Settings.h>

// Settings *Settings::getInstance() {
//     if(!instance) {
//         instance = new Settings();
//     }
//     return instance;
// }

void Settings::setup() {
    if(!LittleFS.begin()) {
        Serial.println("An Error has occurred while mounting LittleFS");
        return;
    }
    LittleFS.openDir("/");
}

void Settings::loadConfig() {
    File file = LittleFS.open("/config.json", "r");
    if(!file) {
        Serial.println("Failed to open config file");
        return;
    }

    DeserializationError error = deserializeJson(config, file);
    if(error) {
        Serial.println("Failed to read file, using default configuration");
        return;
    }

    file.close();
}

void Settings::saveConfig() {
    File file = LittleFS.open("/config.json", "w");
    if(!file) {
        Serial.println("Failed to open config file for writing");
        return;
    }

    serializeJson(config, file);
    file.close();
}

const char* Settings::getSSID() {
    return config["ssid"];
}

const char* Settings::getPassword() {
    return config["password"];
}

void Settings::setSSID(const char* ssid) {
    config["ssid"] = ssid;
}

void Settings::setPassword(const char* password) {
    config["password"] = password;
}

void Settings::setHostname(const char* hostname) {
    config["hostname"] = hostname;
}

void Settings::setOSCAddress(const char* oscAddress) {
    config["oscAddress"] = oscAddress;
}

// Settings *Settings::instance = nullptr;