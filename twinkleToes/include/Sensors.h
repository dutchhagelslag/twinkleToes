#ifndef sensors_h
#define sensors_h

class Sensor{
 protected:
  int pin;
  
 public:
  Sensor(int pin);
  virtual int check()=0;

};

class AnalogSensor:public Sensor{
 public:
  AnalogSensor(int pin):Sensor(pin){}

  int check();  

};


class TapSensor:public Sensor{
 protected:
  bool stillPressed = false;
  unsigned long debounceTime = 0;
  uint16_t debounceInterval = 100;

 public:
  TapSensor(int pin):Sensor(pin){}

  int check();
};

class HoldSensor:public TapSensor{
public:
  HoldSensor(int pin):TapSensor(pin){}

  int check();
};

#endif
