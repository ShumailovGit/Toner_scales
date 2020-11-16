#ifndef __Keyb
#define __Keyb

class Keyb
{
  public:
    Keyb(int num);
    void init();
//
    int read_();
    int read();  
  private:
    int _num;
    unsigned long period_presses = 500; 
    unsigned long last_press; 
};

#endif
