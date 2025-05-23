/*
    Copyright Giuseppe Di Cillo (www.coagula.org)
    Contact: dicillo@coagula.org
    
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
IMPORTANT: to use the menubackend library by Alexander Brevig download it at http://www.arduino.cc/playground/uploads/Profiles/MenuBackend_1-4.zip and add the next code at line 195
	void toRoot() {
		setCurrent( &getRoot() );
	}
*/
#include "MenuBackend.h"    //MenuBackend library - copyright by Alexander Brevig
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include <APA102.h>

void menuUsed(MenuUseEvent);
void menuChanged(MenuChangeEvent );

/*
 int switchPin1 = D3;              
int switchPin2 = D4;
int switchPin3 = D7;
int switchPin4 = D10;
const int buttonPinLeft = 8;      // pin for the Up button
const int buttonPinRight = 9;    // pin for the Down button
const int buttonPinEsc = 10;     // pin for the Esc button
const int buttonPinEnter = 11;   // pin for the Enter button
*/

const int buttonPinLeft = D3;      // pin for the Up button
const int buttonPinRight = D4;    // pin for the Down button
const int buttonPinEsc = D7;     // pin for the Esc button
const int buttonPinEnter = D10;   // pin for the Enter button

int lastButtonPushed = 0;

int lastButtonEnterState = LOW;   // the previous reading from the Enter input pin
int lastButtonEscState = LOW;   // the previous reading from the Esc input pin
int lastButtonLeftState = LOW;   // the previous reading from the Left input pin
int lastButtonRightState = LOW;   // the previous reading from the Right input pin


long lastEnterDebounceTime = 0;  // the last time the output pin was toggled
long lastEscDebounceTime = 0;  // the last time the output pin was toggled
long lastLeftDebounceTime = 0;  // the last time the output pin was toggled
long lastRightDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 500;    // the debounce time

// LiquidCrystal display with:
// rs on pin 7
// rw on ground
// enable on pin 6
// d4, d5, d6, d7 on pins 5, 4, 3, 2
//LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

#define OLED_RESET 2
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

//Menu variables
MenuBackend menu = MenuBackend(menuUsed,menuChanged);

//initialize menuitems
    MenuItem menu1Item1 = MenuItem("Item1");
      MenuItem menuItem1SubItem1 = MenuItem("Item1SubItem1");
      MenuItem menuItem1SubItem2 = MenuItem("Item1SubItem2");
    MenuItem menu1Item2 = MenuItem("Item2");
      MenuItem menuItem2SubItem1 = MenuItem("Item2SubItem1");
      MenuItem menuItem2SubItem2 = MenuItem("Item2SubItem2");
      MenuItem menuItem3SubItem3 = MenuItem("Item2SubItem3");
    MenuItem menu1Item3 = MenuItem("Item3");

void setup()
{
  pinMode(buttonPinLeft, INPUT);
  pinMode(buttonPinRight, INPUT);
  pinMode(buttonPinEnter, INPUT);
  pinMode(buttonPinEsc, INPUT);
  
  
  // initialize with the I2C addr 0x3C (for the 128x32)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  //configure menu
  menu.getRoot().add(menu1Item1);
  menu1Item1.addRight(menu1Item2).addRight(menu1Item3);
  menu1Item1.add(menuItem1SubItem1).addRight(menuItem1SubItem2);
  menu1Item2.add(menuItem2SubItem1).addRight(menuItem2SubItem2).addRight(menuItem3SubItem3);
  menu.toRoot();

  
  //lcd.setCursor(0,0);  
  //lcd.print("www.coagula.org");
  String msg = "Press any button";
  display.setCursor(0, 0);
  display.println(msg);
  display.display();
  
}  // setup()...


void loop()
{

  readButtons();  //I splitted button reading and navigation in two procedures because 
  navigateMenus();  //in some situations I want to use the button for other purpose (eg. to change some settings)
                  
} //loop()... 


void menuChanged(MenuChangeEvent changed){
  
  MenuItem newMenuItem=changed.to; //get the destination menu
  
  //lcd.setCursor(0,1); //set the start position for lcd printing to the second row
  String msg;
  display.setCursor(0, 8);

  
  if(newMenuItem.getName()==menu.getRoot()){
    msg = "Main Menu       ";
    display.println(msg);
    display.display();
  }else if(newMenuItem.getName()=="Item1"){
    msg = "Item1           ";
    display.println(msg);
    display.display();
  }else if(newMenuItem.getName()=="Item1SubItem1"){
    msg = "Item1SubItem1";
    display.println(msg);
    display.display();
  }else if(newMenuItem.getName()=="Item1SubItem2"){
    msg = "Item1SubItem2   ";
    display.println(msg);
    display.display();
  }else if(newMenuItem.getName()=="Item2"){
    msg = "Item2           ";
    display.println(msg);
    display.display();
  }else if(newMenuItem.getName()=="Item2SubItem1"){
    msg = "Item2SubItem1   ";
    display.println(msg);
    display.display();
  }else if(newMenuItem.getName()=="Item2SubItem2"){
    msg = "Item2SubItem2   ";
    display.println(msg);
    display.display();
  }else if(newMenuItem.getName()=="Item2SubItem3"){
    msg = "Item2SubItem3   ";
    display.println(msg);
    display.display();
  }else if(newMenuItem.getName()=="Item3"){
    msg = "Item3           ";
    display.println(msg);
    display.display();
  }
}

