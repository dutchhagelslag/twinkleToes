#include<Thread.h>
#include<FastLED.h>
#include<Arduino.h>

#include"Configuration.h"
#include"Sensors.h"


Sensor::Sensor(int pin):pin(pin){
  pinMode(pin,INPUT);
}

int AnalogSensor::check(){
  return map(analogRead(pin),0,1023,0,255);
}


int TapSensor::check(){   
   // reads pin, if timer is zero adds new time,
  bool on = digitalRead(pin);
  
  if(!on){
    stillPressed = false;
    return 0;
  }
   
  // time stored on debounceTimers
  else if(on && debounceTime == 0){
    debounceTime = millis();
    return 0;
  }
   
  // if timer is not zero, compare with interval -> return true    
  else if(on && millis() - debounceTime > debounceInterval && stillPressed == false){
    debounceTime = 0;
    stillPressed = true;    
    return 1;
  }
  return 0;
}

int HoldSensor::check(){
  bool on = digitalRead(pin);

  if(!on){
    stillPressed = false;
    return false;
  }
   
  else if(on && debounceTime == 0){
    debounceTime = millis();
    return false;
  }
   
  else if(on && millis() - debounceTime > debounceInterval){
    debounceTime = 0;
    return true;
  }
  return false;
}
