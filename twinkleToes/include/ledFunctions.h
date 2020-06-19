#ifndef ledFunctions_h
#define ledFunctions_h

#include<Arduino.h>  // kill w/ bit manipulation
#include <FastLED.h>

#define NUM_LEDS 30
#define OPERATIONS_LEN 30

#define DATA_PIN 10 // for micro
// #define DATA_PIN 3  // for nano

#define BRIGHTNESS          96
#define FRAMES_PER_SECOND  120

#define COLOR_RUN_INDEX 0
#define COLOR_SHIFT__INDEX 1
#define INSTANT_COLOR_INDEX 2
#define FADE_INDEX 3


extern struct CRGB leds[];
extern struct CRGB ledCopy[];
extern unsigned long debounceTimers[];

extern uint8_t operations[][OPERATIONS_LEN];
extern uint8_t gHue;
// ------------------------------------------------------------\\

//               general purpose functions                     \\

// ------------------------------------------------------------\\

bool debounceInput(uint8_t pin, uint8_t functionIndex);


// ------------------------------------------------------------\\

//             operations[] altering functions                 \\

// ------------------------------------------------------------\\

// void fade(){
//     // uses operations[3][x]

// }

// void instantColor(){ 
//     // uses operations[2][x] 

// }

// void colorShift(){
//     // uses operations[1][x] 
// }

void colorRun();

void runOperations();

#endif