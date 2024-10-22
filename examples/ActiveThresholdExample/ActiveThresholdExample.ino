#include "ActiveThreshold.h"

ActiveThreshold threshold;

int ledPin = 13;

void setup() {
    pinMode(ledPin, OUTPUT);  // Example pin for LED control

    // Initialize the threshold system
    threshold.init()
             .setDefaultThreshold(500)   // Set default threshold
             .loadThresholdFromEEPROM()  // Load any stored threshold from EEPROM
             .setActiveHigh(true)        // Configure active-high behavior
             .onActive(turnOnPin)        // Define what happens when active
             .onInactive(turnOffPin);    // Define what happens when inactive

    Serial.begin(115200);
    Serial.println("Threshold system initialized");
}

void loop() {
    int sensorValue = analogRead(A0);
    Serial.print("Sensor Value: ");
    Serial.println(sensorValue);

    threshold.evaluate(sensorValue);
    delay(1000);
}

// Callback to handle active state
void turnOnPin() {
    digitalWrite(ledPin, HIGH);
    Serial.println("Active state: ON");
}

// Callback to handle inactive state
void turnOffPin() {
    digitalWrite(ledPin, LOW);
    Serial.println("Active state: OFF");
}