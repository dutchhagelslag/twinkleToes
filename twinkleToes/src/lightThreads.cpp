#include<Thread.h>
#include<FastLED.h>
#include<Arduino.h>

#include"lightThreads.h"
#include"EffectController.h"

void darkenFunction(){
  fadeToBlackBy(leds, NUM_LEDS, 40);
}

void Traveling::run(){
  if(index == NUM_LEDS){
    index = 0;
    enabled = false;
  }
  else{
    leds[index].setHSV(hue,155,200);
    index++;
  }
  runned();
}



int AnalogSensor::check(){
  runned();
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
