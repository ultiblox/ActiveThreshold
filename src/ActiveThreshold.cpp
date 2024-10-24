#include "ActiveThreshold.h"

ActiveThreshold::ActiveThreshold()
    : _defaultThreshold(500), _setThreshold(0), _useSetThreshold(false), 
      _isActiveHigh(true), _currentState(false), _onActive(nullptr), _onInactive(nullptr) {}

ActiveThreshold& ActiveThreshold::init() {
    return *this;
}

ActiveThreshold& ActiveThreshold::setDefaultThreshold(int defaultThreshold) {
    _defaultThreshold = defaultThreshold;
    return *this;
}

ActiveThreshold& ActiveThreshold::setThreshold(int threshold) {
    _setThreshold = threshold;
    _useSetThreshold = true;
    return *this;
}

ActiveThreshold& ActiveThreshold::setActiveHigh(bool isActiveHigh) {
    _isActiveHigh = isActiveHigh;
    return *this;
}

ActiveThreshold& ActiveThreshold::onActive(void (*callback)()) {
    _onActive = callback;
    return *this;
}

ActiveThreshold& ActiveThreshold::onInactive(void (*callback)()) {
    _onInactive = callback;
    return *this;
}

void ActiveThreshold::evaluate(int value) {
    bool isActive = isValueActive(value);
    if (isActive != _currentState) {
        _currentState = isActive;
        if (isActive && _onActive) {
            _onActive();
        } else if (!isActive && _onInactive) {
            _onInactive();
        }
    }
}

bool ActiveThreshold::isValueActive(int value) {
    int threshold = _useSetThreshold ? _setThreshold : _defaultThreshold;
    return _isActiveHigh ? (value >= threshold) : (value < threshold);
}

ActiveThreshold& ActiveThreshold::loadThresholdFromEEPROM() {
    int flag;
    EEPROM.get(THRESHOLD_FLAG_EEPROM_ADDR, flag);
    if (flag == EEPROM_VALID_FLAG) {
        EEPROM.get(THRESHOLD_EEPROM_ADDR, _setThreshold);
        _useSetThreshold = true;
    }
    return *this;
}

ActiveThreshold& ActiveThreshold::saveThresholdToEEPROM() {
    EEPROM.put(THRESHOLD_EEPROM_ADDR, _setThreshold);
    int flag = EEPROM_VALID_FLAG;
    EEPROM.put(THRESHOLD_FLAG_EEPROM_ADDR, flag);
    return *this;
}

ActiveThreshold& ActiveThreshold::incrementThreshold() {
    _setThreshold++;
    saveThresholdToEEPROM();
    return *this;
}

ActiveThreshold& ActiveThreshold::decrementThreshold() {
    _setThreshold--;
    saveThresholdToEEPROM();
    return *this;
}

int ActiveThreshold::getThreshold() const {
    return _useSetThreshold ? _setThreshold : _defaultThreshold;
}


