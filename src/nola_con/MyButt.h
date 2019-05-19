/*!
 * @file MyButt.h
    ____  _____      _    ____    _  ___     ____ ____
   |  _ \| ____|_   / \  |  _ \ _/ |/ _ \ _ / ___| ___|
   | | | |  _| (_) / _ \ | | | (_) | | | (_) |   |___ \
   | |_| | |___ _ / ___ \| |_| |_| | |_| |_| |___ ___) |
   |____/|_____(_)_/   \_\____/(_)_|\___/(_)\____|____/


   Author : @theDevilsVoice @p0lr_ @mzbat
   Date   : May 15, 2018
   Version: 0.5
*/
#ifndef MY_BUTT_H
#define MY_BUTT_H

#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include "MyGame.h"
#include "MyMenu.h"
#include "nola.h"

class MyButt {
  private:
    // switch pins
    const int switchPin1 = 0;         // UP     D3   
    const int switchPin2 = 2;         // DOWN   D4
    const int switchPin3 = 13;        // BACK   D7
    const int switchPin4 = 1;         // ENTER  D10
  public:
    int button_press(String button_num,
                     MyGame *mygame,
                     MyMenu *mymenu,
                     Nola *mynola,
                     Adafruit_SSD1306 *display);
    int break_butts(MyMenu *mymenu);
};

#endif // MY_BUTT_H
