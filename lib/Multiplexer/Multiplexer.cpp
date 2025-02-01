
#include <Arduino.h> // Add this line to include the Arduino header file
#include "Multiplexer.h"

Multiplexer::Multiplexer(const uint8_t S0, const uint8_t S1, const uint8_t S2, const uint8_t S3, const uint8_t SIG) {
    for(int i = 0; i < 16; i++) {
        sensors[i] = 0;
    } // Adjust the indentation of the closing bracezq

    pinMode(S0, OUTPUT);
    pinMode(S1, OUTPUT);         
    pinMode(S2, OUTPUT);            
    pinMode(S3, OUTPUT);           
    pinMode(SIG, INPUT_PULLUP); // Change INPUT to INPUT_PULLUP to set the pin mode correctly                   
}

void Multiplexer::setChannel(int channel) {
    this->channel = channel;
    digitalWrite(D5, channel & 1);
    digitalWrite(D6, channel & 2);
    digitalWrite(D7, channel & 4);
    digitalWrite(D8, channel & 8);
};

bool Multiplexer::sensorValueUpdated(int value) {
    if(sensors[channel] != value && abs(sensors[channel] - value) > 10) {
        sensors[channel] = value;
        return true;
    }
    return false;
};

int Multiplexer::getSensorValue() {
    return sensors[channel];
};