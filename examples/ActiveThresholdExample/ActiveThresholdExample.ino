#include "ActiveThreshold.h"

ActiveThreshold threshold;

void setup() {
    pinMode(5, OUTPUT);  // Example pin for LED control

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
    int sensorValue = analogRead(A0);  // Read analog value from sensor
    Serial.print("Sensor Value: ");
    Serial.println(sensorValue);

    threshold.evaluate(sensorValue);   // Evaluate the sensor value
    delay(1000);  // Delay between readings
}

// Callback to handle active state
void turnOnPin() {
    digitalWrite(5, HIGH);  // Set pin 13 HIGH (turn on LED)
    Serial.println("Active state: ON");
}

// Callback to handle inactive state
void turnOffPin() {
    digitalWrite(5, LOW);  // Set pin 13 LOW (turn off LED)
    Serial.println("Active state: OFF");
}