#include <Multiplexer.h>

Multiplexer::Multiplexer() {
    for(int i = 0; i < 16; i++) {
        sensors[i] = 0;
    }

    setup();
}

void Multiplexer::setup() {
    pinMode(D5,OUTPUT);                       /* Define digital signal pin as output to the Multiplexer pin SO */        
    pinMode(D6,OUTPUT);                       /* Define digital signal pin as output to the Multiplexer pin S1 */  
    pinMode(D7,OUTPUT);                       /* Define digital signal pin as output to the Multiplexer pin S2 */ 
    pinMode(D8,OUTPUT);                       /* Define digital signal pin as output to the Multiplexer pin S3 */  
    pinMode(SIG, INPUT);                      /* Define analog signal pin as input or receiver from the Multiplexer pin SIG */  
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