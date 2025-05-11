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
#include "MyDisplay.h"

  #define OLED_RESET 2
  Adafruit_SSD1306 display(OLED_RESET);

  #if (SSD1306_LCDHEIGHT != 64)
  #error("Height incorrect, please fix Adafruit_SSD1306.h!");
  #endif

// class constructor
MyDisplay::MyDisplay() {
  //display.init();
  //display.flipScreenVertically();

  // initialize with the I2C addr 0x3C (for the 128x32)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  
  display.clearDisplay();
  //display.setTextSize(1);
  //display.setTextColor(WHITE);
  //display.setCursor(0,0);
}

//<<destructor>>
MyDisplay::~MyDisplay(){/*nothing to destruct*/}

void MyDisplay::begin(){
  Serial.println( "Called MyDisplay::begin" );
}


/* https://learn.adafruit.com/monochrome-oled-breakouts/arduino-library-and-examples
 *  https://image.online-convert.com/convert-to-bmp  (convert to mono bmp)
 *  http://en.radzio.dxp.pl/bitmap_converter/
 */
void MyDisplay::showNolaLogo(){
  Serial.println( "Laissez Les Pwn Temps Rouler" );
  display.clearDisplay();
  display.drawBitmap(0, 0,  fdl_bmp1, 128, 64, 1);
  //display.drawBitmap(0, 0,  fdl_bmp2, 128, 64, 1);
  display.display();
  delay(750);
}

void MyDisplay::showDeadlocksLogo(){
  Serial.println( "Called MyDisplay::showDeadlocksLogo" );
  display.clearDisplay();
  display.drawBitmap(0, 0,  fdl_bmp2, 128, 64, 1);
  display.display();
  delay(750);
}

void MyDisplay::clearMyDisplay(){
  display.clearDisplay();
  display.display();
}

void MyDisplay::updateMyDisplay(int16_t x, int16_t y, String text){
  Serial.println( "Called MyDisplay::updateMyDisplay" );
  display.println(text);
  display.display();
}

