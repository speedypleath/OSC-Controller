#include <OSCInstance.h>
#include <Multiplexer.h>
#include <Settings.h>
#include <LiquidCrystal_I2C.h>

OSCInstance osc(Serial);
Multiplexer multiplexer(D5, D6, D7, D8, A0);
Settings settings;
LiquidCrystal_I2C lcd(0x27, 16, 2);
int analogValue;

void setup() {
    Serial.begin(115200);
    settings.loadConfig();

    if(!settings.getSSID() || !settings.getPassword()) {
      settings.configureWifi();
      settings.loadConfig();
    }

    osc.setup(settings.getSSID(), settings.getPassword());

    lcd.init();
    lcd.clear();         
    lcd.backlight();
}

void loop() {
  if(millis() % 10 == 0) {
    multiplexer.setChannel(0);
    analogValue = analogRead(A0);
    if(multiplexer.sensorValueUpdated(analogValue)) {
      lcd.clear();  
      lcd.setCursor(0,0);
      lcd.print("Sensor 1: ");
      lcd.print(analogValue);
      osc.sendOSCMessage(0, analogValue, Sensor);
    }
  
    multiplexer.setChannel(1);
    analogValue = analogRead(A0);
    if(multiplexer.sensorValueUpdated(analogValue)) {
      osc.sendOSCMessage(1, analogValue, Midi);
    }

    multiplexer.setChannel(2);
    analogValue = analogRead(A0);
    if(multiplexer.sensorValueUpdated(analogValue)) {
      osc.sendOSCMessage(2, analogValue, Cutoff);
    }
  
    multiplexer.setChannel(3);
    analogValue = analogRead(A0);
    if(multiplexer.sensorValueUpdated(analogValue)) {
      osc.sendOSCMessage(3, analogValue, Sensor);
    }
  }
}