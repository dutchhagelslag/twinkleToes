#include <FastLED.h>

FASTLED_USING_NAMESPACE

#define NUM_LEDS 20
#define DATA_PIN 9
#define BRIGHTNESS          96
#define FRAMES_PER_SECOND  120

uint8_t gHue = 0;

CRGB leds[NUM_LEDS];

void setup() {
  delay(2000);
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  FastLED.clear();
  FastLED.setBrightness(BRIGHTNESS);

  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);

}

void toBlack(int timer){
  for(size_t i = 0; i < 51; i++){
      for(size_t i = 0; i < NUM_LEDS; i++){
          leds[i] -= CRGB(5,5,5);
        }
        delay(timer);
        FastLED.show();

  }
}

void colorRun(CRGB::HTMLColorCode color){
    for(size_t i = 0; i < NUM_LEDS; i += 1){
      leds[i] = color;
      FastLED.show();
      delay(20);
    }  
  }
  
void reverseColorRun(CRGB::HTMLColorCode color){
    for(size_t i = NUM_LEDS+1; i > 0; i -= 1){
      leds[i] = color;
      FastLED.show();
      delay(20);
    }  
  }

void flash(){
  
  }

void loop() {
//  fill_rainbow( leds, NUM_LEDS, gHue, 7);
//  FastLED.show();  
//  FastLED.delay(1000/FRAMES_PER_SECOND); 

  EVERY_N_MILLISECONDS( 20 ) { gHue++; }
  
     if(digitalRead(2)==HIGH){
     colorRun(255);
//     flash(CRGB::Blue);
     delay(100);
     toBlack(10);
     delay(100);
     }
     if(digitalRead(3)==HIGH){
     colorRun(CRGB::Red);
     delay(100);
     toBlack(10);
     delay(100);
     }
     if(digitalRead(4)==HIGH){
     reverseColorRun(CRGB::Green);
     delay(100);
     toBlack(10);
     delay(100);
     }
}
