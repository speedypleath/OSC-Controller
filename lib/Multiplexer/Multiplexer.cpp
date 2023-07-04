#include <Multiplexer.h>

Multiplexer::Multiplexer(const uint8_t S0, const uint8_t S1, const uint8_t S2, const uint8_t S3, const uint8_t SIG) {
    for(int i = 0; i < 16; i++) {
        sensors[i] = 0;
    }

    pinMode(D5,OUTPUT);
    pinMode(D6,OUTPUT);         
    pinMode(D7,OUTPUT);            
    pinMode(D8,OUTPUT);           
    pinMode(SIG, INPUT);                    
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