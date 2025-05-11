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
 
#include "ssd1306.h"
#include "nano_gfx.h"
#include <SPI.h>
#include <APA102.h>
#include <Thread.h>
#include <ThreadController.h>

// ThreadController that will controll all threads
ThreadController controll = ThreadController();

Thread ledThread = Thread();

//define button pins
int switchPin1 = D3;              
int switchPin2 = D4;
 int switchPin3 = D7;
 int switchPin4 = D10;

//define values needed for the LED library
const uint8_t dataPin = D5;
const uint8_t clockPin = D6;
const uint16_t ledCount = 8;
rgb_color colors[ledCount];
const uint8_t brightness = 1; //max value is 31

//The number of milliseconds to debounce the buttons
const int debounce = 500;

//A global variable that holds the LED pattern that we want to display
int ledPattern = 0;

int getLedPattern() {
  return ledPattern;
}

void setLedPattern(int myLed) {
  ledPattern = myLed; 
  char ledPatternChar[64];
  String(myLed).toCharArray(ledPatternChar, 64);
  ssd1306_printFixed(0,  8, ledPatternChar, STYLE_NORMAL);
  delay(200); 
  ssd1306_clearScreen();
}

void ledCallback() {
   
  char ledPatternChar[10];
  String(ledPattern).toCharArray(ledPatternChar, 10);
  ssd1306_printFixed(0,  8, ledPatternChar, STYLE_NORMAL);
  ssd1306_clearScreen();
  if (ledPattern % 2 == 0) {
    redPulse();
  }
  else {
    bluePulse();
  }
  
}

APA102<dataPin, clockPin> ledStrip;

void button1() {
  
  int myLed = getLedPattern();
  /*
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > debounce) {
    myLed++;
    setLedPattern(myLed);
  }
  char ledPatternChar[10];
  String(interrupt_time).toCharArray(ledPatternChar, 10);
  ssd1306_printFixed(0,  8, ledPatternChar, STYLE_NORMAL);
  //ssd1306_printFixed(0,  8, interrupt_time, STYLE_NORMAL);
 */
  myLed++;
  setLedPattern(myLed);
ledCallback();

}

void button2() {
  int myLed = getLedPattern();
  /*
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > debounce) {
    ledPattern--;
  }
   */
   myLed++;
  setLedPattern(myLed);
  ledCallback();
  
}

void button3() {
  int myLed = getLedPattern();
  /*
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > debounce) {
    ledPattern--;
  }
   */
   myLed++;
  setLedPattern(myLed);
  ledCallback();
}

void button4() {
  int myLed = getLedPattern();
  /*
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > debounce) {
    ledPattern--;
  }
   */
   myLed++;
  setLedPattern(myLed);
  ledCallback();
}

void redPulse() {
  for (uint16_t redvalue = 0; redvalue <= 255; redvalue++){
    for(uint16_t led = 0; led < ledCount; led++) {
      colors[led] = rgb_color(0, 0, redvalue);
    }
    ledStrip.write(colors, ledCount, brightness);
  }
  for (uint16_t redvalue = 255; redvalue >= 0; redvalue--){
    for(uint16_t led = 0; led < ledCount; led++) {
      colors[led] = rgb_color(0, 0, redvalue);
    }
    ledStrip.write(colors, ledCount, brightness);
  }
}

void bluePulse() {
  for (uint16_t bluevalue = 0; bluevalue <= 255; bluevalue++){
    for(uint16_t led = 0; led < ledCount; led++) {
      colors[led] = rgb_color(0, bluevalue, 0);
    }
    ledStrip.write(colors, ledCount, brightness);
  }
  for (uint16_t bluevalue = 255; bluevalue >= 0; bluevalue--){
    for(uint16_t led = 0; led < ledCount; led++) {
      colors[led] = rgb_color(0, bluevalue, 0);
    }
    ledStrip.write(colors, ledCount, brightness);
  }
}



void setup() {
  pinMode(switchPin1, INPUT_PULLUP);    // Set the switch pin as input
  digitalWrite(switchPin1, HIGH); // turn on pull up resistor
  pinMode(switchPin2, INPUT_PULLUP);
  digitalWrite(switchPin2, HIGH);
  pinMode(switchPin3, INPUT_PULLUP);
  digitalWrite(switchPin3, HIGH);
  pinMode(switchPin4, INPUT_PULLUP);
  digitalWrite(switchPin4, HIGH);

  attachInterrupt(switchPin1, button1, FALLING);
  attachInterrupt(switchPin2, button2, FALLING);
  attachInterrupt(switchPin3, button3, FALLING);
  attachInterrupt(switchPin4, button4, FALLING);

  ssd1306_setFixedFont(ssd1306xled_font6x8);
  ssd1306_128x64_i2c_init();
  ssd1306_setFixedFont(ssd1306xled_font6x8);
  ssd1306_fillScreen( 0x00 );
  ssd1306_clearScreen();

  // Configure myThread
  ledThread.onRun(ledCallback);
  ledThread.setInterval(5000);
   
  // Adds threads to the controller
  controll.add(&ledThread);
}

void loop() {
  controll.run();
  
}


