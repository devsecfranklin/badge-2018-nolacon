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
#include "MyNetwork.h"
#include "MyLed.h"
#include "MyButtons.h"
#include "MyDisplay.h"

// Initialize instance of MyNetwork() class
MyNetwork mynetwork;
// Initialize instance of MyLed() class
MyLed myled;
// Initialize instance of MyDisplay() class
MyDisplay mydisp;


void setup() {

}

void loop() {

  //mydisp.showDeadlocksLogo();
  mydisp.showNolaLogo();
  // show menus

   // void MQTT_connect();

  //myled.rainbow();
  //mydisp.showNolaLogo();
  
}
