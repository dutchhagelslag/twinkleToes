#ifndef light_threads_h
#define light_threads_h

#define NUM_LEDS 50
#define DATA_PIN 3
#define BRIGHTNESS 96
#define COLOR_ORDER GRB
#define MAX_THREADS 10

#include<Thread.h>
#include<FastLED.h>
#include<Arduino.h>

extern struct CRGB leds[];

void darkenFunction();

class Traveling:public Thread{
private:
  uint8_t index = 0;
  
public:
  uint8_t hue;
  
  Traveling(unsigned long _interval = 100, uint8_t hue = 100):Thread(NULL,_interval),hue(hue){}
  
  void run();
};


class AnalogSensor:public Thread{
private:
  int pin;

public:
  AnalogSensor(int pin):Thread(),pin(pin){}

  int check();  

};

class TapSensor{
private:
  int pin;
  bool stillPressed = false;
  unsigned long debounceTime = 0;
  uint16_t debounceInterval = 100;

public:
  TapSensor(int pin):pin(pin){}

  bool check();

};

#endif
