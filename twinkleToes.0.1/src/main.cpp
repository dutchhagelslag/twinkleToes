#include <Arduino.h>
#include <FastLED.h>
#include<ledFunctions.h>

FASTLED_USING_NAMESPACE

#define NUM_LEDS 30
#define DATA_PIN 9
#define BRIGHTNESS          96
#define FRAMES_PER_SECOND  120
#define SENSOR_PIN 2

CRGB leds[NUM_LEDS];

class FatherLights{
  protected:
    bool done = false;
  public:
    virtual void work()=0;
    virtual bool timeToDie()const{return done;}
    void die(){done = true;}
  };

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
          return nullptr;
        }
        FatherLights* hold = data[front];
        front = (front+1)%capacity;
        count--;      
        return hold;
    }
    
    bool isEmpty(){return (count == 0);}
    bool isFull(){return (count == capacity);}
};

class ColorRun:public FatherLights{
  private:
    uint8_t currentLed = 0; //change to uuint8_t16_t if NUM_LEDS > 256
    uint8_t color;
  public:
    ColorRun(uint8_t color):color(color){};
        
    bool timeToDie()const{return done;}
    
    void work(){
//      leds[currentLed].setHue(color);
      if(currentLed > 1){
        leds[currentLed-1].fadeToBlackBy(64);
      }
      leds[currentLed] = CHSV(color,100,255);
      currentLed += 1;
      if(currentLed == NUM_LEDS){
        die();  
        }
      }
};

class ColorShift: public FatherLights{
  private:
    
  public:
     void work(){

    }
  };
Queue colorRuns(5);

void setup() {
  delay(2000); //sanity check, youve got 2 seconds to get ur shit together
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  FastLED.clear();
  FastLED.setBrightness(BRIGHTNESS);
  pinMode(SENSOR_PIN, INPUT);
}

void loop(){
  if(digitalRead(2)==HIGH){
    colorRuns.enqueue(new ColorRun(5));
    }
  FastLED.show();
  }