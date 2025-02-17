/*
 * 
 * (c) Derya Y. iiot2k@gmail.com
 *
 * Raspberry Pi software pwm c++ library
 *
 * the library uses the gpio character devices interface (V2) from the Linux operating system
 * 
 * link library with your application
 * swpwm_arm64.a on 64bit OS
 *
 * swpwm_lib.h
 *
 */

/************** Pulse Wide Modulation (PWM) functions **************
 *
 * pulse Wide Modulation is generated on output
 * PWM can be used for example to adjust the brightness of LEDs
 * because PWM is generated with software, the accuracy of dutycycle is accurate up to approximately 800Hz
 * for better accuracy use mode GPIO_MODE_PWM_REALTIME
 * in GPIO_MODE_PWM_REALTIME mode the CPU load is higher
 * the on+off time is 1/frequency (e.g. 1/100Hz = 10ms)
 * dutycycle means the % time for on
 * for example dutycycle 75% on 100Hz is 7.5ms on and 2.5ms off time
 * a dutycycle of 0% turns output off
 * a dutycycle of 100% turns output on
 */

#pragma once

#include <stdint.h>

namespace swpwm {

// pwm constants
#define DUTY_MIN 0      // min. duty cycle (%)
#define DUTY_MAX 100    // max. duty cycle (%)
#define FREQ_MIN 1      // min. pwm frequency (Hz)
#define FREQ_MAX 45000  // max. pwm frequency (Hz)

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
 * @brief gets pwm frequency
 * @param pin gpio pin (0..27)
 * @returns pwm frequency in Hz
 */
uint32_t get_pwm_frequency(uint32_t pin);

/**
 * @brief gets pwm duty-cycle
 * @param pin gpio pin (0..27)
 * @returns pwm duty cycle in %
 */
uint32_t get_pwm_dutycycle(uint32_t pin);

/**
 * @brief set pwm parameter
 * @param pin gpio pin (0..27)
 * @param frequency pwm frequency in Hz
 * @param dutycycle pwm duty cycle in %
 * @param realtime true: pwm in realtime
 * @returns true on ok, false on error (error_text() returns reason)
 */
bool set_pwm(uint32_t pin, uint32_t frequency, uint32_t dutycycle, bool realtime);

} // namespace
