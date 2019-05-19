/*!
   @file MyLed.h
    ____  _____      _    ____    _  ___     ____ ____
   |  _ \| ____|_   / \  |  _ \ _/ |/ _ \ _ / ___| ___|
   | | | |  _| (_) / _ \ | | | (_) | | | (_) |   |___ \
   | |_| | |___ _ / ___ \| |_| |_| | |_| |_| |___ ___) |
   |____/|_____(_)_/   \_\____/(_)_|\___/(_)\____|____/


   Author : @theDevilsVoice @p0lr_ @mzbat
   Date   : May 15, 2018
   Version: 0.5
*/

#ifndef MY_LED_H
#define MY_LED_H

#include <APA102.h>

class MyLed {
  public:
    void ledCallback();
    void cyberPolice();
    void rainbow();
    void ytCracker();
    void gradient();

    rgb_color hsvToRgb(uint16_t, uint8_t, uint8_t);
};

#endif // MY_LED_H
