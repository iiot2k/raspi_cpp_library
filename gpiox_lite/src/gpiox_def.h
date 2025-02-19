/*
 * gpio modes for gpiox_init
 *
 * (c) Derya Y. iiot2k@gmail.com
 *
 * gpiox_def.h
 *
 */

#pragma once

#include <stdint.h>

// gpio modes
enum {
    GPIO_MODE_INPUT_NOPULL = 0, // floating input, no input resistor
    GPIO_MODE_INPUT_PULLDOWN,   // pull-down resistor (true if connect +3.3V)
    GPIO_MODE_INPUT_PULLUP,     // pull-up resistor (true if connect to ground)
    GPIO_MODE_OUTPUT,           // output 
    GPIO_MODE_OUTPUT_SOURCE,    // output source (Hi-Z on false, connected to +3.3V on true)
    GPIO_MODE_OUTPUT_SINK,      // output sink (Hi-Z on false, connected to ground on true)
};
