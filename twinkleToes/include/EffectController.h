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
  
  EffectController(unsigned long interval = THREAD_RATE):Thread(NULL,interval){

    for(size_t i = 0; i < MAX_THREADS; i++){
      array[i] = new T();
      array[i]->enabled = false;
    }
  }

  void check(){
    int sensorValue = sensor->check();
    if(sensorValue > 0){
      add(sensorValue);
    }
    return;
  }
  
  void add(uint8_t input = 0){
    for(size_t i = 0; i < MAX_THREADS; i++){
      if(not (array[i]->enabled)){
	array[i]->enabled = true;
	array[i]->activate(input);
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
