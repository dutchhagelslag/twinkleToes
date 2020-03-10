#include <FastLED.h>
#include"functions.h"

FASTLED_USING_NAMESPACE

#define NUM_LEDS 30
#define DATA_PIN 9
#define BRIGHTNESS          96
#define FRAMES_PER_SECOND  120

CRGB leds[NUM_LEDS];

class FatherLights;

class Queue{
  private:
    FatherLights** data = nullptr;
    uint8_t count = 0, capacity , front = 0, rear = - 1;
    
  public:
    Queue(uint8_t arraySize):capacity(arraySize){
      data = new FatherLights*[arraySize];
      }
      
    ~Queue(){
      for(uint8_t i = 0; i < count; i++){
        delete data[front];
        front = (front+1)%capacity;
        }
        delete[] data;
      }
      
    void enqueue(FatherLights* object) {
       if(isFull()){
          return;
        }
        data[rear] = object;
        rear = (rear+1)%capacity;
        count++;
    }
    
    FatherLights* pop(){
       if(isEmpty()){
          return;
        }
        FatherLights* hold = data[front];
        front = (front+1)%capacity;
        count--;      
        return hold;
    }
    
    bool isEmpty(){return (count == 0);}
    bool isFull(){return (count == capacity);}
};

class MillisTimer{
  private:
    unsigned long start;
  public:
    MillisTimer():start(millis()){}
    
    bool operator()(unsigned long uint8_terval){
      if(millis() - start >= uint8_terval)
        start = millis();
        return true;
      return false;      
      }
};

class FatherLights{
  protected:
    bool done = false;
  public:
    virtual void work()=0;
    virtual bool timeToDie()const{return done;}
    void die(){done = true;}
  };

class ColorShift{
  private:
    
  public:
  
  };

class ColorRun:public FatherLights{
  private:
    uint8_t currentLed = 0; //change to uuint8_t16_t if NUM_LEDS > 256
    uint8_t color;
  public:
    ColorRun(uint8_t color):color(color){};
        
    virtual bool timeToDie()const{return done;}
    
    virtual void work(){
//      leds[currentLed].setHue(color);
      leds[currentLed] = CHSV(color,100,255);

      currentLed += 1;
      if(currentLed == NUM_LEDS){
        die();  
        }
      }
};

Queue colorRuns(5);

void setup() {
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  FastLED.clear();
  FastLED.setBrightness(BRIGHTNESS);
  pinMode(2, INPUT);
}

void loop(){
  if(digitalRead(2)==HIGH){
    colorRuns.enqueue(new ColorRun(5));
    }
  FastLED.show();
  }
