#include "blinker.h"



// one cycle slow blink
void slowBlink() {

        gpio_put(LED_PIN, 1);
        sleep_ms(BLINK_SLOW);
        gpio_put(LED_PIN, 0);
        sleep_ms(BLINK_SLOW);

}

// one cycle fast blink
void fastBlink() {

        gpio_put(LED_PIN, 1);
        sleep_ms(BLINK_FAST);
        gpio_put(LED_PIN, 0);
        sleep_ms(BLINK_FAST);

}