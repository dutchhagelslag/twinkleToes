#ifndef effectController_h
#define effectController_h

#include<Thread.h>

#include"Sensors.h"
#include"Configuration.h"
#include"LightThreads.h"

//template<class T>
class EffectController:public Thread{  
private:
  Sensor* sensor;
  int capacity;
  int last = 0;
  int upNext = 0;
public:
  LightThread* array[MAX_THREADS];
  
  EffectController(int size = 10, unsigned long interval = 0):Thread(NULL,interval){
    capacity = size;
  }

  void fill(LightThread* pattern){
    while(last < capacity){
      array[last] = pattern->getCopy();
      last++;
    }
  }

  void add(LightThread* pattern){
    array[last] = pattern->getCopy();
    last++;
  }

  void add(LightThread* pattern[], int length){
    for(int i = 0; i < length && last < capacity; i++){
      array[last] = pattern[i]->getCopy();
      last++;
    }
  }

  void check(){
    if(sensor->check() > 0){
      add();
    }
  }

  //passes a sensor and activates a lightThread object
  void add(){
    for(int i = 0; i < last; i++){
      int j = (i+upNext)% last;
      
      if(!(array[i]->locked)){
	array[j]->activate(sensor);
	upNext = j + 1;
	return;
      }
    }
  }
  
  void run(){
    //may comment out this block.
    // if(!shouldRun()){
    //   return;
    // }
    check();
    
    unsigned long time = millis();
    
    for(int i = 0; i < last; i++){
      if(array[i]->shouldRun(time)){
	array[i]->run();
      }
    }
    runned();
  }
    

  void setHue(uint8_t input){
    for(int i = 0; i < last; i++){
      array[i]->setHue(input);
    }
  }
  
  void attachSensor(Sensor& newSensor){
    sensor = &newSensor;
  }
  
};

#endif
