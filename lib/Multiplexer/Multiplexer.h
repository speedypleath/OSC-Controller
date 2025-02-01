#pragma once
#include <Arduino.h>

class Multiplexer {
private:
    int sensors[16];
    int channel;

public:
    Multiplexer(const uint8_t S0, const uint8_t S1, const uint8_t S2, const uint8_t S3, const uint8_t SIG);

    void setChannel(int channel);
    bool sensorValueUpdated(int value);
    int getSensorValue();
};