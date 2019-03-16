/*!
 * @file nola_con.ino
    ____  _____      _    ____    _  ___     ____ ____
   |  _ \| ____|_   / \  |  _ \ _/ |/ _ \ _ / ___| ___|
   | | | |  _| (_) / _ \ | | | (_) | | | (_) |   |___ \
   | |_| | |___ _ / ___ \| |_| |_| | |_| |_| |___ ___) |
   |____/|_____(_)_/   \_\____/(_)_|\___/(_)\____|____/


   Author : @theDevilsVoice @p0lr_ @mzbat @dead10c5
   Date   : May 26, 2018
   Version: 0.5
*/


#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <APA102.h>

#include "nola.h"
#include "MyGame.h"
#include "MyLed.h"
#include "MyMenu.h"
#include "MyNetwork.h"

// Initialize instance of MyNetwork() class
MyNetwork mynetwork;
MyMenu mymenu;
MyGame mygame;
MyLed myled;

//SSD1306 display(0x3c, D2, D1);
#define OLED_RESET 2
Adafruit_SSD1306 display(OLED_RESET);

/*
#if (SSD1306_LCDHEIGHT != 64)
#pragma message("Height incorrect, please fix Adafruit_SSD1306.h!")
#endif
*/

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

  mymenu.inv = 1;
  mymenu.page = 1;
  mymenu.total = 3;

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

  // display main menu page
  if (mymenu.page == 1) {
    display.setCursor(0, 0);
    if (mymenu.inv == 1) {
      display.setTextColor(BLACK, WHITE);
      display.println("bling");
      display.setTextColor(WHITE);
    } else {
      display.println("bling");
    }
    if (mymenu.inv == 2) {
      display.setTextColor(BLACK, WHITE);
      display.println("games");
      display.setTextColor(WHITE);
    } else {
      display.println("games");
    }
    if (mymenu.inv == 3) {
      display.setTextColor(BLACK, WHITE);
      display.println("network");
      display.setTextColor(WHITE);
    } else {
      display.println("network");
    }
    if (mymenu.inv == 4) {
      display.setTextColor(BLACK, WHITE);
      display.println("about");
      display.setTextColor(WHITE);
    } else {
      display.println("about");
    }
    display.display();
  }  // page1

  // all the bling
  if (mymenu.page == 2) {
    display.setCursor(0, 0);
    if (mymenu.inv == 1) {
      display.setTextColor(BLACK, WHITE);
      display.println("Cyber Police");
      display.setTextColor(WHITE);
    } else {
      display.println("Cyber Police");
    }
    if (mymenu.inv == 2) {
      display.setTextColor(BLACK, WHITE);
      display.println("rainbow");
      display.setTextColor(WHITE);
    } else {
      display.println("rainbow");
    }
    if (mymenu.inv == 3) {
      display.setTextColor(BLACK, WHITE);
      display.println("white");
      display.setTextColor(WHITE);
    } else {
      display.println("white");
    }
    if (mymenu.inv == 4) {
      display.setTextColor(BLACK, WHITE);
      display.println("gradient");
      display.setTextColor(WHITE);
    } else {
      display.println("gradient");
    }
    /*
      if (mymenu.inv == 5) {
      display.setTextColor(BLACK, WHITE);
      display.println("next");
      display.setTextColor(WHITE);
      } else {
      display.println("next");
      }
    */
    display.display();
  }  // page2

  //network
  if (mymenu.page == 3) {
    display.setCursor(0, 0);
    if (mymenu.inv == 1) {
      display.setTextColor(BLACK, WHITE);
      display.println("wifi scan");
      display.setTextColor(WHITE);
    } else {
      display.println("wifi scan");
    }
    if (mymenu.inv == 2) {
      display.setTextColor(BLACK, WHITE);
      display.println("mqtt");
      display.setTextColor(WHITE);
    } else {
      display.println("mqtt");
    }
    if (mymenu.inv == 3) {
      display.setTextColor(BLACK, WHITE);
      display.println("desync");
      display.setTextColor(WHITE);
    } else {
      display.println("desync");
    }
    //display.println(mymenu.inv);
    display.display();
  }

  // games
  if (mymenu.page == 4) {
    display.setCursor(0, 0);
    if (mymenu.inv == 1) {
      display.setTextColor(BLACK, WHITE);
      display.println("burgess pong");
      display.setTextColor(WHITE);
    } else {
      display.println("burgess pong");
    }
    display.display();
  }

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
  if (my_butt == 1 && mymenu.inv > 1) {
    mymenu.inv -= 1;
    return 0;
  }

  // DOWN button pressed
  if (my_butt == 2 && mymenu.inv < mymenu.total) {
    mymenu.inv++;
    return 0;
  }
  // BACK button pressed
  if (my_butt == 3 && mymenu.page > 1) {
    mymenu.page = 1;
    return 0;
  }
  // enter button pressed
  if (my_butt == 4) {
    if (mymenu.page == 1 && mymenu.inv == 1) {
      // page 2 (bling)
      mymenu.page++;
      mymenu.inv = 1;   // set to invert first item
      mymenu.total = 4; // match number of items in bling menu
      return 0;
    }
    if (mymenu.page == 1 && mymenu.inv == 2) {
      // page 3 (games)
      mymenu.page = 3;
      mymenu.inv = 1;     // set to invert first item
      mymenu.total = 1;  //match number of items in games menu
      return 0;
    }
    if (mymenu.page == 1 && mymenu.inv == 3) {
      // page 4 (network)
      mymenu.page = 4;
      mymenu.inv = 1;     // set to invert first item
      mymenu.total = 3;  //match number of items in network menu
      return 0;
    }
    if (mymenu.page == 1 && mymenu.inv == 4) {
      // call the about() function
      about();
      return 0;
    }

    /*
      if (mymenu.page == 1 && mymenu.inv == 4) {
       // page 4 (network)
       mymenu.page = 4;
       mymenu.inv = 1;
       return 0;
      }
    */

    // ************* led pattern selection ***********
    if (mymenu.page == 2 && mymenu.inv == 1) {
      mymenu.ledpattern = 1;
      //ledCallback();
      return 0;
    }
    if (mymenu.page == 2 && mymenu.inv == 2) {
      mymenu.ledpattern = 2;
      //ledCallback();
      return 0;
    }
    if (mymenu.page == 2 && mymenu.inv == 3) {
      mymenu.ledpattern = 3;
      //ledCallback();
      return 0;
    }
    if (mymenu.page == 2 && mymenu.inv == 4) {
      mymenu.ledpattern = 5; // gradient pattern
      //ledCallback();
      return 0;
    }

    // ************* game selection ***********
    if (mymenu.page == 3 && mymenu.inv == 1) {
      mygame.burgess_pong(&display);
      return 0;
    }

    // ************* network tool selection ***********
    if (mymenu.page == 4 && mymenu.inv == 1) {
      // wireless scanner
      return 0;
    }
    // ************* network tool selection ***********
    if (mymenu.page == 4 && mymenu.inv == 2) {
      // mqtt
      return 0;
    }
    if (mymenu.page == 4 && mymenu.inv == 3) {
      // desync
      return 0;
    }
  }

} // button_press()

