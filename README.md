# UltiBlox ActiveThreshold Library

*Automatically turn devices on or off when values cross a set threshold.*

[UltiBlox on GitHub](https://github.com/UltiBlox/ActiveThreshold) | [UltiBlox Home](https://ultiblox.org)

## Overview

The `ActiveThreshold` library helps you monitor values and trigger actions based on configurable thresholds, making it ideal for automating responses to sensor data or other input signals. With customizable activation modes and callback support, `ActiveThreshold` offers a straightforward way to implement threshold-based control in embedded systems. If no custom threshold is set, the **default threshold** is used, which can be particularly useful for initial testing or fallback scenarios.

## Features

- Set custom thresholds for activation.
- Configure **Active-High** or **Active-Low** behavior.
- Store thresholds persistently using EEPROM, with a default fallback.
- Register callbacks for activation and deactivation events.
- Increment or decrement thresholds with automatic EEPROM updates.

## Installation

### Option 1: Arduino Library Manager Installation (Recommended)

1. Open the **Arduino IDE**.
2. Go to **Tools > Manage Libraries**.
3. Search for **UltiBlox ActiveThreshold** and click **Install**.
4. Access example sketches under **File > Examples > UltiBlox ActiveThreshold**.

### Option 2: Manual Installation (for Development and Customization)

1. **Clone the Repository**:
   
   ```bash
   git clone git@github.com:UltiBlox/ActiveThreshold.git ~/workspace/ActiveThreshold
   cd ~/workspace/ActiveThreshold
   ```

2. **Prepare the Environment**:
   Run the `prepare.sh` script to set up dependencies:
   
   ```bash
   bash prepare.sh
   ```

3. **Install the Library**:
   
   - **Copy Installation**:
     
     ```bash
     bash install.sh
     ```
   - **Symlink Installation** (for active development):
     
     ```bash
     bash install-symlink.sh
     ```

4. **Build Examples**:
   Compile example sketches with:
   
   ```bash
   bash build.sh
   ```

## Dependencies

- **EEPROM Library**: Required for persistent storage of thresholds.
- **Arduino Core Library**

## Usage Example

Refer to the [ActiveThresholdExample.ino](examples/ActiveThresholdExample/ActiveThresholdExample.ino) file for a complete usage example demonstrating threshold-based activation and deactivation.

## Methods

### Initialize the Threshold System

```cpp
init()
```

Initializes the threshold system.

### Set the Default Threshold

```cpp
setDefaultThreshold(int defaultThreshold)
```

Sets a default threshold value for triggering activation if no custom threshold is set or stored in EEPROM. This fallback threshold ensures the system can operate without requiring a stored value.

### Define a Custom Threshold

```cpp
setThreshold(int threshold)
```

Defines a custom threshold value.

### Configure Active-High or Active-Low Behavior

```cpp
setActiveHigh(bool isActiveHigh)
```

Sets activation mode to **active-high** (`true`), activating when the value meets or exceeds the threshold, or **active-low** (`false`), activating when the value falls below the threshold.

### Register Callback for Activation

```cpp
onActive(void (*callback)())
```

Registers a callback function to execute when the threshold becomes active.

### Register Callback for Deactivation

```cpp
onInactive(void (*callback)())
```

Registers a callback function to execute when the threshold becomes inactive.

### Evaluate the Input Value

```cpp
evaluate(int value)
```

Evaluates the input value against the threshold, monitoring for changes in the activation state and triggering the appropriate callback if a state change occurs.

### Load Threshold from EEPROM

```cpp
loadThresholdFromEEPROM()
```

Loads the saved threshold from EEPROM, if available. If no threshold is stored, the default threshold will be used.

### Save Threshold to EEPROM

```cpp
saveThresholdToEEPROM()
```

Saves the current threshold to EEPROM for persistence across power cycles.

### Increase the Threshold Value

```cpp
incrementThreshold()
```

Increases the threshold value by one and updates the stored value in EEPROM.

### Decrease the Threshold Value

```cpp
decrementThreshold()
```

Decreases the threshold value by one and updates the stored value in EEPROM.

### Get the Current Threshold Value

```cpp
getThreshold() const
```

Returns the current active threshold value, whether it’s the default or a custom-set threshold.

## Examples

- **[ActiveThresholdExample.ino](examples/ActiveThresholdExample/ActiveThresholdExample.ino)**: Demonstrates how to set up and use the library to activate or deactivate a pin based on sensor input.

## License

[This project is licensed under the UltiBlox License.](https://ultiblox.org/license)
