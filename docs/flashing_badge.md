# Arduino IDE Setup

- [Download and Install the Arduino IDE](https://www.arduino.cc/en/Main/Software) for your platform.
- Obtain a USB 2.0 Male to micro B cable.

## Add ESP8266 12E Boards

Add support for our microprocessor to the Arduino IDE:

- Open the preferences window from the Arduino IDE.
  - For Windows, Go to File -> Preferences
  - For Mac, Go to Arduino -> Preferences
- Enter <http://arduino.esp8266.com/stable/package_esp8266com_index.json> into the “Additional Board Manager URLs” field.
- Go to Tools -> Board -> Boards Manager and open the "Board Manager" window.
- Scroll down, select the "esp8266 by ESP8266 Community" option and click install
- Choose the "NodeMCU 1.0 (ESP8266-12E Module)" board from Tools > Board > Generic ESP8266 Module

## Add Libraries

For Mac, Linux, or Windows:

- Click "sketch" -> "Include Library" -> "Manage Libraries"
- In the "filter" box, search for these libraries:
  - Adafruit GFX Library
  - Adafruit SSD1306
  - APA102
  - ArduinoThread

### Manually Add Libraries on Linux

Optionally, you can run these commands in Linux to install supporting libraries.
Note that a restart of Arduino IDE may be required.

```sh
cd ~/Arduino
git clone git@github.com:adafruit/Adafruit-GFX-Library.git
git clone git@github.com:adafruit/Adafruit_SSD1306.git
git clone git@github.com:pololu/apa102-arduino.git
git clone git@github.com:ivanseidel/ArduinoThread.git
```

## Make Changes

Now Open the "nola_con.ino" file in the Arduino IDE.

### Update Your Handle

On line 40 in the file "MyMenu.h", replace "@nola_con" with your handle:

```sh
const String myHandle = "@nola_con";
```

### Change Wireless Settings

## Flash the Board

### Fix Display Settings

If you get error of "Height incorrect, please fix Adafruit_SSD1306.h!":
Open Adafruit_SSD1306.h file, in the path like

```sh
"C:\Users\user\Documents\Arduino\libraries\Adafruit_SSD1306\Adafruit_SSD1306.h"
/home/thedevilsvoice/Arduino/libraries/Adafruit_SSD1306/Adafruit_SSD1306.h
```

Un-comment "#define SSD1306_128_64", and comment "#define SSD1306_128_32".
