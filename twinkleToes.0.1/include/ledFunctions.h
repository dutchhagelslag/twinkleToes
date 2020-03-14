#ifndef ledFunctions_h
#define ledFunctions_h

#include<Arduino.h> // kill w/ bit manipulation
#include <FastLED.h>

#define NUM_LEDS 30
#define DATA_PIN 3
#define BRIGHTNESS          96
#define FRAMES_PER_SECOND  120
#define SENSOR_PIN 2

extern struct CRGB leds[];

class FatherLights{
  protected:
    bool done = false;
  public:
    virtual void work()=0;

    virtual bool timeToDie()const;

    void die();
  };


class Processes{
  private:
    FatherLights** data = nullptr;
    uint8_t count = 0, capacity;
  public:
    Processes(uint8_t arraySize);
      
    void add(FatherLights* process);

    void remove(size_t index);

    size_t scan()const;
    
    bool isFull()const;
};


class ColorRun:public FatherLights{
  private:
    uint8_t currentLed = 0; //change to uuint8_t16_t if NUM_LEDS > 256
    uint8_t hue;
  public:
    ColorRun(uint8_t hue);
        
    bool timeToDie()const;
    
    void work();
};

class ColorShift: public FatherLights{
  private:
    
  public:
     void work();
  };

#endif