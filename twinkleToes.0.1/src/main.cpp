#include <Arduino.h>
#include <FastLED.h>
#include"ledFunctions.h"

FASTLED_USING_NAMESPACE

uint8_t sensorPins[] = {2,3,4};

CRGB leds[NUM_LEDS];

Processes processes(1);

void setup() {
  delay(2000); //sanity check, youve got 2 seconds to get ur shit together
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  FastLED.clear();
  FastLED.setBrightness(BRIGHTNESS);

  for(uint8_t i = 0; i < sizeof(sensorPins); i++){
    pinMode(sensorPins[i], INPUT);
    };
}

void loop(){
  if(digitalRead(2)==HIGH && !processes.isFull()){
    processes.add(new ColorRun(5));
    }

  size_t index = processes.scan();
  if(index != 9999999){
    processes.remove(index);
  } 
  FastLED.show();
  }