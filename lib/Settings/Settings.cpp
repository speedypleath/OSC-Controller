#include <Settings.h>

Settings::Settings() {
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
    serializeJsonPretty(config, Serial);
    file.close();
}

void Settings::configureWifi() {
  int numberOfNetworks = WiFi.scanNetworks();

  for(int i = 0; i < numberOfNetworks; i++){
      Serial.print(i + 1); 
      Serial.print(". Network name: ");
      Serial.println(WiFi.SSID(i));
      Serial.print("Signal strength: ");
      Serial.println(WiFi.RSSI(i));
      Serial.println("-----------------------");

  }

  while (Serial.available() == 0) {}
  int menuChoice = Serial.parseInt() - 1;
  auto ssid = WiFi.SSID(menuChoice);
  setSSID(ssid.c_str());

  Serial.println("Enter password:");
  while (Serial.available() == 0) {}
  auto password = Serial.readString();
  setPassword(password.c_str());

  saveConfig();
}

void Settings::resetConfig() {
    LittleFS.remove("/config.json");
    LittleFS.format();
}

const char* Settings::getSSID() {
    return config["network"]["ssid"];
}

const char* Settings::getPassword() {
    return config["network"]["password"];
}

void Settings::setSSID(const char* ssid) {
    if(!config["network"].is<JsonObject>()) {
        config["network"] = JsonObject();
    }
    config["network"]["ssid"] = ssid;
}

void Settings::setPassword(const char* password) {
    if(!config["network"].is<JsonObject>()) {
        config["network"] = JsonObject();
    }
    config["network"]["password"] = password;
}

void Settings::setHostname(const char* hostname) {
    config["hostname"] = hostname;
}

void Settings::setOSCAddress(const char* oscAddress) {
    config["oscAddress"] = oscAddress;
}