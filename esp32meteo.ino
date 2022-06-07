#include "secrets.h"

#include "WiFi.h"

void setup() {
    Serial.begin(115200);

    WiFi.begin(wifiSsid, wifiPassword);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Connecting to WiFi..");
    }
 
    Serial.println("Connected to the WiFi network");
}

void loop() {

}