/*!
   @file MyGame.cpp
    ____  _____      _    ____    _  ___     ____ ____
   |  _ \| ____|_   / \  |  _ \ _/ |/ _ \ _ / ___| ___|
   | | | |  _| (_) / _ \ | | | (_) | | | (_) |   |___ \
   | |_| | |___ _ / ___ \| |_| |_| | |_| |_| |___ ___) |
   |____/|_____(_)_/   \_\____/(_)_|\___/(_)\____|____/


   Author : @theDevilsVoice @p0lr_ @mzbat
   Date   : May 15, 2018
   Version: 0.6
*/
#include "MyGame.h"
#include "MyNetwork.h"

void MyGame::drawCourt(Adafruit_SSD1306 *display) {
  display->drawRect(0, 0, 128, 64, WHITE);
}

void MyGame::setup(Adafruit_SSD1306 *display) {

  // turn off wifi
  WiFi.softAPdisconnect (true);
  WiFi.mode(WIFI_OFF);
  
  // Display the splash screen (we're legally required to do so)
  display->display();
  unsigned long start = millis();

  display->clearDisplay();
  drawCourt(display);

  while (millis() - start < 2000);

  display->display();

  ball_update = millis();
  paddle_update = ball_update;

}

void MyGame::burgess_pong(Adafruit_SSD1306 *display) {

  setup(display);
   while (1) { 
  bool update = false;
  unsigned long time = millis();

  static bool up_state = false;
  static bool down_state = false;


    up_state |= (digitalRead(switch1) == LOW);
    down_state |= (digitalRead(switch2) == LOW);

    if (time > ball_update) {
      uint8_t new_x = ball_x + ball_dir_x;
      uint8_t new_y = ball_y + ball_dir_y;
  
      // Check if we hit the vertical walls
      if (new_x == 0 || new_x == 127) {
        ball_dir_x = -ball_dir_x;
        new_x += ball_dir_x + ball_dir_x;
      }
  
      // Check if we hit the horizontal walls.
      if (new_y == 0 || new_y == 63) {
        ball_dir_y = -ball_dir_y;
        new_y += ball_dir_y + ball_dir_y;
      }
  
      // Check if we hit the CPU paddle
      if (new_x == CPU_X && new_y >= cpu_y && new_y <= cpu_y + PADDLE_HEIGHT) {
        ball_dir_x = -ball_dir_x;
        new_x += ball_dir_x + ball_dir_x;
      }
  
      // Check if we hit the player paddle
      if (new_x == PLAYER_X
          && new_y >= player_y
          && new_y <= player_y + PADDLE_HEIGHT)
      {
        ball_dir_x = -ball_dir_x;
        new_x += ball_dir_x + ball_dir_x;
      }
  
      display->drawPixel(ball_x, ball_y, BLACK);
      display->drawPixel(new_x, new_y, WHITE);
      ball_x = new_x;
      ball_y = new_y;
  
      ball_update += BALL_RATE;
  
      update = true;
    }
  
    if (time > paddle_update) {
      paddle_update += PADDLE_RATE;
  
      // CPU paddle
      display->drawFastVLine(CPU_X, cpu_y, PADDLE_HEIGHT, BLACK);
      const uint8_t half_paddle = PADDLE_HEIGHT >> 1;
      if (cpu_y + half_paddle > ball_y) {
        cpu_y -= 1;
      }
      if (cpu_y + half_paddle < ball_y) {
        cpu_y += 1;
      }
      if (cpu_y < 1) cpu_y = 1;
      if (cpu_y + PADDLE_HEIGHT > 63) cpu_y = 63 - PADDLE_HEIGHT;
      display->drawFastVLine(CPU_X, cpu_y, PADDLE_HEIGHT, WHITE);
  
      // Player paddle
      display->drawFastVLine(PLAYER_X, player_y, PADDLE_HEIGHT, BLACK);
      if (up_state) {
        player_y -= 1;
      }
      if (down_state) {
        player_y += 1;
      }
      up_state = down_state = false;
      if (player_y < 1) player_y = 1;
      if (player_y + PADDLE_HEIGHT > 63) player_y = 63 - PADDLE_HEIGHT;
      display->drawFastVLine(PLAYER_X, player_y, PADDLE_HEIGHT, WHITE);
  
      update = true;
    }
    if (update)
      display->display();
  }
}

