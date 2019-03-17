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
    int total; //total menu items on page
    int ledpattern;

    String menu_page_1[4] = { "bling", "games", "network", "about" };
    String menu_page_2[4] = { "Cyber Police", "rainbow", "white" "gradient" };
    String menu_page_3[3] = { "Mesh", "Scanner", "Deauth" };
    String menu_page_4[1] = { "Burgess Pong" };

    String my_menu [5][5] = {
      { "bling", "games", "network", "about", "" },
      { "Cyber Police", "rainbow", "white" "gradient"},
      { "Mesh", "Scanner", "Deauth", "", "" },
      { "Burgess Pong", "", "", "", "" }
    };
                               
    void show_menu();
};

#endif // MY_MENU_H
