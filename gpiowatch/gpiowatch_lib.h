/*
 * 
 * (c) Derya Y. iiot2k@gmail.com
 *
 * Raspberry Pi gpiowatch c++ library
 *
 * the library uses the gpio character devices interface (V2) from the Linux operating system
 * 
 * link library with your application
 * gpiowatch_arm64.a on 64bit OS
 *
 * gpiowatch_lib.h
 *
 */

#pragma once

#include <stdint.h>

namespace gpiowatch {

// gpio mode
enum {
    GPIO_MODE_INPUT_NOPULL = 0,
    GPIO_MODE_INPUT_PULLDOWN,
    GPIO_MODE_INPUT_PULLUP,
};

// gpio mode
enum {
    GPIO_EDGE_RISING = 0,
    GPIO_EDGE_FALLING,
    GPIO_EDGE_BOTH,
};

/**
 * @brief gets error text after call functions
 * @returns error text
 */
const char* error_text();

/**
 * @brief stops pwm and deinit gpio
 * @param pin gpio pin (0..27)
 * @returns true on ok, false on error (error_text() returns reason)
 */
bool deinit_gpio(uint32_t pin);

/**
 * @brief gets gpio state
 * @param pin gpio pin (0..27)
 * @returns gpio state
 */
uint32_t get_gpio(uint32_t pin);

/**
 * @brief watch input callback function
 * @param state input state 0/1
 * @param edge GPIO_EDGE_RISING or GPIO_EDGE_FALLING
 * @param pin gpio pin (2..27)
 */
typedef void (*watch_cb)(uint32_t state, uint32_t edge, uint32_t pin);

/**
 * @brief watch gpio input for changes
 * @param pin gpio pin (0..27)
 * @param mode GPIO_MODE_INPUT_..
 * @param debounce time in ms, 0 disables debounce
 * @param edge GPIO_EDGE_RISING, GPIO_EDGE_FALLING or GPIO_EDGE_BOTH
 * @param cb watch input callback function
 * @returns true on ok, false on error
 */
bool watch_gpio(uint32_t pin, uint32_t mode, uint32_t debounce, uint32_t edge, watch_cb cb);

} // namespace
