/*!
 * @file MyNetwork.cpp
 * 
 *    
    ____  _____      _    ____    _  ___     ____ ____
   |  _ \| ____|_   / \  |  _ \ _/ |/ _ \ _ / ___| ___|
   | | | |  _| (_) / _ \ | | | (_) | | | (_) |   |___ \
   | |_| | |___ _ / ___ \| |_| |_| | |_| |_| |___ ___) |
   |____/|_____(_)_/   \_\____/(_)_|\___/(_)\____|____/


 * @section author Author
 * 
 * Written by @theDevilsVoice for @dead10c5
 * 
   Date   : May 26, 2018
   Version: 0.5
*/
#include "MyNetwork.h"


// redo this stuff into a struct
/*   String BadSSID[] = "";
  bool   WiFiScanned = false;
  int    WiFiIndex = 0;
  int    WiFiCount = 0;
  bool   DisplayUpdate = true;
*/


MyNetwork::MyNetwork() {
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  WiFiScanned = false;
  WiFiIndex = 0;
  WiFiCount = 0;
  DisplayUpdate = true;
  WiFi.softAPdisconnect (true);
}

int MyNetwork::MyNetStatus() {
  return WiFi.status();
}

String MyNetwork::GetWiFiStatus(int StatusCode) {
  if (StatusCode == 255) {
    return ("No Shield");
  } else if (StatusCode == 0) {
    return ("Idle");
  } else if (StatusCode == 1) {
    return ("SSID Unavailable");
  } else if (StatusCode == 2) {
    return ("Scan Completed");
  } else if (StatusCode == 3) {
    return ("Connected");
  } else if (StatusCode == 4) {
    return ("Connect Failed");
  } else if (StatusCode == 5) {
    return ("Connection Lost");
  } else if (StatusCode == 6) {
    return ("Disconnected");
  } else {
    return ("Unknown State " + String(StatusCode));
  }
}

String MyNetwork::GetWiFiEncryption(int StatusCode) {
  if (StatusCode == 2) {
    return ("WPA PSK");
  } else if (StatusCode == 4) {
    return ("WPA2 PSK");
  } else if (StatusCode == 5) {
    return ("WEP");
  } else if (StatusCode == 7) {
    return ("None");
  } else if (StatusCode == 8) {
    return ("WPA/WPA2");
  } else {
    return ("Unknown");
  }
}

/* 
 * Function to connect and reconnect as necessary to the MQTT server.
 * Should be called in the loop function and it will take care if connecting.
 */
 /*
void MyNetwork::MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  String msg="Connecting to MQTT... ";
  Serial.println(msg);
  //display.println(msg);
  //display.display();
  
  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  msg = "MQTT Connected!";
  Serial.println(msg);
  //display.println(msg);
  //display.display();
  
}
*/
