/*
 * esp32meteostation
 * main file
 * Author: Tomas Weber
 * Date: 18/06/22
 */

// user defined secret variables
#include "secrets.h"

// esp32 WiFi library
#include "WiFi.h"
const unsigned long wifiConnectionTimeout = 15000; // ...in milliseconds

// pins definition
// RGB led pins
const int RGBpin[3] = {
    27, // 0 - RED
    26, // 1 - GREEN
    33  // 2 - BLUE
};
// LDR ADC pin
const int LDRpin = 34;

bool wifiConnect();
void blinkJobTypeCode(int iterations);
void blinkStatusCode(int color);

void setup() {
    Serial.begin(115200);

    // set the pinMode for the RGBpin led pins
    Serial.print("Setting pinMode for RGBpin led pins. ");
    for (int i = 0; i < 3; i++) {
        pinMode(RGBpin[i], OUTPUT);
        digitalWrite(RGBpin[i], LOW);
    }
    Serial.println("Done.");

    // connect to the WiFi
    Serial.print("Connecting to the WiFi. ");
    // blink the WiFi code
    blinkJobTypeCode(2);
    if (wifiConnect()) {
        Serial.println(" Done.");
        blinkStatusCode(RGBpin[1]);
    }
    else {
        Serial.println(" WiFi connection cannot be established.");
        blinkStatusCode(RGBpin[0]);
    }
}

void loop() {
    Serial.println(analogRead(LDRpin));
}
bool wifiConnect() {
    // setup the WiFi
    WiFi.setHostname(wifiHostname);
    WiFi.begin(wifiSsid, wifiPassword);

    // connect to the WiFi
    // set the current time for the WiFi connection timeout
    unsigned long currentMillis = millis();
    while (WiFi.status() != WL_CONNECTED) {
        // check the time for the timeout
        if (millis() > wifiConnectionTimeout + currentMillis)
            // if the timeout pass, exit the connection loop
            break;
        Serial.print(".");
        digitalWrite(RGBpin[2], HIGH);
        delay(50);
        digitalWrite(RGBpin[2], LOW);
        delay(150);
    }

    if (WiFi.status() != WL_CONNECTED)
        return false;
    
    Serial.print(WiFi.localIP());
    return true;
}
void blinkJobTypeCode(int iterations) {
    for (int i = 0; i < iterations; i++) {
        digitalWrite(RGBpin[2], HIGH);
        delay(400);
        digitalWrite(RGBpin[2], LOW);
        delay(100);
    }
}
void blinkStatusCode(int color) {
    digitalWrite(color, HIGH);
    delay(500);
    digitalWrite(color, LOW);
}