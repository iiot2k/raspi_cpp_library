/*
 * gpiox functions
 *
 * (c) Derya Y. iiot2k@gmail.com
 *
 * gpiox.h
 *
 */

#pragma once

#include <stdint.h>

/**
 * @brief returns Linux kernel name of this GPIO chip
 * @returns chip name
 */
const char* gpiox_get_chipname();

/**
 * @brief returns functional name for this GPIO chip
 * @returns chip label
 */
const char* gpiox_get_chiplabel();

/**
 * @brief initialized gpio pin with mode
 * @param pin pin number (0..27)
 * @param mode gpio mode (see gpiox_def.h)
 * @param setval debounce-time in us for inputs, state for outputs
 * @returns false on error, true on ok
 */
bool gpiox_init(uint32_t pin, uint32_t mode, uint32_t setval);

/**
 * @brief de-initialized gpio pin
 * @param pin pin number (0..27)
 * @returns false on error, true on ok
 */
bool gpiox_deinit(uint32_t pin);

/**
 * @brief reads gpio pin state
 * @param pin pin number (0..27)
 * @param val receives state as 0/1
 * @returns false on error, true on ok
 */
bool gpiox_read(uint32_t pin, uint32_t& val);

/**
 * @brief writesto gpio pin
 * @param pin pin number (0..27)
 * @param val state as 0/1 to set
 * @returns false on error, true on ok
 */
bool gpiox_write(uint32_t pin, uint32_t val);
