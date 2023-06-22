#pragma once
#include <Arduino.h>

#define S0 D0                             /* Assign Multiplexer pin S0 connect to pin D0 of NodeMCU */
#define S1 D1                             /* Assign Multiplexer pin S1 connect to pin D1 of NodeMCU */
#define S2 D2                             /* Assign Multiplexer pin S2 connect to pin D2 of NodeMCU */
#define S3 D3                             /* Assign Multiplexer pin S3 connect to pin D3 of NodeMCU */
#define SIG A0                            /* Assign SIG pin as Analog output for all 16 channels of Multiplexer to pin A0 of NodeMCU */

class Multiplexer {
private:
    int sensors[16];
    int channel = 0;

    // Singleton
    static Multiplexer *instance;
    Multiplexer();
public:
    Multiplexer(Multiplexer &other) = delete;
    void operator=(const Multiplexer &) = delete;
    static Multiplexer *getInstance();

    void setup();
    void setChannel(int channel);
    bool sensorValueUpdated(int value);
    int getSensorValue();
};