/*!
 * @file nola_con.ino
    ____  _____      _    ____    _  ___     ____ ____
   |  _ \| ____|_   / \  |  _ \ _/ |/ _ \ _ / ___| ___|
   | | | |  _| (_) / _ \ | | | (_) | | | (_) |   |___ \
   | |_| | |___ _ / ___ \| |_| |_| | |_| |_| |___ ___) |
   |____/|_____(_)_/   \_\____/(_)_|\___/(_)\____|____/


   Author : @theDevilsVoice @p0lr_ @mzbat @dead10c5
   Date   : May 26, 2018
   Version: 0.6
*/


#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <APA102.h>

#include "nola.h"
#include "MyLed.h"
#include "MyMenu.h"
#include "MyNetwork.h"

// Initialize instance of MyNetwork() class
MyNetwork mynetwork;
MyMenu mymenu;
MyLed myled;

//SSD1306 display(0x3c, D2, D1);
#define OLED_RESET 2
Adafruit_SSD1306 display(OLED_RESET);

#define CLR(x,y) (x&=(~(1<<y)))
#define SET(x,y) (x|=(1<<y))

// Create an object for writing to the LED strip.
APA102<dataPin, clockPin> ledStrip;

// Create a buffer for holding the colors (3 bytes per color).
rgb_color colors[ledCount];

void setup() {

  // initialize with the I2C addr 0x3C (for the 128x32)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setRotation(2);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);

  // deadlocks logo
  display.clearDisplay();
  display.drawBitmap(0, 0,  deadlocks, 128, 64, 1);
  display.display();
  delay(2000);

  // nolacon logo
  display.clearDisplay();
  display.drawBitmap(0, 0,  fdl_bmp1, 128, 64, 1);
  display.display();
  delay(2000);
  display.clearDisplay();
  display.display();

  pinMode(switchPin1, INPUT_PULLUP);
  pinMode(switchPin2, INPUT_PULLUP);
  pinMode(switchPin3, INPUT_PULLUP);
  pinMode(switchPin4, INPUT_PULLUP);

  mymenu.inv = 0;
  mymenu.page = 0;

}

void loop() {

   // check if any button is pressed
  if (digitalRead(switchPin1) == LOW) {               
    button_press("1");
  } else if (digitalRead(switchPin2) == LOW) {
    button_press("2");
  } else if (digitalRead(switchPin3) == LOW) {
    button_press("3");
  } else if (digitalRead(switchPin4) == LOW) {
    button_press("4");
  } else {
    //do nothing
  }

  show_menu();
}

void show_menu () {

  display.setTextSize(1);
  display.setCursor(0, 0);
  for(int a = 0; a < 5; a = a + 1 ){
    char *curr_item = new char[32];
    mymenu.my_menu[mymenu.page][a].toCharArray(curr_item, 32);
    if (!(curr_item == NULL) || !(*curr_item == '\0')) {
      if (mymenu.inv == a) {
        display.setTextColor(BLACK, WHITE);
        display.println(mymenu.my_menu[mymenu.page][a]);
        display.setTextColor(WHITE);
      } else {
        display.println(mymenu.my_menu[mymenu.page][a]);
      }
    }
  }
  display.display();

} // show_menu()

int button_press(String button_num) {

  display.setCursor(0, 0);
  display.clearDisplay();
  display.display();

  digitalWrite(switchPin1, HIGH);  // UP
  digitalWrite(switchPin2, HIGH);  // DOWN
  digitalWrite(switchPin3, HIGH);  // BACK
  digitalWrite(switchPin4, HIGH);  // ENTER

  int my_butt = button_num.toInt();

  // UP button pressed
  if (my_butt == 1 && mymenu.inv > 0) {
    mymenu.inv -= 1;
    return 0;
  }

  // DOWN button pressed
  if (my_butt == 2) {
    mymenu.inv++;
    return 0;
  }
  // BACK button pressed
  if (my_butt == 3 && mymenu.page > 0) {
    mymenu.page = 0;
    return 0;
  }
  // enter button pressed

  if (my_butt == 4) {

    /*
    for (int b = 0; b < 4; b = b++ ){
      mymenu.page
      mymenu.inv
    } */
    
    if (mymenu.page == 0 && mymenu.inv == 0) {
      // page 2 (bling)
      mymenu.page++;
      mymenu.inv = 0;   // set to invert first item
      return 0;
    }
    if (mymenu.page == 0 && mymenu.inv == 1) {
      // page 3 (network)
      mymenu.page = 3;
      mymenu.inv = 0;     // set to invert first item
      //mymenu.total = 1;  //match number of items in games menu
      return 0;
    }
    if (mymenu.page == 0 && mymenu.inv == 3) {
      // call the about() function
      about();
      return 0;
    }

    // ************* led pattern selection ***********
    if (mymenu.page == 1 && mymenu.inv == 0) {
      mymenu.ledpattern = 0;
      ledCallback();
      return 0;
    }
    if (mymenu.page == 1 && mymenu.inv == 1) {
      mymenu.ledpattern = 1;
      ledCallback();
      return 0;
    }
    if (mymenu.page == 1 && mymenu.inv == 2) {
      mymenu.ledpattern = 2;
      ledCallback();
      return 0;
    }
    if (mymenu.page == 1 && mymenu.inv == 3) {
      mymenu.ledpattern = 3; // gradient pattern
      ledCallback();
      return 0;
    }

    // ************* network tool selection ***********
    if (mymenu.page == 2 && mymenu.inv == 0) {
      // wireless scanner
      return 0;
    }
    // ************* network tool selection ***********
    if (mymenu.page == 2 && mymenu.inv == 1) {
      // mqtt
      return 0;
    }
    if (mymenu.page == 2 && mymenu.inv == 2) {
      // desync
      return 0;
    }
  }
} // button_press()

