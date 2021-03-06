/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

const uint LED_PIN = 25; // this is the standard on-board LED
const uint BLINK_FAST = 200; // half the period in ms
const uint BLINK_SLOW = 500; // half the period in ms

int slaves[10]; // space for max 10 scanned I2C-slaves
unsigned short int slaveCounter = 0; 

// I2C reserves some addresses for special purposes. We exclude these from the scan.
// These are any addresses of the form 000 0xxx or 111 1xxx
bool reserved_addr(uint8_t addr) {
    return (addr & 0x78) == 0 || (addr & 0x78) == 0x78;
}

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

void scanActiveSlaves(){
    
// copied from pico-examples blink , I2C, ....

    for (int addr = 0; addr < (1 << 7); ++addr) {

        // Perform a 1-byte dummy read from the probe address. If a slave
        // acknowledges this address, the function returns the number of bytes
        // transferred. If the address byte is ignored, the function returns
        // -1.

        // Skip over any reserved addresses.
        int ret;
        uint8_t rxdata;
        if (reserved_addr(addr))
            ret = PICO_ERROR_GENERIC;
        else
            ret = i2c_read_blocking(i2c0, addr, &rxdata, 1, false);

        if (ret >= 0) {
            slaves[slaveCounter] = addr;
            slaveCounter++;
        }    
    }

}

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