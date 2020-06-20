#ifndef light_threads_h
#define light_threads_h
#define NUM_LEDS 50
#define DATA_PIN 3
#define BRIGHTNESS 96
#define COLOR_ORDER GRB


#include<Thread.h>
#include<ThreadController.h>
#include<FastLED.h>
#include<Arduino.h>

extern struct CRGB leds[];

class Traveling:public Thread{
private:
  uint8_t index = 0;
  uint8_t hue;
  ThreadController* threadcontroller;

public:
  Traveling(unsigned long _interval, uint8_t hue):Thread(NULL,_interval),hue(hue){}
  
  void run(){
    if(index == NUM_LEDS){
      threadcontroller->remove(this);
      
    }
    else{
      leds[index].setHSV(hue,155,50);
      index++;
    }
    runned();
  }
};



class AnalogSensor:public Thread{
private:
  int pin;
  ThreadController* threadcontroller;

public:
  AnalogSensor(int pin, ThreadController* threadcontroller):Thread(NULL,100),pin(pin),threadcontroller(threadcontroller){}

  void run(){
    int value = 300 - map(analogRead(pin),0,1023,0,255); 
    if(value < 290){

      if(threadcontroller->size() == 15){
	threadcontroller->add(new Traveling(value,value));
      }
    runned();
    }
  }

};

class DigitalSensor:public Thread{
private:
  int pin;
  ThreadController* threadcontroller;
  bool stillPressed = false;
  unsigned long debounceTime = 0;
  uint16_t debounceInterval = 500;

public:
  DigitalSensor(int pin,ThreadController* threadcontroller):Thread(NULL,100),pin(pin),threadcontroller(threadcontroller){}

  void run(){
    
    // reads pin, if timer is zero adds new time, ends
    bool on = digitalRead(pin);

    if(!on){
      stillPressed = false;
    }
    
    // time stored on debounceTimers
    else if((on && debounceTime == 0)){
      debounceTime = millis();
    }
    
    // if timer is not zero, compare with interval -> return true    
    else if((on && debounceTime > 0)){
      if(millis() - debounceTime > debounceInterval){
	debounceTime = 0;
	stillPressed = true;
	threadcontroller->add(new Traveling(100,100));
      }
    }
    runned();
    }

};


class LEDController:public Thread{
private:

public:


};
#endif
