/*
 *  ____  _____      _    ____    _  ___     ____ ____  
 * |  _ \| ____|_   / \  |  _ \ _/ |/ _ \ _ / ___| ___| 
 * | | | |  _| (_) / _ \ | | | (_) | | | (_) |   |___ \ 
 * | |_| | |___ _ / ___ \| |_| |_| | |_| |_| |___ ___) |
 * |____/|_____(_)_/   \_\____/(_)_|\___/(_)\____|____/ 
 *                                                    
 *                                                    
 * Author : @theDevilsVoice
 * Date   : March 31, 2018
 * Version: 0.4
 */
#ifndef MY_LED_H
  #define MY_LED_H

#include <APA102.h>

  class MyLed{
    public:
      MyLed();
      ~MyLed();
      void begin();
      void rainbow();
      void gradient();
      rgb_color hsvToRgb(uint16_t, uint8_t, uint8_t);

  };
   
#endif // MY_LED_H
