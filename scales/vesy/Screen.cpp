#include <Arduino.h>
#include "Screen.h"
#include <UTFT.h>
#include <EEPROM.h>

extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegmentFull[];
UTFT myGLCD(ILI9481, 38, 39, 40, 41); // дисплей занимает весь порт А и С (c 20 по 43 пин)


Screen::Screen(int num)
{
  _num = num;
}
void Screen::init()
{
  myGLCD.InitLCD();
  myGLCD.clrScr();
  //delay (500);
}

void Screen::print(String process, int x, int y)
{
  String str1 = fill_text(process);
  myGLCD.setFont (BigFont);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.print(str1, x, y);
}
String Screen::fill_text(String str)
{
  int len = 10;
  if (str.length() < 10)
  {
    for (int i = 0; len - str.length(); i++)
    {
      str = " " + str;
    }
  }
  return str;

}


void Screen::error(int err, String str)
{
  myGLCD.clrScr();
  if (err == 1)
  {
    myGLCD.setFont (SevenSegmentFull);
    myGLCD.setColor(VGA_RED);
    myGLCD.print("ERROR", 100, 100);
    myGLCD.print(str, 100, 200);
  }
  else 
  {
    myGLCD.setFont (SevenSegmentFull);
    myGLCD.setColor(VGA_WHITE);
    myGLCD.print("press start", 100, 100);
  }
}

