// Extend Analog Inputs for NodeMCU board using 16 channel Analog Multiplexer

// Note Summary
// Note : Safety is very important when dealing with electricity. We take no responsibilities while you do it at your own risk.
// Note : NodeMCU is a very famous micro-controller with Wifi function which is commonly used for Internet Of Thing (IOT) application. 
// Note : However,NodeMCU only has one analog input which only allow to read one analog sensor.  
// Note : This code is made practical to convert 1 Analog Input to up to 16 Analog Inputs using the 16-channel Analog Multiplexer Module.
// Note : The main code for 16 channel Analog Multiplexer was Written by Sachin Soni for techiesms YouTube channel & community (https://www.youtube.com/watch?v=02spXPoa_Y8)
// Note : Solarduino is only to modify the code to suit our own undertanding and application.
 
/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/////////////*/

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>

#ifndef STASSID
#define STASSID "ZTE_CD9944"
#define STAPSK "3rgy.AGv"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

WiFiUDP Udp;                                // A UDP instance to let us send and receive packets over UDP
const IPAddress outIp(192,168,0,184);        // remote IP of your computer
const unsigned int outPort = 4560;          // remote port to receive OSC
const unsigned int localPort = 8888;        // local port to listen for OSC packets (actually not used for sending)

#define S0 D0                             /* Assign Multiplexer pin S0 connect to pin D0 of NodeMCU */
#define S1 D1                             /* Assign Multiplexer pin S1 connect to pin D1 of NodeMCU */
#define S2 D2                             /* Assign Multiplexer pin S2 connect to pin D2 of NodeMCU */
#define S3 D3                             /* Assign Multiplexer pin S3 connect to pin D3 of NodeMCU */
#define SIG A0                            /* Assign SIG pin as Analog output for all 16 channels of Multiplexer to pin A0 of NodeMCU */

int decimal = 2;                          // Decimal places of the sensor value outputs 
int sensor0;                            /* Assign the name "sensor0" as analog output value from Channel C0 */
int sensor1;                            /* Assign the name "sensor1" as analog output value from Channel C1 */
int sensor2;                            /* Assign the name "sensor2" as analog output value from Channel C2 */
int sensor3;                            /* Assign the name "sensor3" as analog output value from Channel C3 */
int sensor4;                            /* Assign the name "sensor4" as analog output value from Channel C4 */
int sensor5;                            /* Assign the name "sensor5" as analog output value from Channel C5 */
int sensor6;                            /* Assign the name "sensor6" as analog output value from Channel C6 */
int sensor7;                            /* Assign the name "sensor7" as analog output value from Channel C7 */
int sensor8;                            /* Assign the name "sensor8" as analog output value from Channel C8 */
int sensor9;                            /* Assign the name "sensor9" as analog output value from Channel C9 */
int sensor10;                           /* Assign the name "sensor10" as analog output value from Channel C10 */
int sensor11;                           /* Assign the name "sensor11" as analog output value from Channel C11 */
int sensor12;                           /* Assign the name "sensor12" as analog output value from Channel C12 */
int sensor13;                           /* Assign the name "sensor13" as analog output value from Channel C13 */
int sensor14;                           /* Assign the name "sensor14" as analog output value from Channel C14 */
int sensor15;                           /* Assign the name "sensor15" as analog output value from Channel C15 */
int analogValue;                        /* Assign the name "analogValue" as analog output value from Channel C0 to C15 */

double normalize(int value) {
    return (double)value / 1024.0;
}

int normalizeMidi(int value) {
    return (int)(normalize(value) * 127);
}

void sendOSCMessage() {
    OSCMessage msg("/test");
    msg.add(normalize(sensor0));
    msg.add(normalizeMidi(sensor1));
    msg.add(normalizeMidi(sensor2));
    msg.add(normalize(sensor3));
    Serial.println("Sending OSC message");
    Serial.println(normalize(sensor0));
    Serial.println(normalizeMidi(sensor1));
    Serial.println(normalizeMidi(sensor2));
    Serial.println(normalize(sensor3));
    Udp.beginPacket(outIp, outPort);
    msg.send(Udp);
    Udp.endPacket();
    msg.empty();
}

bool sensorValueUpdated(int lastValue, int newValue) {
    return lastValue != newValue && abs(lastValue - newValue) > 10;
}

void setup() {                                /* Put your codes here to run only once during micro controller startup */

  /* 0- General */
  
    pinMode(S0,OUTPUT);                       /* Define digital signal pin as output to the Multiplexer pin SO */        
    pinMode(S1,OUTPUT);                       /* Define digital signal pin as output to the Multiplexer pin S1 */  
    pinMode(S2,OUTPUT);                       /* Define digital signal pin as output to the Multiplexer pin S2 */ 
    pinMode(S3,OUTPUT);                       /* Define digital signal pin as output to the Multiplexer pin S3 */  
    pinMode(SIG, INPUT);                      /* Define analog signal pin as input or receiver from the Multiplexer pin SIG */  
  
    Serial.begin(115200);

    // Connect to WiFi network
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");

    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    Serial.println("Starting UDP");
    Udp.begin(localPort);
    Serial.print("Local port: ");
}

