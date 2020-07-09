#include<Thread.h>
#include<FastLED.h>
#include<Arduino.h>

#include"Configuration.h"
#include"LightThreads.h"
#include"EffectController.h"

void darkenFunction(){
  fadeToBlackBy(leds, NUM_LEDS, 40);
}

//flip enabled flag when complete

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
  hue = input;
  HueTraveling::enabled = true;
}





void SpeedTraveling::activate(uint8_t input){
  interval = input;
  SpeedTraveling::enabled = true;
}





void TravelingPieces::run(){  
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

void TravelingPieces::activate(uint8_t input){
  if(input > 0){
    return;
  }
}
