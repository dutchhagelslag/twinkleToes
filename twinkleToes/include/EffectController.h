#ifndef effectController_h
#define effectController_h

#include<Thread.h>

#include"Sensors.h"
#include"Configuration.h"
#include"LightThreads.h"

template<class T>
class EffectController:public Thread{  
private:
  Sensor* sensor;
  
public:
  T* array[MAX_THREADS];
  
  EffectController(unsigned long interval = CONTROLLER_RATE):Thread(NULL,interval){

    for(size_t i = 0; i < MAX_THREADS; i++){
      array[i] = new T();
      array[i]->enabled = false;
    }
  }
  
  void check(){
    if(sensor->check() > 0){
      add();
    }
  }
  
  void add(){
    for(size_t i = 0; i < MAX_THREADS; i++){
      if(not (array[i]->enabled)){
	array[i]->activate(sensor);
	return;
      }
    }
  }
  
  void run(){
    unsigned long time = millis();
    
    for(int i = 0; i < MAX_THREADS; i++){
      if(array[i]->shouldRun(time)){
	array[i]->run();
      }
    }
    runned();
  }
    

  void setHue(uint8_t input){
    for(int i = 0; i < MAX_THREADS; i++){
      array[i]->setHue(input);
    }
  }
  
  void attachSensor(Sensor& newSensor){
    sensor = &newSensor;
  }
  
};

#endif
