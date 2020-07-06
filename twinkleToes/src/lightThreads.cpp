#include<Thread.h>
#include<FastLED.h>
#include<Arduino.h>

#include"Configuration.h"
#include"LightThreads.h"
#include"EffectController.h"

void darkenFunction(){
  fadeToBlackBy(leds, NUM_LEDS, 40);
}

void LightThread::setHue(uint8_t input){
  hue = input;
}

void HueTraveling::run(){
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

void HueTraveling::activate(uint8_t input){
  enable = true;
  hue = input;
}

void TravelingPieces::run(){
  if(!enabled){
    return;
  }
  
  for(int i = front; i < end; i++){
    leds[i].setHSV(hue,255,200);
  }
  
  if(end < NUM_LEDS){
    end++;
  }
  
  if(released && front < NUM_LEDS){
    front++;
  }

  if(front == NUM_LEDS){
    enabled = false;
    front = 0;
    end = 0;
  }
  
  runned();
}
