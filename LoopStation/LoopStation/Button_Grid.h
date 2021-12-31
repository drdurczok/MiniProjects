#ifndef BUTTON_GRID
#define BUTTON_GRID

#include <Arduino.h>
#include "led.h"

#define NUM_BUTTONS_PER_COL 4

void button_grid_init();
void isPressed();

#endif
