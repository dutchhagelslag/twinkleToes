#include <Arduino.h>
#include <FastLED.h>
#include"ledFunctions.h"

FASTLED_USING_NAMESPACE

//rewrite with define macro if u need space, pin 3 is reserved 
uint8_t sensorPins[] = {2}; 

CRGB leds[NUM_LEDS];
CRGB ledCopy[NUM_LEDS];

//same indexes for the two lists
uint8_t operations[4][OPERATIONS_LEN];
unsigned long debounceTimers[OPERATIONS_LEN]; 

uint8_t gHue = 0;

void setup() {
  delay(2000); //sanity check, youve got 2 seconds to get ur shit together

  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  FastLED.clear();
  FastLED.setBrightness(BRIGHTNESS);

  //setup inputs
  for(uint8_t i = 0; i < sizeof(sensorPins); i++){
    pinMode(sensorPins[i], INPUT);
    };

  //set debounceTimers to ;
  for(uint8_t i = 0; i < OPERATIONS_LEN; i++){
    debounceTimers[i] = 0;
    };
  
  //set row[0] to leds length
  for(uint8_t i = 1; i < OPERATIONS_LEN; i++){
    operations[0][i] = NUM_LEDS;
    };
  
  //set operations' index 0 to 1
  for(uint8_t i = 0; i < 3; i++){
    operations[i][0] = 1;
    };
}

void loop(){

  if(debounceInput(2,COLOR_RUN_INDEX)){
    colorRun();
  }

  EVERY_N_MILLISECONDS(100){
    runOperations();
  }
}