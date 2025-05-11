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
#include "MyMenu.h"

// Change this to your handle
const String myHandle = "@theDevilsVoice";

// class constructor
MyMenu::MyMenu() {}

//<<destructor>>
MyMenu::~MyMenu(){/*nothing to destruct*/}

void MyMenu::begin(){
  Serial.println( "Called MyMenu::begin" );
}

// * Network
// ** Connect to MQTT
// ** Scan WiFi
// * LEDs
// ** rainbox
// ** blink
