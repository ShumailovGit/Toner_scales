#include <Arduino.h>
#include "Rom.h" 
#include <EEPROM.h>


Rom::Rom(int num)
{
  _num = num;
}
void Rom::init()
{
  
}

unsigned int Rom::read(int p_address)
// This function will read a 2 byte integer from the eeprom at the specified address and address + 1
{
  byte lowByte = EEPROM.read(p_address);
  byte highByte = EEPROM.read(p_address + 1);
  if ( (((lowByte << 0) & 0xFF) == 0xFF) && (((highByte << 0) & 0xFF) == 0xFF) ) return 0;
  else return ((lowByte << 0) & 0xFF) + ((highByte << 8) & 0xFF00);
}
void Rom::write(int p_address, int p_value)
// This function will write a 2 byte integer to the eeprom at the specified address and address + 1
{
  byte lowByte = ((p_value >> 0) & 0xFF);
  byte highByte = ((p_value >> 8) & 0xFF);
  EEPROM.write(p_address, lowByte);
  EEPROM.write(p_address + 1, highByte);
}
