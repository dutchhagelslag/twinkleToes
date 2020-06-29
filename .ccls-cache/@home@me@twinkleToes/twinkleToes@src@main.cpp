#include <Arduino.h>
#include <FastLED.h>
#include <Thread.h>
#include <StaticThreadController.h>

#include"lightThreads.h"

CRGB leds[NUM_LEDS];

Thread darken(darkenFunction,100);

void setup() {

  delay(2000); //sanity check, youve got 2 seconds to get ur shit together

  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  FastLED.clear();
  FastLED.setBrightness(BRIGHTNESS);
  fill_solid(leds,NUM_LEDS,CRGB::Red);
  FastLED.show();
 
}

void loop(){

  if(darken.shouldRun()){
    darken.run();
  }
  
  FastLED.show();
}
