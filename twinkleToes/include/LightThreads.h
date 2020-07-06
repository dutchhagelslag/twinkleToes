#ifndef light_threads_h
#define light_threads_h

#include<Thread.h>
#include<FastLED.h>
#include<Arduino.h>
#include<EffectController.h>
#include"Configuration.h"


void darkenFunction();

class LightThread:public Thread{
private:
  
public:
  LightThread(unsigned long _interval = THREAD_RATE):Thread(NULL,_interval){}

  virtual void run(){};
  virtual void activate(uint8_t input = 0){};

  void setHue(uint8_t input);

  uint8_t hue = 150;
};

class HueTraveling:public LightThread{
private:
  uint8_t index = 0;
  
public:

  HueTraveling(unsigned long _interval = THREAD_RATE):LightThread(_interval){}
  
  void run();
  void activate(uint8_t input);
};

class SpeedTraveling:publicLightThread{
}


class TravelingPieces:public LightThread{
public:
  uint8_t front = 0;
  uint8_t end = 0;
  bool released = false;
public:
  TravelingPieces(unsigned long _interval = THREAD_RATE):LightThread(_interval){}
  void run();
  void activate(uint8_t input);
}; 


#endif
