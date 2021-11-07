AVRDUDE      = /usr/bin/avrdude
AVRDUDE_CONF = /etc/avrdude.conf
# Arduino 1.5.x+ comes with it's own copy of avr tools which you can leverage in your build process 
ARDUINO_DIR = /opt/arduino-1.8.9
ARDMK_DIR = /usr/share/arduino
#AVR_TOOLS_DIR – Directory where avr tools are installed
ARCHITECTURE  = avr
BOARD_TAG    = esp8266
MONITOR_PORT  = /dev/ttyACM0
include $(ARDMK_DIR)/Arduino.mk
USER_LIB_PATH +=.
# specify space separated list of libraries that are needed for your sketch 
ARDUINO_LIBS += APA102 
