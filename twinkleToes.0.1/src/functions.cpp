#include <Arduino.h>
#include <FastLED.h>
#include"ledFunctions.h"

bool FatherLights::timeToDie()const{return done;}
void FatherLights::die(){done = true;}


Queue::Queue(uint8_t arraySize):capacity(arraySize){
    data = new FatherLights*[arraySize];
    }
      
Queue::~Queue(){
    for(uint8_t i = 0; i < count; i++){
    delete data[front];
    front = (front+1)%capacity;
    }
    delete[] data;
    }
    
void Queue::enqueue(FatherLights* object) {
    if(isFull()){
        return;
    }
    data[rear] = object;
    rear = (rear+1)%capacity;
    count++;
}

FatherLights* Queue::pop(){
    if(isEmpty()){
        return nullptr;
    }
    FatherLights* hold = data[front];
    front = (front+1)%capacity;
    count--;      
    return hold;
}

bool Queue::isEmpty()const{return (count == 0);}
bool Queue::isFull()const{return (count == capacity);}


ColorRun::ColorRun(uint8_t color):color(color){};
        
bool ColorRun::timeToDie()const{return done;}

void ColorRun::work(){
//      leds[currentLed].setHue(color);
    if(currentLed > 1){
    leds[currentLed-1].fadeToBlackBy(64);
    }
    leds[currentLed] = CHSV(color,100,255);
    currentLed += 1;
    if(currentLed == NUM_LEDS){
    die();  
    }
    }


void ColorShift::work(){

}