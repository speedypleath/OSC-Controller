#pragma once
#include <Arduino.h>

#define SIG A0                            /* Assign SIG pin as Analog output for all 16 channels of Multiplexer to pin A0 of NodeMCU */

class Multiplexer {
private:
    int sensors[16];
    int channel = 0;

public:
    Multiplexer();

    void setup();
    void setChannel(int channel);
    bool sensorValueUpdated(int value);
    int getSensorValue();
};