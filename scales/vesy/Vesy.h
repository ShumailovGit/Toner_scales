#ifndef __Vesy
#define __Vesy

class Vesy
{
  public:
    Vesy(int num);
    int init();
    bool is_ready();
    long read();
    long readVes();
    float offset, temp, CurScale = 3.76;
  private:
    int _num;
    long previous_weight=0;
};

#endif
