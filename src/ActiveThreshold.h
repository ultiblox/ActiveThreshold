#ifndef ActiveThreshold_h
#define ActiveThreshold_h

#include "Arduino.h"
#include <EEPROM.h>

class ActiveThreshold {
private:
    int _defaultThreshold;
    int _setThreshold;
    bool _useSetThreshold;
    bool _isActiveHigh;
    bool _currentState;

    void (*_onActive)();
    void (*_onInactive)();

    static const int THRESHOLD_EEPROM_ADDR = 30;
    static const int THRESHOLD_FLAG_EEPROM_ADDR = 34;
    static const int EEPROM_VALID_FLAG = 0xABCD;

public:
    ActiveThreshold();

    ActiveThreshold& init();
    ActiveThreshold& setDefaultThreshold(int defaultThreshold);
    ActiveThreshold& setThreshold(int threshold);
    ActiveThreshold& setActiveHigh(bool isActiveHigh);
    ActiveThreshold& onActive(void (*callback)());
    ActiveThreshold& onInactive(void (*callback)());

    void evaluate(int value);
    ActiveThreshold& loadThresholdFromEEPROM();
    ActiveThreshold& saveThresholdToEEPROM();

    ActiveThreshold& incrementThreshold();
    ActiveThreshold& decrementThreshold();

    int getThreshold() const;




private:
    bool isValueActive(int value);
};

#endif