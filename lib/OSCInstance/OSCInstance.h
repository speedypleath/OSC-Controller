#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>
#include <Credentials.h>

enum MessageType {
    Sensor,
    Midi,
    Cutoff
};

class OSCInstance {
private:
    const char* ssid = STASSID;
    const char* password = STAPSK;

    HardwareSerial *serial;
    WiFiUDP Udp;                                // A UDP instance to let us send and receive packets over UDP
    const IPAddress outIp = IPAddress(192,168,0,184);        // remote IP of your computer
    const unsigned int outPort = 4560;          // remote port to receive OSC
    const unsigned int localPort = 8888;        // local port to listen for OSC packets (actually not used for sending)

public:
    OSCInstance(HardwareSerial& serial);
    void setup();
    double normalize(int value);
    int normalizeCutoff(int value);
    int normalizeMidi(int value);
    void sendOSCMessage(int channel, int sensor, MessageType type);
};