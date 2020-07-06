#include<Thread.h>
#include<FastLED.h>
#include<Arduino.h>

#include"Configuration.h"
#include"Sensors.h"
#include"EffectController.h"


int AnalogSensor::check(){
  return map(analogRead(pin),0,1023,0,255);
}


bool TapSensor::check(){   
   // reads pin, if timer is zero adds new time,
  bool on = digitalRead(pin);

  if(!on){
    stillPressed = false;
    return false;
  }
   
  // time stored on debounceTimers
  else if(on && debounceTime == 0){
    debounceTime = millis();
    return false;
  }
   
  // if timer is not zero, compare with interval -> return true    
  else if(on && millis() - debounceTime > debounceInterval && stillPressed == false){
    debounceTime = 0;
    stillPressed = true;
    return true;
  }
  return false;
}


bool HoldSensor::check(){   
   // reads pin, if timer is zero adds new time,
  bool on = digitalRead(pin);

  if(!on && stillPressed && controller){
    stillPressed = false;
    item->released = true;
  }
  
  if(!on){
    stillPressed = false;
    return false;
  }
   
  // time stored on debounceTimers
  else if(on && debounceTime == 0){
    debounceTime = millis();
    return false;
  }
   
  // if timer is not zero, compare with interval -> return true    
  else if(on && millis() - debounceTime > debounceInterval && stillPressed == false){
    debounceTime = 0;
    stillPressed = true;
    item = controller->add();
    return true;
  }
  return false;
}
