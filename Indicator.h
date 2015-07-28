#ifndef INDICATOR_H
#define INDICATOR_H

class Indicator {
  public:
Indicator();
  
    void run();
    void setBlueBlinks(int b);
    void setRedBlinks(int b);
    void setYellowBlinks(int b);
    
  private:
long blinkInterval;
long gapInterval;

int blueBlinks;


int blueCount;

  
long previousBlueMillis;

int blueLedState; 


};

#endif
