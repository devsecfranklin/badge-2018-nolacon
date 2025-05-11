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

// class constructor
MyMenu::MyMenu() {
  currentMenu = 0;   
  high_lit = 0;
}

//<<destructor>>
MyMenu::~MyMenu(){/*nothing to destruct*/}

void MyMenu::begin(){
  Serial.println( "Called MyMenu::begin" );
}

char* MyMenu::getMyMenu() {
  char *mymenu = (char*)malloc(1);
  strcpy(mymenu, "bling\ngames\nnetwork");
  return mymenu;
}
