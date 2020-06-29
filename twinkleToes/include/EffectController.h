#ifndef effectController_h
#define effectController_h

#include<Thread.h>
#include"lightThreads.h"

template<class T>
class EffectController:public Thread{  
public:
  T* array[MAX_THREADS];
  
  EffectController(unsigned long _interval = 0):Thread(NULL,_interval){

    for(size_t i = 0; i < MAX_THREADS; i++){
      array[i] = new T();
      array[i]->enabled = false;
    }
  }

  void run(){
    if(_onRun != NULL)
      _onRun();

    unsigned long time = millis();
    for(int i = 0; i < MAX_THREADS; i++){
      if(array[i]->shouldRun(time)){
	array[i]->run();
      }
    }
    runned();
  }

  void add(){
    for(int i = 0; i < MAX_THREADS; i++){
      if(array[i]->enabled == false){
	array[i]->enabled = true;
	return;
      }
    }
    return;
  }
};

#endif
