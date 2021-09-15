#include "led.h"

CRGB leds[NUM_LEDS];

void led_init() { 
  FastLED.addLeds<WS2812B, LED_PIN, RGB>(leds, NUM_LEDS); 
}

void led_light(int col, int row) {
  int pos = col*NUM_LEDS_COL + row;
  leds[pos] = CRGB::Blue;
  FastLED.show();
}

void led_reset(int col, int row) {
  int pos = col*NUM_LEDS_COL + row;
  leds[pos] = CRGB::Black;
  FastLED.show();
}

void led_reset_row(int col){
  for (unsigned i = col*NUM_LEDS_COL; i < NUM_LEDS_COL; i++){
    Serial.println(i);
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}

void led_reset_all(){
  for (unsigned i = 0; i < NUM_LEDS; i++){
    leds[i] = CRGB::Black;
  }
  FastLED.show();
}
