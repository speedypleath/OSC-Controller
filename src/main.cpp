#include <OSCInstance.h>
#include <Multiplexer.h>
#include <Settings.h>

OSCInstance *osc;
Multiplexer *multiplexer = Multiplexer::getInstance();
Settings *settings = Settings::getInstance();
int analogValue;

void configureWifi() {
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
  settings->setSSID(ssid.c_str());

  Serial.println("Enter password:");
  while (Serial.available() == 0) {}
  auto password = Serial.readString();
  settings->setPassword(password.c_str());

  settings->saveConfig();
}

void setup() {
    Serial.begin(115200);
    multiplexer->setup();
    settings->setup();
    settings->loadConfig();

    if(!settings->getSSID() || !settings->getPassword()) {
      configureWifi();
      settings->loadConfig();
    }

    osc = OSCInstance::getInstance(Serial, settings->getSSID(), settings->getPassword());
    osc->setup();
}

void loop() {
  if(millis() % 10 == 0) {
    multiplexer->setChannel(0);
    analogValue = analogRead(SIG);
    if(multiplexer->sensorValueUpdated(analogValue)) {
      osc->sendOSCMessage(0, analogValue, Sensor);
    }
  
    multiplexer->setChannel(1);
    analogValue = analogRead(SIG);
    if(multiplexer->sensorValueUpdated(analogValue)) {
      osc->sendOSCMessage(1, analogValue, Midi);
    }

    multiplexer->setChannel(2);
    analogValue = analogRead(SIG);
    if(multiplexer->sensorValueUpdated(analogValue)) {
      osc->sendOSCMessage(2, analogValue, Cutoff);
    }
  
    multiplexer->setChannel(3);
    analogValue = analogRead(SIG);
    if(multiplexer->sensorValueUpdated(analogValue)) {
      osc->sendOSCMessage(3, analogValue, Sensor);
    }
  }
}