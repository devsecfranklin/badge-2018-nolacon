/*
 *  ____  _____      _    ____    _  ___     ____ ____  
 * |  _ \| ____|_   / \  |  _ \ _/ |/ _ \ _ / ___| ___| 
 * | | | |  _| (_) / _ \ | | | (_) | | | (_) |   |___ \ 
 * | |_| | |___ _ / ___ \| |_| |_| | |_| |_| |___ ___) |
 * |____/|_____(_)_/   \_\____/(_)_|\___/(_)\____|____/ 
 *                                                    
 *                                                    
 * Author : @p0lr_ @mzbat @dead10c5 @theDevilsVoice
 * Date   : March 31, 2018
 * Version: 0.4
 */

#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include <APA102.h>
#include "deadlocks.h"

// Create an object for writing to the LED strip.
APA102<dataPin, clockPin> ledStrip;

void setup() {

  pinMode(switchPin1,INPUT_PULLUP);
  pinMode(switchPin2,INPUT_PULLUP);
  pinMode(switchPin3,INPUT_PULLUP);
  pinMode(switchPin4,INPUT_PULLUP);
  
  // initialize with the I2C addr 0x3C (for the 128x32)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
  display.setRotation(2); 
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0); 
  display.clearDisplay();
  display.drawBitmap(0, 0,  deadlocks, 128, 64, 1);
  display.display();
  delay(2000);
  display.clearDisplay();
  display.drawBitmap(0, 0,  fdl_bmp1, 128, 64, 1);
  display.display();
  delay(2000);
  display.clearDisplay();
  display.clearDisplay();
  display.display();
}

void loop() {

  uint8_t time = millis() >> 4;
  for(uint16_t i = 0; i < ledCount; i++) {
    uint8_t p = time - i * 8;
    colors[i] = hsvToRgb((uint32_t)p * 359 / 256, 255, 255);
  }
  ledStrip.write(colors, ledCount, brightness);
  //delay(10);

  if (digitalRead(switchPin1) == LOW) {               // check if the button is pressed
    button_press("1");
  } else if (digitalRead(switchPin2) == LOW) {
    button_press("2");
  } else if (digitalRead(switchPin3) == LOW) {
    button_press("3");
  } else if (digitalRead(switchPin4) == LOW) {
    button_press("4");
  } else {
  String msg = "Press any button";
  //Serial.println(msg);
  display.setCursor(0, 0);
  display.println(msg);
  display.display();
  }
}

/* Converts a color from HSV to RGB.
 * h is hue, as a number between 0 and 360.
 * s is the saturation, as a number between 0 and 255.
 * v is the value, as a number between 0 and 255. */
rgb_color hsvToRgb(uint16_t h, uint8_t s, uint8_t v)
{
    uint8_t f = (h % 60) * 255 / 60;
    uint8_t p = (255 - s) * (uint16_t)v / 255;
    uint8_t q = (255 - f * (uint16_t)s / 255) * (uint16_t)v / 255;
    uint8_t t = (255 - (255 - f) * (uint16_t)s / 255) * (uint16_t)v / 255;
    uint8_t r = 0, g = 0, b = 0;
    switch((h / 60) % 6){
        case 0: r = v; g = t; b = p; break;
        case 1: r = q; g = v; b = p; break;
        case 2: r = p; g = v; b = t; break;
        case 3: r = p; g = q; b = v; break;
        case 4: r = t; g = p; b = v; break;
        case 5: r = v; g = p; b = q; break;
    }
    return rgb_color(r, g, b);
}

void button_press(String button_num) {
  //digitalWrite(LED_BUILTIN, LOW);   // turn LED on
  String msg = "Button " + button_num + " pressed";
  //Serial.println(msg);
  display.setCursor(0, 8);
  display.println(msg);
  display.display();
  //led_half_breath();
  delay(100);
  //digitalWrite(LED_BUILTIN, HIGH);  // turn LED off
  digitalWrite(switchPin1, HIGH);
  digitalWrite(switchPin2, HIGH);
  digitalWrite(switchPin3, HIGH);
  digitalWrite(switchPin4, HIGH);
  //delay(20);
  display.setCursor(0, 0);
  display.clearDisplay();
  display.display();

}