/*
   The buttons will break you out of the current LED pattern
*/

int break_butts() {
  if (digitalRead(switchPin1) == LOW) {               // check if the button is pressed
    // reset menu
    mymenu.inv == 1;
    mymenu.page == 1;
    // turn off LED pattern
    mymenu.ledpattern = 4;
    ledCallback();
    button_press("1");
    return 1;
  } else if (digitalRead(switchPin2) == LOW) {
    mymenu.inv == 1;
    mymenu.page == 1;
    mymenu.ledpattern = 4;
    ledCallback();
    button_press("2");
    return 1;
  } else if (digitalRead(switchPin3) == LOW) {
    mymenu.inv == 1;
    mymenu.page == 1;
    mymenu.ledpattern = 4;
    ledCallback();
    button_press("3");
    return 1;
  } else if (digitalRead(switchPin4) == LOW) {
    mymenu.inv == 1;
    mymenu.page == 1;
    mymenu.ledpattern = 4;
    ledCallback();
    button_press("4");
    return 1;
  } else {
    return 0;
  }

  //return 0;

} //break_butts()

void ledCallback() {

  if (mymenu.ledpattern == 1) {
    cyberPolice();
  }

  if (mymenu.ledpattern == 2) {
    rainbow();
  }

  // send increasing white only
  if (mymenu.ledpattern == 3) {
    ytCracker();
  }

  // turn off leds
  if (mymenu.ledpattern == 4) {
    for (uint16_t i = 0; i < ledCount; i++) {
      colors[i] = myled.hsvToRgb(0, 0, 0);
    }
    ledStrip.write(colors, ledCount, 0);
  }

  // random solid colors
  if (mymenu.ledpattern == 5) {
    gradient();
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