void loop() {                                 /* Put your codes here to run over and over again endlessly */
  if(millis() % 10 == 0) {
    // Channel 0 (C0 pin - binary output 0,0,0,0)
    digitalWrite(S0,LOW); digitalWrite(S1,LOW); digitalWrite(S2,LOW); digitalWrite(S3,LOW);
    analogValue = analogRead(SIG);
    if(sensorValueUpdated(sensor0, analogValue)) {
      sensor0 = analogValue;
      sendOSCMessage();
    }
  
    // Channel 1 (C1 pin - binary output 1,0,0,0)
    digitalWrite(S0,HIGH); digitalWrite(S1,LOW); digitalWrite(S2,LOW); digitalWrite(S3,LOW);
    analogValue = analogRead(SIG);
    if(sensorValueUpdated(sensor1, analogValue)) {
      sensor1 = analogValue;
      sendOSCMessage();
    }

    // Channel 2 (C2 pin - binary output 0,1,0,0)
    digitalWrite(S0,LOW); digitalWrite(S1,HIGH); digitalWrite(S2,LOW); digitalWrite(S3,LOW);
    analogValue = analogRead(SIG);
    if(sensorValueUpdated(sensor2, analogValue)) {
      sensor2 = analogValue;
      sendOSCMessage();
    }
  
    // Channel 3 (C3 pin - binary output 1,1,0,0)
    digitalWrite(S0,HIGH); digitalWrite(S1,HIGH); digitalWrite(S2,LOW); digitalWrite(S3,LOW);
    analogValue = analogRead(SIG);
    if(sensorValueUpdated(sensor3, analogValue)) {
      sensor3 = analogValue;
      sendOSCMessage();
    }
  
    // // Channel 4 (C4 pin - binary output 0,0,1,0)
    // digitalWrite(S0,LOW); digitalWrite(S1,LOW); digitalWrite(S2,HIGH); digitalWrite(S3,LOW);
    // sensor4 = analogRead(SIG);
  
    // // Channel 5 (C5 pin - binary output 1,0,1,0)
    // digitalWrite(S0,HIGH); digitalWrite(S1,LOW); digitalWrite(S2,HIGH); digitalWrite(S3,LOW);
    // sensor5 = analogRead(SIG);

    // // Channel 6 (C6 pin - binary output 0,1,1,0)
    // digitalWrite(S0,LOW); digitalWrite(S1,HIGH); digitalWrite(S2,HIGH); digitalWrite(S3,LOW);
    // sensor6 = analogRead(SIG);

    // // Channel 7 (C7 pin - binary output 1,1,1,0)
    // digitalWrite(S0,HIGH); digitalWrite(S1,HIGH); digitalWrite(S2,HIGH); digitalWrite(S3,LOW);
    // sensor7 = analogRead(SIG);

    // // Channel 8 (C8 pin - binary output 0,0,0,1)
    // digitalWrite(S0,LOW); digitalWrite(S1,LOW); digitalWrite(S2,LOW); digitalWrite(S3,HIGH);
    // sensor8 = analogRead(SIG);

    // // Channel 9 (C9 pin - binary output 1,0,0,1)
    // digitalWrite(S0,HIGH); digitalWrite(S1,LOW); digitalWrite(S2,LOW); digitalWrite(S3,HIGH);
    // sensor9 = analogRead(SIG);

    // // Channel 10 (C10 pin - binary output 0,1,0,1)
    // digitalWrite(S0,LOW); digitalWrite(S1,HIGH); digitalWrite(S2,LOW); digitalWrite(S3,HIGH);
    // sensor10 = analogRead(SIG);

    // // Channel 11 (C11 pin - binary output 1,1,0,1)
    // digitalWrite(S0,HIGH); digitalWrite(S1,HIGH); digitalWrite(S2,LOW); digitalWrite(S3,HIGH);
    // sensor11 = analogRead(SIG);

    // // Channel 12 (C12 pin - binary output 0,0,1,1)
    // digitalWrite(S0,LOW); digitalWrite(S1,LOW); digitalWrite(S2,HIGH); digitalWrite(S3,HIGH);
    // sensor12 = analogRead(SIG);

    // // Channel 13 (C13 pin - binary output 1,0,1,1)
    // digitalWrite(S0,HIGH); digitalWrite(S1,LOW); digitalWrite(S2,HIGH); digitalWrite(S3,HIGH);
    // sensor13 = analogRead(SIG);

    // // Channel 14 (C14 pin - binary output 0,1,1,1)
    // digitalWrite(S0,LOW); digitalWrite(S1,HIGH); digitalWrite(S2,HIGH); digitalWrite(S3,HIGH);
    // sensor14 = analogRead(SIG);

    // // Channel 15 (C15 pin - binary output 1,1,1,1)
    // digitalWrite(S0,HIGH); digitalWrite(S1,HIGH); digitalWrite(S2,HIGH); digitalWrite(S3,HIGH);
    // sensor15 = analogRead(SIG);
  }
}