#include <Arduino.h>
#include "Motor.h"


//можно использовать внутренний ШИМ . занимает счетчики
// Пины драйверов движков и заслонки ----------------------
#define Polarity  //обьявлено --- подключено к плюсу
#define cover 8 // заслоника -  не будет в данной версии--
#define cover_err 5 // ошибка заслонки 1 - ошибка 


#define extruder 9 // податчик                            
boolean extruder_fl = false ; // флаг экструдера
#define extruder_pwm_start 250 // !!!посчитать частоту - частота при старте
#define extruder_pwm_end 1  //  - частота при оконцании
#define extruder_pwm_end_mas 10 //  - остаток веса до окончания
char extruder_pwm = extruder_pwm_start;
#define extruder_err 5 // ошибка экструдера 1 - ошибка 


#define mix 10 // мешалка внутри бака                     
boolean mix_fl = false ; // флаг мешалки
#define mix_pwm 10 // !!!посчитать частоту
#define mix_err 5 // ошибка мешалки 1 - ошибка 




Motor::Motor(int num)
{
  _num = num;
}
int  Motor::init()
{
  pinMode(extruder_err, INPUT);
  pinMode(mix_err, INPUT);
  if (digitalRead(extruder_err) == true || digitalRead(mix_err) == true)
  {
    return 1;
  }
  else
  {
    // диоды подключены к плюсу - LOW - горит
    pinMode(extruder, OUTPUT);
    pinMode(mix, OUTPUT);
#ifdef Polarity
    digitalWrite (extruder, HIGH);
    digitalWrite (mix, HIGH);
#else
    digitalWrite (extruder, LOW);
    digitalWrite (mix, LOW);
#endif
    return 0;
  }
}