void menuUsed(MenuUseEvent used){
  display.setCursor(0,0);  
  String msg = "You used        ";
  display.setCursor(0,8);   
  display.print(used.item.getName());
  display.display();
  delay(2000);  //delay to allow message reading
  display.setCursor(0,0);  
  display.print("www.coagula.org");
  display.display();
  menu.toRoot();  //back to Main
}

void  readButtons(){  //read buttons status
  int reading;
  int buttonEnterState=LOW;             // the current reading from the Enter input pin
  int buttonEscState=LOW;             // the current reading from the input pin
  int buttonLeftState=LOW;             // the current reading from the input pin
  int buttonRightState=LOW;             // the current reading from the input pin

  //Enter button
                  // read the state of the switch into a local variable:
                  reading = digitalRead(buttonPinEnter);

                  // check to see if you just pressed the enter button 
                  // (i.e. the input went from LOW to HIGH),  and you've waited 
                  // long enough since the last press to ignore any noise:  
                
                  // If the switch changed, due to noise or pressing:
                  if (reading != lastButtonEnterState) {
                    // reset the debouncing timer
                    lastEnterDebounceTime = millis();
                  } 
                  
                  if ((millis() - lastEnterDebounceTime) > debounceDelay) {
                    // whatever the reading is at, it's been there for longer
                    // than the debounce delay, so take it as the actual current state:
                    buttonEnterState=reading;
                    lastEnterDebounceTime=millis();
                  }
                  
                  // save the reading.  Next time through the loop,
                  // it'll be the lastButtonState:
                  lastButtonEnterState = reading;
                  

    //Esc button               
                  // read the state of the switch into a local variable:
                  reading = digitalRead(buttonPinEsc);

                  // check to see if you just pressed the Down button 
                  // (i.e. the input went from LOW to HIGH),  and you've waited 
                  // long enough since the last press to ignore any noise:  
                
                  // If the switch changed, due to noise or pressing:
                  if (reading != lastButtonEscState) {
                    // reset the debouncing timer
                    lastEscDebounceTime = millis();
                  } 
                  
                  if ((millis() - lastEscDebounceTime) > debounceDelay) {
                    // whatever the reading is at, it's been there for longer
                    // than the debounce delay, so take it as the actual current state:
                    buttonEscState = reading;
                    lastEscDebounceTime=millis();
                  }
                  
                  // save the reading.  Next time through the loop,
                  // it'll be the lastButtonState:
                  lastButtonEscState = reading; 
                  
                     
   //Down button               
                  // read the state of the switch into a local variable:
                  reading = digitalRead(buttonPinRight);

                  // check to see if you just pressed the Down button 
                  // (i.e. the input went from LOW to HIGH),  and you've waited 
                  // long enough since the last press to ignore any noise:  
                
                  // If the switch changed, due to noise or pressing:
                  if (reading != lastButtonRightState) {
                    // reset the debouncing timer
                    lastRightDebounceTime = millis();
                  } 
                  
                  if ((millis() - lastRightDebounceTime) > debounceDelay) {
                    // whatever the reading is at, it's been there for longer
                    // than the debounce delay, so take it as the actual current state:
                    buttonRightState = reading;
                   lastRightDebounceTime =millis();
                  }
                  
                  // save the reading.  Next time through the loop,
                  // it'll be the lastButtonState:
                  lastButtonRightState = reading;                  
                  
                  
    //Up button               
                  // read the state of the switch into a local variable:
                  reading = digitalRead(buttonPinLeft);

                  // check to see if you just pressed the Down button 
                  // (i.e. the input went from LOW to HIGH),  and you've waited 
                  // long enough since the last press to ignore any noise:  
                
                  // If the switch changed, due to noise or pressing:
                  if (reading != lastButtonLeftState) {
                    // reset the debouncing timer
                    lastLeftDebounceTime = millis();
                  } 
                  
                  if ((millis() - lastLeftDebounceTime) > debounceDelay) {
                    // whatever the reading is at, it's been there for longer
                    // than the debounce delay, so take it as the actual current state:
                    buttonLeftState = reading;
                    lastLeftDebounceTime=millis();;
                  }
                  
                  // save the reading.  Next time through the loop,
                  // it'll be the lastButtonState:
                  lastButtonLeftState = reading;  

                  //records which button has been pressed
                  if (buttonEnterState==HIGH){
                    lastButtonPushed=buttonPinEnter;

                  }else if(buttonEscState==HIGH){
                    lastButtonPushed=buttonPinEsc;

                  }else if(buttonRightState==HIGH){
                    lastButtonPushed=buttonPinRight;

                  }else if(buttonLeftState==HIGH){
                    lastButtonPushed=buttonPinLeft;

                  }else{
                    lastButtonPushed=0;
                  }                  
}

void navigateMenus() {
  MenuItem currentMenu=menu.getCurrent();
  
  switch (lastButtonPushed){
    case buttonPinEnter:
      if(!(currentMenu.moveDown())){  //if the current menu has a child and has been pressed enter then menu navigate to item below
        menu.use();
      }else{  //otherwise, if menu has no child and has been pressed enter the current menu is used
        menu.moveDown();
       } 
      break;
    case buttonPinEsc:
      menu.toRoot();  //back to main
      break;
    case buttonPinRight:
      menu.moveRight();
      break;      
    case buttonPinLeft:
      menu.moveLeft();
      break;      
  }
  
  lastButtonPushed=0; //reset the lastButtonPushed variable
}



