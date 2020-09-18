#ifndef light_threads_h
#define light_threads_h

#include<Thread.h>
#include<FastLED.h>
#include<Arduino.h>
#include"Configuration.h"
#include"Sensors.h"

void darkenFunction();

//objects that recieve Sensors and determines how to control the light by its reading.
class LightThread:public Thread{
public:
  uint8_t hue = 150;
  bool locked = false;

  LightThread():Thread(NULL,THREAD_RATE){}

  //runs pattern based on sensor reading
  virtual void run(){};

  //recieves Sensor and enables
  virtual void activate(Sensor* input){};

  void setHue(uint8_t input);
};

//the base for a single light traveling across the LED strip
class Traveling:public LightThread{
private:
  uint16_t start = 0; // start index
  uint8_t end = NUM_LEDS; 
  bool orientation = true; // true == lights move from 0 to NUM_LEDS
  uint8_t moveInterval = 1;
  uint8_t index = 0; // current index
public:
  Traveling():LightThread(){}  
  void run();
  void activate(Sensor* input);

  void setStart(uint8_t input);
  void setEnd(uint8_t input);
  void setJump(uint8_t input);
  void reverse();
};

//takes variable sensor reading which determines the hue of the traveling light.
class HueTraveling:public Traveling{
public:
  HueTraveling():Traveling(){}
  void activate(Sensor* input);
};

//takes variable sensor reading which determines the speed of the traveling light.
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
