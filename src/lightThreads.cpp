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
    locked = false;
    runned();
    return;
  }

  leds[index].setHSV(hue,155,200);

  //decides if the light goes left or right
  index += moveInterval;
  runned();
}


void Traveling::setStart(uint8_t input){
  start = input;
}

void Traveling::setEnd(uint8_t input){
  end = input;
}

void Traveling::setJump(uint8_t input){
  moveInterval = input;
}

void Traveling::activate(Sensor* input){
  enabled = true;
  locked = true;
}

LightThread* Traveling::getCopy(){
  return new Traveling(*this);
}

//


void HueTraveling::activate(Sensor* input){
  hue = input->check();
  HueTraveling::enabled = true;
  locked = true;
}

LightThread* HueTraveling::getCopy(){
  return new HueTraveling(*this);
}

void SpeedTraveling::activate(Sensor* input){
  interval = input->check();
  SpeedTraveling::enabled = true;
  locked = true;
}

LightThread* SpeedTraveling::getCopy(){
  return new SpeedTraveling(*this);
}

//

void TravelingPieces::activate(Sensor* input){
  if(enabled){return;}
  
  sensor = input;
  TravelingPieces::enabled = true;
}

void TravelingPieces::run(){
  // digitalWrite(13,HIGH); delay(100); digitalWrite(13,LOW);

  //check to see if sensor has been released
  if(sensor->check() == 0){
    released = true;
    locked = true;
  }

  leds[end].setHSV(hue,255,200);

  //starts cleanup
  if(released){
    leds[front].setHSV(hue,255,0);
  }
  
  if(end < NUM_LEDS){
    end++;
  }
  
  if(released && front < NUM_LEDS){
    front++;
  }
  
  //reset pattern
  if(front == NUM_LEDS){
    enabled = false;
    released = false;
    locked = false;
    front = 0; end = 0;
  }
  
  runned();
}

LightThread* TravelingPieces::getCopy(){
  return new TravelingPieces(*this);
}
