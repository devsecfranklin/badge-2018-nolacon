/*!
 * @file MyMenu.h
 *  ____  _____      _    ____    _  ___     ____ ____  
 * |  _ \| ____|_   / \  |  _ \ _/ |/ _ \ _ / ___| ___| 
 * | | | |  _| (_) / _ \ | | | (_) | | | (_) |   |___ \ 
 * | |_| | |___ _ / ___ \| |_| |_| | |_| |_| |___ ___) |
 * |____/|_____(_)_/   \_\____/(_)_|\___/(_)\____|____/ 
 *                                                    
 *                                                    
 * Author : @theDevilsVoice @p0lr_ @mzbat
 * Date   : May 15, 2018
 * Version: 0.5
 */

#ifndef MY_MENU_H
#define MY_MENU_H

#include <string>


class MyMenu{
  public:
    const String myHandle = "@nola_con";
    String myText; 
    int page;  // page number
    int inv;   // which menu item to invert
    int ledpattern;

    String my_menu[4][5] = {
      { "bling1", network", "about"},
      { "Cyber Police", "rainbow", "white", "gradient"},
      { "Mesh", "Scanner", "Deauth", "Empty"}
    };
                               
    void show_menu();
};

#endif // MY_MENU_H
