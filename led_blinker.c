/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "slaves.h"
#include "blinker.h"

// main routine, ends with endless blinkloop
int main() {

    stdio_init_all();

    sleep_ms(10 * 1000); // wait for 10 seconds
    
    printf("started LED-blinker test + I2C-scanner\n\n");

    // init the onboard-LED
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    // init the I2C-interface
    // This example will use I2C0 on GPIO4 (SDA) and GPIO5 (SCL)
    i2c_init(i2c0, 100 * 1000);
    gpio_set_function(4, GPIO_FUNC_I2C);
    gpio_set_function(5, GPIO_FUNC_I2C);
    gpio_pull_up(4);
    gpio_pull_up(5);

    slowBlink();
    slowBlink();

    scanActiveSlaves();

    printf("Found slaves:\n");
    printf("=============\n");
    for (size_t i = 0; i < 10; i++)
    {
        if (slaves[i] > 0) {
            printf("%X\n", slaves[i]);
        }
    }

    while (true) {
        fastBlink();
        sleep_ms(1000);

        printf(".");
    }

}