#include <Arduino.h>
#include <FastLED.h>
#include <Thread.h>
#include <StaticThreadController.h>

#include"TwinkleToe.h"

#define COLOR_ORDER GRB

const int NUM_LEDS = 50;
const int DATA_PIN = 3;
const int BRIGHTNESS = 96;
const int THREAD_RATE = 10;


CRGB leds[NUM_LEDS];

Thread darken(darkenFunction,100);

EffectController<SpeedTraveling> travelingController;

EffectController<TravelingPieces> pieces;

AnalogSensor sensitive(A4);

TapSensor tap(5);

void setup() {

  delay(2000); //sanity check, youve got 2 seconds to get ur shit together

  pinMode(13,OUTPUT);
  
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  FastLED.clear();
  FastLED.setBrightness(BRIGHTNESS);
  // fill_solid(leds,NUM_LEDS,CRGB::Red);
  // FastLED.show();

  for(int i = 0; i < MAX_THREADS; i++){
    travelingController.array[i]->setHue(10*i);
    }
  
  travelingController.attachSensor(sensitive);
  // travelingController.attachSensor(tap);
}

void loop(){

  if(darken.shouldRun()){
    darken.run();
  }

  travelingController.check();
  
  if(travelingController.shouldRun()){
    travelingController.run();
  }
  
  FastLED.show();
}
