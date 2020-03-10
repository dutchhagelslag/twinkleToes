#include <Arduino.h>
#include <FastLED.h>
#include"ledFunctions.h"

FASTLED_USING_NAMESPACE

#define NUM_LEDS 30
#define DATA_PIN 9
#define BRIGHTNESS          96
#define FRAMES_PER_SECOND  120
#define SENSOR_PIN 2

CRGB leds[NUM_LEDS];

Queue colorRuns(5);

void setup() {
  delay(2000); //sanity check, youve got 2 seconds to get ur shit together
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  FastLED.clear();
  FastLED.setBrightness(BRIGHTNESS);
  pinMode(SENSOR_PIN, INPUT);
}

void loop(){
  if(digitalRead(2)==HIGH){
    colorRuns.enqueue(new ColorRun(5));
    }
  FastLED.show();
  }