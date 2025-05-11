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

//#include "SSD1306.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include <APA102.h>
#include <Thread.h>
#include <ThreadController.h>
#include "nola.h"


// ThreadController that will controll all threads
ThreadController controll = ThreadController();

// Create an object for writing to the LED strip.
APA102<dataPin, clockPin> ledStrip;

// Create a buffer for holding the colors (3 bytes per color).
rgb_color colors[ledCount];

Thread ledThread = Thread();
Thread screenThread = Thread();
Thread buttonThread = Thread();

String myText = "default"; 

void ledCallback() {

/*
  uint8_t time = millis() >> 4;
  for(uint16_t i = 0; i < ledCount; i++) {
    uint8_t p = time - i * 8;
    colors[i] = hsvToRgb((uint32_t)p * 359 / 256, 255, 255);
  }
  ledStrip.write(colors, ledCount, brightness);
  delay(10);
  */


  /*
  // send increasing white only
  ledStrip.startFrame();
  float power = minPower;
  for(uint16_t i = 0; i < ledCount; i++)
  {
    sendWhite(power);
    power = power * multiplier;
  }
  ledStrip.endFrame(ledCount);
  */
  //display.startscrollright(0x00, 0x0F);
  display.invertDisplay(true);
  cyberPolice();
  delay(150); 
  display.invertDisplay(false);
  //cyberPolice();
  //delay(150); 
}

void screenCallback() {
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(0,0); 
  display.println(myText);
  display.display();
}

void setup() {
  /*
  display.init();
  display.flipScreenVertically();
  delay(50);
  */
  // initialize with the I2C addr 0x3C (for the 128x32)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0); 
  // adafruit logo
  //display.drawBitmap(30, 16,  logo16_glcd_bmp, 16, 16, 1);
  //display.display();
  //delay(2000);
  display.clearDisplay();
  display.drawBitmap(0, 0,  deadlocks, 128, 64, 1);
  display.display();
  delay(2000);
  display.clearDisplay();
  display.drawBitmap(0, 0,  fdl_bmp1, 128, 64, 1);
  display.display();
  delay(2000);
  display.clearDisplay();
  display.display();
  display.setTextSize(3);
  //display.setCursor(DP_WID_MID - (3 * CH_WID * 2), DP_HEI_MID - (CH_HEI / 2)); // center
  display.print("NOLACON 2018");
  display.display();
  delay(500);
  display.setTextSize(1);
  display.clearDisplay();
  display.display();
  
  
  pinMode(switchPin1, INPUT_PULLUP);    // Set the switch pin as input
  digitalWrite(switchPin1, HIGH); // turn on pull up resistor
  pinMode(switchPin2, INPUT_PULLUP);
  digitalWrite(switchPin2, HIGH);
  pinMode(switchPin3, INPUT_PULLUP);
  digitalWrite(switchPin3, HIGH);
  pinMode(switchPin4, INPUT_PULLUP);
  digitalWrite(switchPin4, HIGH);
  pinMode(LED_BUILTIN, OUTPUT); // initialize the on-board LED
  //digitalWrite(LED_BUILTIN, HIGH);  // turn LED off

  // Configure myThread
  ledThread.onRun(ledCallback);
  ledThread.setInterval(500);

  // Configure myThread
  screenThread.onRun(screenCallback);
  screenThread.setInterval(250);

  // Configure buttonThread
  buttonThread.onRun(buttonCallback);
  buttonThread.setInterval(250);
   
  // Adds both threads to the controller
  controll.add(&ledThread);
  controll.add(&screenThread);
  controll.add(&buttonThread); 
}

void loop() {
  controll.run();
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


/*
 * Check if any button was pressed
 */
void buttonCallback() {
  if (digitalRead(switchPin1) == LOW) {               // check if the button is pressed
    button_press("1");
  } else if (digitalRead(switchPin2) == LOW) {
    button_press("2");
  } else if (digitalRead(switchPin3) == LOW) {
    button_press("3");
  } else if (digitalRead(switchPin4) == LOW) {
    button_press("4");
  }
  else {
    //Serial.println("Nothing just happened");
    //break;
  }
}

/*
 * A button was pressed, do stuff about it. 
 */
void button_press(String button_num) {
  //digitalWrite(LED_BUILTIN, LOW);   // turn LED on
  String msg;

  if (button_num.equals("1"))  {
    msg = "UP pressed";
  }
  if (button_num.equals("2"))  {
    msg = "DOWN pressed";
  }
  if (button_num.equals("3"))  {
    msg = "ENTER pressed";
  }
  if (button_num.equals("4"))  {
    msg = "ESC pressed";
  }
  
  display.setCursor(0,24);
  display.print(msg);
  display.display();

  msg = "Button " + button_num + " pressed";
  //Serial.println(msg);
  display.setCursor(0, 32);
  display.print(msg);
  display.display();
  //led_half_breath();
  //delay(100);
  //digitalWrite(LED_BUILTIN, HIGH);  // turn LED off
  digitalWrite(switchPin1, HIGH);
  digitalWrite(switchPin2, HIGH);
  digitalWrite(switchPin3, HIGH);
  digitalWrite(switchPin4, HIGH);
  delay(200);
  //display.setCursor(0, 0);
  display.clearDisplay();
  display.display();

}

// This function sends a white color with the specified power,
// which should be between 0 and 7905.
void sendWhite(uint16_t power)
{
  // Choose the lowest possible 5-bit brightness that will work.
  uint8_t brightness5Bit = 1;
  while(brightness5Bit * 255 < power && brightness5Bit < 31)
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

void cyberPolice() {
  myText = " CYBER\nPOLICE";
  for(uint16_t i = 0; i < ledCount; i++)
  {
    
    if (i%2 == 0) {
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
  
  for(uint16_t i = 0; i < ledCount; i++)
    if (i%2 != 0) {
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

