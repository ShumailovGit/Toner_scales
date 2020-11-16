#ifndef __Rom
#define __Rom

#define _curScale 0
#define _rest_weight 2
#define _last_weight 4
#define _last_err 6  // нужна ли?

class Rom
{
  public:
    Rom(int num);
    void init();
    unsigned int read(int p_address);
    void write(int p_address, int p_value);
    
  private:
    int _num;
    
};

#endif
