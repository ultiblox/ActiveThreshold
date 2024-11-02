# ActiveThreshold Library

## Overview
The `ActiveThreshold` library provides an efficient way to manage threshold-based activation and deactivation for analog or digital signals, commonly used with sensors in embedded systems. It enables automatic triggering based on predefined thresholds, useful in projects where specific signal values should activate or deactivate functions. For example, it can automate alerts or control devices when temperature, light, or voltage levels cross critical values.

## Features
- **Custom Threshold Setting**: Set and modify a threshold value for activation based on specific conditions.
- **Persistent Storage**: Save and load threshold values to/from EEPROM, ensuring they remain across power cycles.
- **Active-High / Active-Low Modes**: Configure activation to occur when a signal crosses above (active-high) or below (active-low) the threshold.
- **Callback Functions**: Trigger specific actions when entering or leaving the active state.
- **Threshold Adjustment**: Increment or decrement threshold values dynamically, with changes saved in EEPROM.

## Key Concepts

- **Threshold Setting**: Defines the activation boundary, where values above or below it can trigger callbacks, depending on the configuration. Example: If the threshold is set to 600, the library can activate when a sensor value goes above or below 600 based on active-high or active-low mode.

- **Active-High / Active-Low Mode**:
  - **Active-High** mode: Activation occurs when the signal reaches or exceeds the threshold. This is useful for scenarios like detecting overheating where high temperatures activate a cooling system.
  - **Active-Low** mode: Activation occurs when the signal falls below the threshold, useful for monitoring conditions like low battery levels.

- **Persistent Storage with EEPROM**:
  - Saves thresholds across device resets using EEPROM storage, which is non-volatile memory. This feature is beneficial for long-term applications where the threshold should be retained even after power cycles.

## Methods

- `init()`: Initializes the threshold management with any specified configurations. **Note**: `init()` should be called after setting up all other configurations, to finalize the setup.
- `setDefaultThreshold(int defaultThreshold)`: Sets a default threshold, applied if no custom threshold is set.
- `setThreshold(int threshold)`: Configures a specific threshold, overriding the default.
- `setActiveHigh(bool isActiveHigh)`: Configures activation behavior as active-high (true) or active-low (false).
- `onActive(void (*callback)())`: Defines a callback function that triggers when activation occurs.
- `onInactive(void (*callback)())`: Defines a callback function that triggers when deactivation occurs.
- `evaluate(int value)`: Evaluates the given value against the current threshold and calls the appropriate callback if a state change occurs.
- `loadThresholdFromEEPROM()`: Loads the threshold value saved in EEPROM.
- `saveThresholdToEEPROM()`: Saves the current threshold value to EEPROM.
- `incrementThreshold()`: Increases the threshold by one and saves the new value to EEPROM.
- `decrementThreshold()`: Decreases the threshold by one and saves the new value to EEPROM.
- `getThreshold()`: Returns the current active threshold value.

## Usage Example

Below is a sample setup to initialize the library, set a custom threshold, and define active/inactive callbacks to control an LED based on sensor input.

```cpp
#include "ActiveThreshold.h"

ActiveThreshold threshold;

void onThresholdActive() {
    Serial.println("Threshold Active!");
    digitalWrite(LED_BUILTIN, HIGH);  // Turn LED on
}

void onThresholdInactive() {
    Serial.println("Threshold Inactive!");
    digitalWrite(LED_BUILTIN, LOW);   // Turn LED off
}

void setup() {
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);                      // Set up built-in LED
    threshold.setDefaultThreshold(400)                 // Set default threshold
             .setThreshold(600)                        // Set custom threshold
             .setActiveHigh(true)                      // Configure as active-high
             .onActive(onThresholdActive)              // Set activation callback
             .onInactive(onThresholdInactive);         // Set deactivation callback

    threshold.init();                                  // Initialize after configuration
}

void loop() {
    int sensorValue = analogRead(A0);                  // Example sensor reading
    threshold.evaluate(sensorValue);                   // Evaluate against threshold
}
```

### EEPROM Error Handling
To ensure reliable EEPROM loading, check if a valid threshold was loaded. If not, you can use the default threshold:

```cpp
threshold.loadThresholdFromEEPROM();
if (threshold.getThreshold() == 0) {  
    Serial.println("EEPROM load failed, using default threshold.");
}
```

## Dependencies
- **EEPROM Library**: Required for threshold persistence.
- **Arduino Core Library**: Standard functions used across Arduino sketches.

## License
[This project is licensed under the UltiBlox License.](https://ultiblox.org/license)
