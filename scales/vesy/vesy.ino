#include "Screen.h" // процедуры отображения
#include "Vesy.h" // процедуры работы с весом
#include "Keyb.h" // процедуры работы с клавиатурой
#include "Motor.h" // процедуры работы с двигателями
#include "Rom.h"  // процедуры работы с памятью

#include "variables.h" // переменные для работы

Screen scr(1);
Vesy vesy(1);
Keyb keyb(1);
Motor motor(1);
Rom rom(1);

void setup() {
  scr.init();
  keyb.init();

  rom.init();
  vesy.CurScale = (float) rom.read(_curScale) / 1000;
  if (vesy.CurScale < 1 || vesy.CurScale > 1000) {
    vesy.CurScale = 3.76;
  }
  rest_weight = rom.read(_rest_weight);
  last_weight = rom.read(_last_weight);
  last_err = rom.read(_last_err);

  // Serial.begin(9600);

  if (motor.init() == 1)
  {
    scr.error(1, "motor");
    while (motor.init() == 1 ) {}
    scr.error(0, " ");
    while (fkey[keyb.read()] != 's' )  {}
  }

  if (vesy.init() == 1)
  {
    scr.error(1, " vesy ");
    while (1) {}
  }

  if (last_err != 0)
  {
    scr.error(1, "work not full");
    while (fkey[keyb.read()] != 's' )  {}
    need_mas = last_weight;
  }
  
  scr.print(String(vesy.offset), 10, 10);
  // delay(1000);


}


void loop() {
  // put your main code here, to run repeatedly:
  scr.print(String(vesy.readVes()), 10, 100);
  delay(100);

}
