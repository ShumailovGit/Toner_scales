#include <Arduino.h>
#include "Keyb.h" 


// пины клавитуры 
#define pin_key A0  
#define pin_start A3
#define pin_stop A2 
#define pin_menu A1 

const int key_volt[13] = {1000, 900, 830, 750, 720, 650, 620, 580, 550, 520, 490, 470, -1};


Keyb::Keyb(int num)
{
  _num = num;
}
void Keyb::init()
{
  pinMode(pin_key,  INPUT);
  pinMode(pin_start, INPUT);
  pinMode(pin_stop, INPUT);
  pinMode(pin_menu, INPUT);
  last_press = millis();
}
// чтение клавиатуры: 0 - если ничего не нажато
int Keyb::read_() 
{
  int key = 0;
  int a_key = analogRead(pin_key);
  int i = 0;
  while (a_key < key_volt[i]) {
    i++;
  }
  if (i < 12) {
    key = i+1;
  }
  if (digitalRead(pin_start) == HIGH) {
    key = 13;
  }
  if (digitalRead(pin_stop) == HIGH) {
    key = 14;
  }
  if (digitalRead(pin_menu) == HIGH) {
    key = 15;
  }
  return key;
}

int Keyb::read() 
{
  if (millis()-last_press>=period_presses)
    {
      last_press= millis();
       return read_();
    } else 
    {
      return 0;
    }
}