/*
 *  The buttons will break you out of the current LED pattern
 */

int break_butts() {
  if (digitalRead(switchPin1) == LOW) {               // check if the button is pressed
    // reset menu
    mymenu.inv == 0;
    mymenu.page == 0;
    // turn off LED pattern
    mymenu.ledpattern = 4;
    ledCallback();
    button_press("1");
    return 1;
  } else if (digitalRead(switchPin2) == LOW) {
    mymenu.inv == 0;
    mymenu.page == 0;
    mymenu.ledpattern = 4;
    ledCallback();
    button_press("2");
    return 1;
  } else if (digitalRead(switchPin3) == LOW) {
    mymenu.inv == 0;
    mymenu.page == 0;
    mymenu.ledpattern = 4;
    ledCallback();
    button_press("3");
    return 1;
  } else if (digitalRead(switchPin4) == LOW) {
    mymenu.inv == 0;
    mymenu.page == 0;
    mymenu.ledpattern = 4;
    ledCallback();
    button_press("4");
    return 1;
  } else {
    return 0;
  }

} //break_butts()

void ledCallback() {

  if (mymenu.ledpattern == 0) {
    cyberPolice();
  }

  if (mymenu.ledpattern == 1) {
    rainbow();
  }

  // send increasing white only
  if (mymenu.ledpattern == 2) {
    ytCracker();
  }

  // random solid colors
  if (mymenu.ledpattern == 3) {
    gradient();
  }
  // turn off leds
  if (mymenu.ledpattern == 4) {
    for (uint16_t i = 0; i < ledCount; i++) {
      colors[i] = myled.hsvToRgb(0, 0, 0);
    }
    ledStrip.write(colors, ledCount, 0);
  }
  
} // ledCallback()


void cyberPolice() {
  yield();
  mymenu.myText = " CYBER\nPOLICE";
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println(mymenu.myText);
  display.display();

  while (break_butts() == 0) {

    for (uint16_t i = 0; i < ledCount; i++)
    {
      if (i % 2 == 0) {
        //uint8_t x = time - i * 8;
        colors[i].red = 0;
        colors[i].green = 0;
        colors[i].blue = 255;
      } else {
        colors[i].red = 0;
        colors[i].green = 255;
        colors[i].blue = 0;
      }

    }
    ledStrip.write(colors, ledCount, 10);
    delay(200);

    for (uint16_t i = 0; i < ledCount; i++)
      if (i % 2 != 0) {
        //uint8_t x = time - i * 8;
        colors[i].red = 0;
        colors[i].green = 0;
        colors[i].blue = 255;
      } else {
        colors[i].red = 0;
        colors[i].green = 255;
        colors[i].blue = 0;
      }
    ledStrip.write(colors, ledCount, 5);
    delay(200);
  }
}

void rainbow() {
  yield();
  mymenu.myText = "   Laissez\n   les bon\n     temps\n    roulez";
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println(mymenu.myText);
  display.display();

  while (break_butts() == 0) {

    uint8_t time = millis() >> 4;
    for (uint16_t i = 0; i < ledCount; i++) {
      uint8_t p = time - i * 8;
      colors[i] = myled.hsvToRgb((uint32_t)p * 359 / 256, 255, 255);
    }
    ledStrip.write(colors, ledCount, brightness);
    delay(10);
  }
}

void ytCracker() {
  yield();
  mymenu.myText = "   Laissez\n   les bon\n     temps\n    roulez";
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println(mymenu.myText);
  display.display();

  while (break_butts() == 0) {
    ledStrip.startFrame();
    float power = minPower;
    for (uint16_t i = 0; i < ledCount; i++)
    {
      sendWhite(power);
      power = power * multiplier;
    }
    ledStrip.endFrame(ledCount);
  }
}

void gradient() {
  yield();
  mymenu.myText = "   Laissez\n   les bon\n     temps\n    roulez";
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println(mymenu.myText);
  display.display();

  while (break_butts() == 0) {
    uint8_t time = millis() >> 2;
    for (uint16_t i = 0; i < ledCount; i++) {
      uint8_t x = time - i * 8;
      colors[i] = rgb_color(x, 255 - x, x);
    }
    ledStrip.write(colors, ledCount, brightness);
  }
}

void about() {
  while (break_butts() == 0) {
    yield();
    display.clearDisplay();
    display.setTextSize(0.5);
    display.setCursor(0, 0);
    display.setTextColor(BLACK, WHITE);
    display.println("Created by the\n DE:AD:10:C5\n");
    display.setTextColor(WHITE);
    display.println("Version: " + version );
    display.println("\n@mzbat");
    display.println("@p0lr_");
    display.println("@theDevilsVoice");
    display.display();
  }
}

// This function sends a white color with the specified power,
// which should be between 0 and 7905.
void sendWhite(uint16_t power)
{
  // Choose the lowest possible 5-bit brightness that will work.
  uint8_t brightness5Bit = 1;
  while (brightness5Bit * 255 < power && brightness5Bit < 31)
  {
    brightness5Bit++;
  }

  // Uncomment this line to simulate an LED strip that does not
  // have the extra 5-bit brightness register.  You will notice
  // that roughly the first third of the LED strip turns off
  // because the brightness8Bit equals zero.
  //brightness = 31;

  // Set brightness8Bit to be power divided by brightness5Bit,
  // rounded to the nearest whole number.
  uint8_t brightness8Bit = (power + (brightness5Bit / 2)) / brightness5Bit;

  // Send the white color to the LED strip.  At this point,
  // brightness8Bit multiplied by brightness5Bit should be
  // approximately equal to power.
  ledStrip.sendColor(brightness8Bit, brightness8Bit, brightness8Bit, brightness5Bit);
}
