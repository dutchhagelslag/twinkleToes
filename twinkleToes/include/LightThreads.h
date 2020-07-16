#ifndef light_threads_h
#define light_threads_h

#include<Thread.h>
#include<FastLED.h>
#include<Arduino.h>
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


class Traveling:public LightThread{
private:
  uint16_t start = 0;
  uint8_t end = NUM_LEDS;
  bool orientation = true; // true == 0 -> NUM_LEDS
  uint8_t moveInterval = 1;
  uint8_t index = 0;
public:
  Traveling():LightThread(){}
  
  void setStart(uint8_t input);
  void setEnd(uint8_t input);
  void setJump(uint8_t input);
  void reverse();
  void run();
  
  void activate(Sensor* input);
};

class HueTraveling:public Traveling{
public:
  HueTraveling():Traveling(){}
  void activate(Sensor* input);
};

class SpeedTraveling:public Traveling{
public:
  SpeedTraveling():Traveling(){}
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
