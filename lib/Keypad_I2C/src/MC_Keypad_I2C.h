#ifndef MC_KEYPAD_I2C_H
#define MC_KEYPAD_I2C_H

#include <Arduino.h>
#include <Wire.h>

class KeypadI2C{
public:
    static const char DEFAULT_KEYMAP[4][4];

    KeypadI2C(uint8_t address, const char keymap[4][4] = DEFAULT_KEYMAP);

    void begin();
    char getKey();

private:
    uint8_t pcfAddr;
    char keys[4][4];
    uint8_t lastKey;
    uint32_t lastDebounceTime;

    void writePCF8574(byte data);
    byte readPCF8574();
};

#endif