/*!
   @file MyGame.h
    ____  _____      _    ____    _  ___     ____ ____
   |  _ \| ____|_   / \  |  _ \ _/ |/ _ \ _ / ___| ___|
   | | | |  _| (_) / _ \ | | | (_) | | | (_) |   |___ \
   | |_| | |___ _ / ___ \| |_| |_| | |_| |_| |___ ___) |
   |____/|_____(_)_/   \_\____/(_)_|\___/(_)\____|____/


   Author : @theDevilsVoice @p0lr_ @mzbat
   Date   : May 15, 2018
   Version: 0.5
*/

#ifndef MY_GAME_H
#define MY_GAME_H

#include "Arduino.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "nola.h"



class MyGame {
  public:
    int switch1 = 0;         // UP     D3
    int switch2 = 2;         // DOWN   D4
    int switch3 = 13;        // BACK   D7
    int switch4 = 1;         // ENTER  D10

    void drawCourt(Adafruit_SSD1306 *display);
    void setup(Adafruit_SSD1306 *display);
    void burgess_pong(Adafruit_SSD1306 *display);

  private:
    // ******************* burgess pong game *********************
    // shamelssly stolen from:  https://github.com/eholk/Arduino-Pong/blob/master/pong.ino
    const unsigned long PADDLE_RATE = 33;
    const unsigned long BALL_RATE = 16;
    const uint8_t PADDLE_HEIGHT = 24;

    uint8_t ball_x = 64, ball_y = 32;
    uint8_t ball_dir_x = 1, ball_dir_y = 1;
    unsigned long ball_update;

    unsigned long paddle_update;
    const uint8_t CPU_X = 12;
    uint8_t cpu_y = 16;

    const uint8_t PLAYER_X = 115;
    uint8_t player_y = 16;
    // ******************* burgess pong game *********************
};
#endif // MY_GAME_H
