#ifndef ledFunctions_h
#define ledFunctions_h

#include <FastLED.h>

#define NUM_LEDS 30
#define DATA_PIN 9
#define BRIGHTNESS          96
#define FRAMES_PER_SECOND  120
#define SENSOR_PIN 2

extern struct CRGB leds[];

class FatherLights{
  protected:
    bool done = false;
  public:
    virtual void work()=0;
    virtual bool timeToDie();
    void die();
    virtual ~FatherLights(){};
  };

class Queue{
  private:
    FatherLights** data = nullptr;
    uint8_t count = 0, capacity , front = 0, rear = - 1;
  public:
    Queue(uint8_t arraySize);
      
    ~Queue();
      
    void enqueue(FatherLights* object);

    FatherLights* pop();

    bool isEmpty();
    bool isFull();
};

class ColorRun:public FatherLights{
  private:
    uint8_t currentLed = 0; //change to uuint8_t16_t if NUM_LEDS > 256
    uint8_t color;
  public:
    ColorRun(uint8_t color);
        
    bool timeToDie()const;
    
    void work();
};

class ColorShift: public FatherLights{
  private:
    
  public:
     void work();
  };

#endif