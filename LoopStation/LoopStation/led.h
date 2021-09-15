#ifndef WS2812B_LED
#define WS2812B_LED

#include "FastLED.h"

#define NUM_LEDS_ROW 4
#define NUM_LEDS_COL 4
#define NUM_LEDS 16
#define LED_PIN 5

void led_init();
void led_light(int, int);
void led_reset(int, int);
void led_reset_row(int);
void led_reset_all(int);

#endif
