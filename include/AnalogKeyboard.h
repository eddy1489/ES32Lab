/*
  Autor: Eder João Santini
  WhatsApp +55 69 98463 9009
  Data de criação: 05/31/20222
*/

#ifndef _ANALOGKEYBOARD_h
#define _ANALOGKEYBOARD_h

#include <Arduino.h>

#define ANALOGKEYBOARD_VERSION "0.3.3 update 06/03/2022"    // mm/dd/yyyy
// <<<<<<<<<<<<<<< Classe AnalogKeyboard >>>>>>>>>>>>>>
class AnalogKeyboard {
  private:    
    uint8_t  _pinKeyboard;      // Keyboard read pin 
    uint16_t _addressKey[5];    // Key analog address
    boolean  _keyPress[5] = {false, false, false, false, false};      // Checks if the key is pressed
    boolean  _keyRelease[5] = {true, true, true, true, true};      // Checks if the key is release
    uint8_t  _readingAccuracy;  // Reading accuracy over established analog values
    
  public:

    // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Constructor >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    /*Constructor of the AnalogKeyboard object.
    - pinKeyboard: Pin for analogue reading of the keyboard circuit (Required);
    - addressKey0: Analog address of key 0;
    - addressKey1: Analog address of key 1;
    - addressKey2: Analog address of key 2;
    - addressKey3: Analog address of key 3;
    - addressKey4: Analog address of key 4;
    - readingAccuracy: Value in percentage to adjust the recognition accuracy of the analog reading of each key.
    */
    AnalogKeyboard(uint8_t pinKeyboard, uint16_t addressKey0 = 0, uint16_t addressKey1 = 870, uint16_t addressKey2 = 1657, uint16_t addressKey3 = 2457, uint16_t addressKey4 = 3322, uint8_t readingAccuracy = 20 ) {
        _pinKeyboard     = pinKeyboard;
        _readingAccuracy = readingAccuracy;

        _addressKey[0] = addressKey0;
        _addressKey[1] = addressKey1;
        _addressKey[2] = addressKey2;
        _addressKey[3] = addressKey3;
        _addressKey[4] = addressKey4;

    }

    // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Hold >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    /* HOLD key method.
    - Key: Number of selected key;
    */
    boolean hold(uint8_t key){
        uint16_t readValue = analogRead(_pinKeyboard);
        uint16_t toleranceValue = _addressKey[key] * (float(_readingAccuracy) / 100);

        if( ((_addressKey[key] - toleranceValue) <= readValue )  &&  ( readValue <= (_addressKey[key] + toleranceValue) )  ) { 
            return true;
        }
        return false;
    }

    // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Press >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    /* Method PRESS the key.
    - Key: Number of selected key;
    */
    boolean press(uint8_t key){
        if( !hold(key) & !_keyPress[key] ) {
            _keyPress[key] = true;
        } else if(hold(key) & _keyPress[key] ){
            _keyPress[key] = false;
            return true;
        }
        return false;
    }

    // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Release >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    /* Method RELEASE the key.
    - Key: Number of selected key;
    */  
    boolean release(uint8_t key){
        if( !hold(key) & !_keyRelease[key] ) {
            _keyRelease[key] = true;
            return true;

        } else if(hold(key) & _keyRelease[key] ){
            _keyRelease[key] = false;
        }
        return false;
    }
    // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
};
#endif
