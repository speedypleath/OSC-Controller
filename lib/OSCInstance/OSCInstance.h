#pragma once

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>

enum MessageType {
    Sensor,
    Midi,
    Cutoff
};

class OSCInstance {
private:
    HardwareSerial *serial;
    const char* ssid;
    const char* password;

    WiFiUDP Udp;                                // A UDP instance to let us send and receive packets over UDP
    const IPAddress outIp = IPAddress(192,168,0,184);        // remote IP of your computer
    const unsigned int outPort = 4560;          // remote port to receive OSC
    const unsigned int localPort = 8888;        // local port to listen for OSC packets (actually not used for sending)

    // Singleton
    static OSCInstance *instance;
    OSCInstance(HardwareSerial& serial, const char* ssid, const char* password);
public:
    OSCInstance(OSCInstance &other) = delete;
    void operator=(const OSCInstance &) = delete;
    static OSCInstance *getInstance(HardwareSerial& serial, const char* ssid, const char* password);

    void setup();
    double normalize(int value);
    int normalizeCutoff(int value);
    int normalizeMidi(int value);
    void sendOSCMessage(int channel, int sensor, MessageType type);
};