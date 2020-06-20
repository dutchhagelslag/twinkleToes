#include <Arduino.h>
#include <FastLED.h>
#include<Thread.h>
#include<ThreadController.h>

#include"lightThreads.h"

CRGB leds[NUM_LEDS];

ThreadController threadcontroller(100);

DigitalSensor sensor1(2,&threadcontroller);

AnalogSensor sensor2(A2,&threadcontroller);

void darken(){
  fadeToBlackBy(leds, NUM_LEDS, 10);
}

void setup() {

  delay(2000); //sanity check, youve got 2 seconds to get ur shit together

  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  FastLED.clear();
  FastLED.setBrightness(BRIGHTNESS);

 
}

void loop(){
  sensor1.run();
  sensor2.run();
  
  threadcontroller.run();

  FastLED.show();
}
