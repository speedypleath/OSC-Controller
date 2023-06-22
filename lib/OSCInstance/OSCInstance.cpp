#include <OSCInstance.h>

OSCInstance::OSCInstance(HardwareSerial& serial) {
    this->serial = &serial;
}

void OSCInstance::setup() {
    serial->begin(115200);
    serial->println();
    serial->println();
    serial->print("Connecting to ");
    serial->println(ssid);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        serial->print(".");
    }
    serial->println("");

    serial->println("WiFi connected");
    serial->println("IP address: ");
    serial->println(WiFi.localIP());

    serial->println("Starting UDP");
    Udp.begin(localPort);
    serial->print("Local port: ");
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