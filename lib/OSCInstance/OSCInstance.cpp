#include <OSCInstance.h>

OSCInstance::OSCInstance(HardwareSerial& serial): serial(&serial) {}

void OSCInstance::setup(const char* ssid, const char* password) {
    this->ssid = ssid;
    this->password = password;
    
    this->serial->println();
    this->serial->println();
    this->serial->print("Connecting to: ");
    this->serial->println(ssid);
 
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        this->serial->print(".");
    }
    this->serial->println("");

    this->serial->println("WiFi connected");
    this->serial->println("IP address: ");
    this->serial->println(WiFi.localIP());

    this->serial->println("Starting UDP");
    Udp.begin(localPort);
    this->serial->print("Local port: ");
}

double OSCInstance::normalize(int value) {
    return (double)value / 1024.0;
}

int OSCInstance::normalizeMidi(int value) {
    return (int)(normalize(value) * 127);
}

int OSCInstance::normalizeCutoff(int value) {
    return (int)(normalize(value) * 137);
}

void OSCInstance::sendOSCMessage(int channel, int sensor, MessageType type) {
    char address[10];
    char printBuffer[64];

    sprintf(address, "test/%d", channel);
    OSCMessage msg(address);

    switch (type)
    {
    case Sensor:
        msg.add(normalize(sensor));
        sprintf(printBuffer, "Sending OSC message to address: %s with value: %lf", address, normalize(sensor));
        break;
    case Midi:
        sprintf(printBuffer, "Sending OSC message to address: %s with value: %d", address, normalizeMidi(sensor));
        msg.add(normalizeMidi(sensor));
        break;
    case Cutoff:
        sprintf(printBuffer, "Sending OSC message to address: %s with value: %d", address, normalizeCutoff(sensor));
        msg.add(normalizeCutoff(sensor));
        break;
    default:
        break;
    }

    serial->println(printBuffer);
    Udp.beginPacket(outIp, outPort);
    msg.send(Udp);
    Udp.endPacket();
    msg.empty();
}