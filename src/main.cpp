#include <OSCInstance.h>
#include <Multiplexer.h>
#include <Settings.h>

OSCInstance *osc;
Multiplexer *multiplexer = Multiplexer::getInstance();
Settings *settings = new Settings();
int analogValue;

void setup() {
    multiplexer->setup();
    settings->setup();
    settings->loadConfig();
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