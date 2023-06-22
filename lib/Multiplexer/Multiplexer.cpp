#include <Multiplexer.h>

Multiplexer::Multiplexer() {
    for(int i = 0; i < 16; i++) {
        sensors[i] = 0;
    }
}

Multiplexer *Multiplexer::getInstance() {
    if(!instance) {
        instance = new Multiplexer();
    }
    return instance;
}

void Multiplexer::setup() {
    pinMode(S0,OUTPUT);                       /* Define digital signal pin as output to the Multiplexer pin SO */        
    pinMode(S1,OUTPUT);                       /* Define digital signal pin as output to the Multiplexer pin S1 */  
    pinMode(S2,OUTPUT);                       /* Define digital signal pin as output to the Multiplexer pin S2 */ 
    pinMode(S3,OUTPUT);                       /* Define digital signal pin as output to the Multiplexer pin S3 */  
    pinMode(SIG, INPUT);                      /* Define analog signal pin as input or receiver from the Multiplexer pin SIG */  
}

void Multiplexer::setChannel(int channel) {
    this->channel = channel;
    digitalWrite(S0, channel & 1);
    digitalWrite(S1, channel & 2);
    digitalWrite(S2, channel & 4);
    digitalWrite(S3, channel & 8);
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

Multiplexer *Multiplexer::instance = nullptr;