#ifndef __Screen
#define __Screen

class Screen
{
  public:
    Screen(int num);
    void init();

    void error(int err, String str);
    void print(String process, int x, int y);
    String fill_text(String str);
  private:
    int _num;
};

#endif
