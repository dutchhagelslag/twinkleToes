#include <Arduino.h>
#include <FastLED.h>
#include <Thread.h>
#include <StaticThreadController.h>

#include"lightThreads.h"
#include"EffectController.h"
CRGB leds[NUM_LEDS];

Thread darken(darkenFunction,50);

EffectController<Traveling> travelingController;

AnalogSensor analogSensor(4);

TapSensor TapSensor(5);

void setup() {

  delay(2000); //sanity check, youve got 2 seconds to get ur shit together

  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  FastLED.clear();
  FastLED.setBrightness(BRIGHTNESS);
  // fill_solid(leds,NUM_LEDS,CRGB::Red);
  // FastLED.show();
  int hueHold = 0;
  for(int i = 0; i < MAX_THREADS; i++){
    travelingController.array[i]->hue = hueHold;
    hueHold += 25;
  }
   
}

void loop(){

  if(darken.shouldRun()){
    darken.run();
  }

  if(TapSensor.check()){
    travelingController.add();
    
  }

  travelingController.run();
  
  FastLED.show();
}
