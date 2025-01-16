#include "MC_Keypad_I2C.h"

const char KeypadI2C::DEFAULT_KEYMAP[4][4] = {
    {'D', '#', '0', '*'},
    {'C', '9', '8', '7'},
    {'B', '6', '5', '4'},
    {'A', '3', '2', '1'}
};

KeypadI2C::KeypadI2C(uint8_t address, const char keymap[4][4])
    : pcfAddr(address), lastKey(0), lastDebounceTime(0){
        memcpy(keys, keymap, sizeof(keys));
}

void KeypadI2C::begin(){
    Wire.begin();
}

char KeypadI2C::getKey(){
    for(int row = 0; row < 4; row++){
        byte rowData = ~(1 << row);
        writePCF8574(rowData);
        delayMicroseconds(100);

        byte colData = readPCF8574() >> 4;
        for(int col = 0; col < 4; col++){
            if(!(colData & (1 << col))){
                uint32_t now = millis();
                if(now - lastDebounceTime > 150){
                    lastDebounceTime = now;
                    return keys[row][col];
                }
            }
        }
    }
    return 0;
}

void KeypadI2C::writePCF8574(byte data){
    Wire.beginTransmission(pcfAddr);
    Wire.write(data);
    Wire.endTransmission();
}

byte KeypadI2C::readPCF8574(){
    Wire.requestFrom(pcfAddr, (uint8_t)1);
    if(Wire.available()){
        return Wire.read();
    }
    return 0xFF;
}