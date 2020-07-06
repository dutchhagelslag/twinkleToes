#include <Arduino.h>
#include <FastLED.h>
#include <Thread.h>
#include <StaticThreadController.h>

#include"TwinkleToe.h"

#define COLOR_ORDER GRB

const int NUM_LEDS = 50;
const int DATA_PIN = 3;
const int BRIGHTNESS = 96;
const int THREAD_RATE = 100;


CRGB leds[NUM_LEDS];

Thread darken(darkenFunction,50);

EffectController<Traveling> travelingController;

EffectController<TravelingPieces> pieces;

AnalogSensor analogSensor(A4);

TapSensor TapSensor(5);

HoldSensor hold(6,&pieces);

void setup() {

  delay(2000); //sanity check, youve got 2 seconds to get ur shit together

  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  FastLED.clear();
  FastLED.setBrightness(BRIGHTNESS);
  // fill_solid(leds,NUM_LEDS,CRGB::Red);
  // FastLED.show();
   
}

void loop(){

  // if(darken.shouldRun()){
  //   darken.run();
  // }

  if(TapSensor.check()){
    travelingController.add();
  }

  hold.check();
  
  travelingController.run();
  
  pieces.run();
  
  FastLED.show();
}
