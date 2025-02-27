/*
 * 
 * (c) Derya Y. iiot2k@gmail.com
 *
 * Raspberry Pi gpio c++ library
 * 
 * link library with your application
 * libgpiox_arm64.a on 64bit OS
 *
 * gpiox_lib.h
 *
 */

#pragma once

#include <stdint.h>

namespace gpiox {

/**
 * @brief gets error text after call functions
 * @returns error text
 */
const char* error_text();

/**
 * @brief gpio modes
 */
enum {
    GPIO_MODE_INPUT_NOPULL = 0, // floating input
    GPIO_MODE_INPUT_PULLDOWN,   // input with pull down resistor
    GPIO_MODE_INPUT_PULLUP,     // input with pull up resistor
    GPIO_MODE_OUTPUT,           // output
    GPIO_MODE_OUTPUT_SOURCE,    // output source, Hi-Z on 0, connect to +3.3V on 1
    GPIO_MODE_OUTPUT_SINK,      // output sink, Hi-Z on 0, connect to ground on 1
};

/**
 * @brief init gpio input/output with mode
 * @param pin gpio pin (0..27)
 * @param mode GPIO_MODE_INPUT_.. or GPIO_MODE_OUTPUT..
 * @param setval debounce time in us for inputs, 0/1 or true/false for output
 * @returns true on ok, false on error
 * @note setval 0 for inputs disables debounce
 */
bool init_gpio(uint32_t pin, uint32_t mode, uint32_t setval);

/**
 * @brief deinits gpio
 * @param pin gpio pin (0..27)
 * @returns true on ok, false on error
 *
 * @note GPIO pin is deinitialized when the program ends
 * @note stops also blink)
 */
bool deinit_gpio(uint32_t pin);

/**
 * @brief gets gpio state as boolean
 * @param pin gpio pin (0..27)
 * @returns true on active, false on deactive
 */
bool get_gpio(uint32_t pin);

/**
 * @brief get gpio state as number (0/1)
 * @param pin gpio pin (0..27)
 * @returns 1 on active, 0 on deactive
 */
uint32_t get_gpio_num(uint32_t pin);

/**
 * @brief set gpio output
 * @param pin gpio pin (0..27)
 * @param val state to set 0/1
 * @returns true on ok, false on error
 */
bool set_gpio(uint32_t pin, uint32_t val);

/**
 * @brief toggle (change state) of gpio output
 * @param pin gpio pin (0..27)
 * @returns true on ok, false on error
 */
bool toggle_gpio(uint32_t pin);

/**
 * @brief blink gpio output on period
 * @param pin gpio pin (0..27)
 * @param period blink period in ms (1..), 0 stops blink
 * @returns true on ok, false on error
 */
bool blink_gpio(uint32_t pin, uint32_t period);

/**
 * @brief stop gpio blink and set output to 0
 * @param pin gpio pin (0..27)
 * @returns true on ok, false on error
 * @note call of read/write/toggle functions stops also blink
 */
bool stop_blink_gpio(uint32_t pin);

} // namespace
