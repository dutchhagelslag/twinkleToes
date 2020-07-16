#include <Arduino.h>
#include <FastLED.h>
#include <Thread.h>

#include"TwinkleToe.h"

#define COLOR_ORDER GRB

const int NUM_LEDS = 50;
const int DATA_PIN = 3;
const int BRIGHTNESS = 96;
const int THREAD_RATE = 100;

CRGB leds[NUM_LEDS];

Thread darken(darkenFunction,100);

SpeedTraveling speed();

TravelingPieces pieces();

EffectController<Traveling> travelingController;

// EffectController<TravelingPieces> pieces;

AnalogSensor sensitive(A4);

// HoldSensor hold(5);

TapSensor tap(5);

void setup() {

  pinMode(13,OUTPUT);
  
  //sanity check
  delay(2000); 

  //Setting up FastLED
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  FastLED.clear();
  FastLED.setBrightness(BRIGHTNESS);

  //Configure individual lightThreads which are exposed in the EffectController
  //MAX_THREADS is the amount of threads held by the controller
  //This can be configured in Configuration.h
  for(int i = 0; i < MAX_THREADS; i++){
    travelingController.array[i]->setHue(20*i);
  }

  travelingController.array[2]->setStart(6);
  
  for(int i = 1; i < MAX_THREADS; i+=2){
    travelingController.array[i]->setStart(NUM_LEDS);
    travelingController.array[i]->setEnd(0);
    travelingController.array[i]->reverse();
  }

  travelingController.array[3]->setStart(15);

  //Attach sensors to effectcontrollers
  // pieces.attachSensor(hold);
  //travelingController.attachSensor(sensitive);
  travelingController.attachSensor(tap);
}

void loop(){

  // For a gradual fade on all LEDs
  if(darken.shouldRun()){
    darken.run();
  }

  // travelingController.check();
  // if(travelingController.shouldRun()){
  //   travelingController.run();
  // }

  // pieces.check();

  // if(pieces.shouldRun()){
  //   pieces.run();
  // }

  travelingController.check();
  travelingController.run();
  
  FastLED.show();
}
