#include <Arduino.h>
#include "Vesy.h"
//#include "HX711.h"

#define DOUT A9
#define PD_SCK A8
#define iter 50
#define GAIN 1
//HX711 scale(DOUT, PD_SCK);





Vesy::Vesy(int num)
{
  _num = num;
}
int Vesy::init()
{
  pinMode(PD_SCK, OUTPUT);
  pinMode(DOUT, INPUT);
  delay(100);
  for (int i = 0; i < 200; i++)
  {
    while (!is_ready());
    temp += read();
  }
  temp = temp / 200;

  temp = floor( (temp / 100) + 0.5);
  offset = temp;
  
  if (offset<500)
  {return 1;} 
  else
  {return 0;}
}

long Vesy::readVes()
{
  if (is_ready())
  {
    temp = read();
    temp = floor( (temp / 100) + 0.5);
    // previous_weight= floor((temp - offset) / CurScale );
    temp = floor((temp - offset) / CurScale );
  //  temp = floor(temp - offset) ;
    if ((abs(previous_weight - temp) > 1))
    {
      previous_weight= temp;
      return temp;
    }
    else
    {
      return previous_weight;
    }

  } else
  {
    return previous_weight;
  }
}



bool Vesy::is_ready() {
  return digitalRead(DOUT) == LOW;
}

long Vesy::read() {

  unsigned long value = 0;
  byte data[3] = { 0 };
  byte filler = 0x00;

  // pulse the clock pin 24 times to read the data
  data[2] = shiftIn(DOUT, PD_SCK, MSBFIRST);
  data[1] = shiftIn(DOUT, PD_SCK, MSBFIRST);
  data[0] = shiftIn(DOUT, PD_SCK, MSBFIRST);

  // set the channel and the gain factor for the next reading using the clock pin

  digitalWrite(PD_SCK, HIGH);
  digitalWrite(PD_SCK, LOW);


  // Datasheet indicates the value is returned as a two's complement value
  // Flip all the bits
  data[2] = ~data[2];
  data[1] = ~data[1];
  data[0] = ~data[0];

  // Replicate the most significant bit to pad out a 32-bit signed integer
  if ( data[2] & 0x80 ) {
    filler = 0xFF;
  } else if ((0x7F == data[2]) && (0xFF == data[1]) && (0xFF == data[0])) {
    filler = 0xFF;
  } else {
    filler = 0x00;
  }

  // Construct a 32-bit signed integer
  value = ( static_cast<unsigned long>(filler) << 24
            | static_cast<unsigned long>(data[2]) << 16
            | static_cast<unsigned long>(data[1]) << 8
            | static_cast<unsigned long>(data[0]) );

  // ... and add 1
  return static_cast<long>(++value);
}

