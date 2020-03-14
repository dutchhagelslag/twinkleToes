#include <Arduino.h> // kill w/ bit manipulation
#include <FastLED.h>
#include"ledFunctions.h"

//       If you need space, comment out functions u dont use.

//================All Lights must obey FatherLights==================\\

bool FatherLights::timeToDie()const{return done;}
void FatherLights::die(){done = true;}

//===================================================================\\

Processes::Processes(uint8_t arraySize):capacity(arraySize){
    data = new FatherLights*[arraySize]; //rewrite for stack if low RAM
    }
      
void Processes::add(FatherLights* process) {
    
}

void Processes::remove(size_t index){
    data[index] = data[capacity-1]; 
    delete data[capacity-1];
    data[capacity-1] = nullptr;
}

size_t Processes::scan()const{
    for(size_t i = 0; i < capacity; i++){
        if(data[i]->timeToDie()){
            return i;
        }
    }
    return 9999999;
};

bool Processes::isFull()const{return (count == capacity);}

//===================================================================\\

ColorRun::ColorRun(uint8_t hue):hue(hue){};
        
bool ColorRun::timeToDie()const{return done;}

void ColorRun::work(){
//      leds[currentLed].setHue(color);
    if(currentLed > 1){
    leds[currentLed-1].fadeToBlackBy(64);
    }
    leds[currentLed] = CHSV(hue,70,255);
    currentLed += 1;
    if(currentLed == NUM_LEDS){
    die();  
    }
    }


void ColorShift::work(){

}

//=======================================================

