#ifndef manager_h
#define manager_h

#include"Sensors.h"
#include"EffectController.h"

class Manager{
 private:
  EffectController** effects;
 public:
   Manager(){
     //     effects
   }

   void run();

   void addEffect();
};

#endif
