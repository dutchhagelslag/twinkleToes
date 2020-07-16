#include<Thread.h>
#include<FastLED.h>
#include<Arduino.h>

#include"Configuration.h"
#include"LightThreads.h"
#include"EffectController.h"
#include"Sensors.h"

void darkenFunction(){
  fadeToBlackBy(leds, NUM_LEDS, 40);
}


//flip enabled flag when complete


void LightThread::setHue(uint8_t input){
  hue = input;
}


//


void Traveling::run(){
  if(index == end){
    index = start;
    enabled = false;
    runned();
    return;
  }

  leds[index].setHSV(hue,155,200);

  (orientation) ? index += moveInterval: index -= moveInterval;
  runned();
}


void Traveling::setStart(uint8_t input){
  start = input;
}

void Traveling::setEnd(uint8_t input){
  end = input;
}

void Traveling::reverse(){
  orientation = !orientation;
}

void Traveling::setJump(uint8_t input){
  moveInterval = input;
}

void Traveling::activate(Sensor* input){
  Traveling::enabled = true;
}


//


void HueTraveling::activate(Sensor* input){
  hue = input->check();
  HueTraveling::enabled = true;
}

void SpeedTraveling::activate(Sensor* input){
  interval = input->check();
  SpeedTraveling::enabled = true;
}


//


void TravelingPieces::run(){
  delay(100);
  // digitalWrite(13,HIGH); delay(100); digitalWrite(13,LOW);
  if(sensor->check() == 0){
    released = true;
  }
  
  leds[end].setHSV(hue,255,200);

  
  if(released){
    leds[front].setHSV(hue,255,0);
    if(sensor->locked){
      sensor->unlock();
    }
  }
  
  if(end < NUM_LEDS){
    end++;
  }
  
  if(released && front < NUM_LEDS){
    front++;
  }

  if(front == NUM_LEDS){
    enabled = false;
    released = false;
    front = 0; end = 0;
  }
  
  runned();
}

void TravelingPieces::activate(Sensor* input){
  sensor = input;
  if(!(sensor->locked)){
    TravelingPieces::enabled = true;
    sensor->lock();
    runned();
  }
}
