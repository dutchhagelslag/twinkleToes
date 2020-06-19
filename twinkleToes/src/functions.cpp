#include<Arduino.h>  // kill w/ bit manipulation
#include <FastLED.h>
#include"ledFunctions.h"

// ------------------------------------------------------------\\

//               general purpose functions                     \\

// ------------------------------------------------------------\\

bool debounceInput(uint8_t pin, uint8_t functionIndex){
    // reads pin, if timer is zero adds new time, ends

    bool on = digitalRead(pin);

    if(!on){
        return false;
    }

    // time stored on debounceTimers
    if(on && debounceTimers[functionIndex] == 0){
        debounceTimers[functionIndex] = millis();
        return false;
    }

    // if timer is not zero, compare with interval -> return true
    
    uint16_t debounceInterval = 500;

    if(on && debounceTimers[functionIndex] > 0){
        if(millis() - debounceTimers[functionIndex] > debounceInterval){
            debounceTimers[functionIndex] = 0;
            return true;
        }
    }
    // p.s. if button press lands exactly when timer is zero it misses but idc? 
}


// ------------------------------------------------------------\\

//             operations[] altering functions                 \\

// ------------------------------------------------------------\\

// void fade(){
//     // uses operations[3][x]
//     operations[3][operations[3][0]] = NUM_LEDS;
//     operations[3][0] += 1;

// }

// void instantColor(){ 
//     // uses operations[2][x] 
//     operations[2][operations[2][0]] = NUM_LEDS;
//     operations[2][0] += 1;

// }

// void colorShift(){
//     // uses operations[1][x] 
//     operations[1][operations[1][0]] = NUM_LEDS;
//     operations[1][0] += 1;
// }

void colorRun(){ 
    // uses operations[0][x], elem = index
    if(operations[0][0] < OPERATIONS_LEN){
        operations[0][operations[0][0]] = 0;
        operations[0][0] += 1;
        }
    else{
        operations[0][1] = 0;
        operations[0][0] = 1;
    }
}

void runOperations(){
    //checks array and runs functions on values

    // checks colorRun, operation[0][i], basic rotation
    for(uint8_t i = 1; i < OPERATIONS_LEN; i++){
        if(operations[0][i] < NUM_LEDS){
            leds[operations[0][i]].setHSV(gHue,155,50);
            operations[0][i] += 1;
        }
        if(operations[0][i] == NUM_LEDS){
            leds[operations[0][i]] = CRGB::Black;
        }

    }
        gHue += 100;

    // for(uint8_t i = 0; i < OPERATION_LEN; i++){
        
    // }

    // for(uint8_t i = 0; i < OPERATION_LEN; i++){
        
    // }

    // for(uint8_t i = 0; i < OPERATION_LEN; i++){
        
    // }

    FastLED.show();
}
