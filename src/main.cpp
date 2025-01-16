#include <Arduino.h>
#include <Wire.h>
#include "MC_Keypad_I2C.h"

KeypadI2C keypad(0x21);

void setup(){
  Serial.begin(115200);
  keypad.begin();
  Serial.print("Test Begin...");
}

void loop(){
  char key = keypad.getKey();
  if(key){
    Serial.print("Key Pressed ");
    Serial.println(key);
  }
}