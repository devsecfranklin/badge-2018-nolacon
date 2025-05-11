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
#include "MyButtons.h"

// class constructor
MyButtons::MyButtons(){
  pinMode(UP, INPUT_PULLUP);
  pinMode(ESC, INPUT_PULLUP);
  pinMode(ENTER, INPUT_PULLUP);
  pinMode(DOWN, INPUT_PULLUP);
}

//<<destructor>>
MyButtons::~MyButtons(){/*nothing to destruct*/}
