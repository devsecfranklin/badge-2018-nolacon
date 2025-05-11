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
 *
 *                           = GPIO
 * static const uint8_t D0   = 16;
 * static const uint8_t D1   = 5;
 * static const uint8_t D2   = 4;
 * static const uint8_t D3   = 0;
 * static const uint8_t D4   = 2;
 * static const uint8_t D5   = 14;
 * static const uint8_t D6   = 12;
 * static const uint8_t D7   = 13;
 * static const uint8_t D8   = 15;
 * static const uint8_t D9   = 3;
 * static const uint8_t D10  = 1;
 */
#ifndef MY_BUT_H
#define MY_BUT_H
#define UP 0 //switch 1
#define DOWN 2 //switch 2
#define ESC 13 //switch 3
#define ENTER 15 //switch 4

#include <Arduino.h>

 class MyButtons{
    public:
      MyButtons();
      ~MyButtons();
 };

#endif // MY_BUT_H
