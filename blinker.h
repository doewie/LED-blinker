#ifndef DOEWIE_BLINKER_H
#define DOEWIE_BLINKER_H

#include "pico/stdlib.h";

const uint LED_PIN = 25; // this is the standard on-board LED
const uint BLINK_FAST = 200; // half the period in ms
const uint BLINK_SLOW = 500; // half the period in ms

void slowBlink();
void slowBlink();

#endif