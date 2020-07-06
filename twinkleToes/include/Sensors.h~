#ifndef sensors_h
#define sensors_h

#include<FastLED.h>
#include"EffectController.h"
#include"LightThreads.h"

class Sensor{
 protected:
  int pin;
  
 public:
 Sensor(int pin):pin(pin){
    pinMode(pin, INPUT);
  }
};


class AnalogSensor:public Sensor{
 public:
  AnalogSensor(int pin):Sensor(pin){}

  int check();  

};

class TapSensor:public Sensor{
 protected:
  bool stillPressed = false;
  unsigned long debounceTime = 0;
  uint16_t debounceInterval = 100;

 public:
  TapSensor(int pin):Sensor(pin){}

  virtual bool check();

};

class HoldSensor:public TapSensor{
 private:
  EffectController<TravelingPieces>* controller = nullptr;
  TravelingPieces* item;
  
 public:
  HoldSensor(int pin, EffectController<TravelingPieces>* controller):TapSensor(pin), controller(controller){}

  bool check();
};



#endif
