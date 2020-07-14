#ifndef light_threads_h
#define light_threads_h

#include<Thread.h>
#include<FastLED.h>
#include<Arduino.h>
#include<EffectController.h>
#include"Configuration.h"
#include"Sensors.h"

void darkenFunction();

class LightThread:public Thread{
public:
  uint8_t hue = 150;

  LightThread():Thread(NULL,THREAD_RATE){}
  virtual void run(){};
  virtual void activate(Sensor* input){};
  void setHue(uint8_t input);
};



class HueTraveling:public LightThread{
private:
  uint8_t index = 0;
public:
  HueTraveling():LightThread(){}
  void run();
  void activate(Sensor* input);
};



class SpeedTraveling:public HueTraveling{
public:
  SpeedTraveling():HueTraveling(){}
  void activate(Sensor* input);
};


class TravelingPieces:public LightThread{
public:
  uint8_t front = 0;
  uint8_t end = 0;
  bool released = false;
  
  Sensor* sensor = nullptr;
  bool chosen = false; 
  
  TravelingPieces():LightThread(){}
  void run();
  void activate(Sensor* input);
}; 


#endif
