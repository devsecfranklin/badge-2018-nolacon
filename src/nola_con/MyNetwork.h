/*!
 * @file MyNetwork.h
 *  ____  _____      _    ____    _  ___     ____ ____  
 * |  _ \| ____|_   / \  |  _ \ _/ |/ _ \ _ / ___| ___| 
 * | | | |  _| (_) / _ \ | | | (_) | | | (_) |   |___ \ 
 * | |_| | |___ _ / ___ \| |_| |_| | |_| |_| |___ ___) |
 * |____/|_____(_)_/   \_\____/(_)_|\___/(_)\____|____/ 
 *                                                    
 *                                                    
 * Author : @theDevilsVoice @p0lr_ @mzbat
 * Date   : May 26, 2018
 * Version: 0.5
 */
#ifndef MY_NETWORK_H
  #define MY_NETWORK_H

#include "ESP8266WiFi.h"
//#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

//const char* my_ssid = "nola_badge";
//const char* my_password = "BonTemps";


/*
 * Adafruit.io Setup 
 * 
 * Use this to connect to https://io.adafruit.com/
 * rather than a local MQTT service. 
 * 
 * Create an ESP8266 WiFiClient class to connect to the MQTT server. 
 * WiFiClient client; or... use WiFiFlientSecure for SSL
 * 
 */
#define AIO_SERVER "io.adafruit.com"
#define AIO_SERVERPORT  8883                   // use 8883 for SSL
#define AIO_USERNAME    ""
#define AIO_KEY         ""

/*
WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

//const char* mqtt_server = "broker.mqttdashboard.com";
//const char* mqtt_server = "iot.eclipse.org";
//const char* mqtt_server = "io.adafruit.com"

// Feeds
Adafruit_MQTT_Publish toServer = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/toServer");
Adafruit_MQTT_Subscribe toBadge = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/toBadge");
*/

  class MyNetwork{
    public:
      MyNetwork();
      
      String BadSSID[];
      bool   WiFiScanned;
      int    WiFiIndex;
      int    WiFiCount;
      bool   DisplayUpdate;
      
      int    MyNetStatus();
      String GetWiFiStatus(int);
      String GetWiFiEncryption(int);
      //void MQTT_connect();

  };

#endif // MY_NETWORK_H
