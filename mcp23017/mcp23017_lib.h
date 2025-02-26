/*
 * C++ library for mcp23017 16-Bit I2C I/O Expander with Serial Interface
 *
 * (c) Derya Y. iiot2k@gmail.com
 *
 * link libraries on build:
 * libmcp23017_arm64.a for 64bit OS
 *
 * mcp23017_lib.h
 *
 */

#pragma once

#include <stdint.h>

#include <vector>
using namespace std;

namespace mcp23017 {

/**
 * i2c address
 */
enum {
    ADR_20 = 0, // 0x20
    ADR_21,     // 0x21
    ADR_22,     // 0x22
    ADR_23,     // 0x23
    ADR_24,     // 0x24
    ADR_25,     // 0x25
    ADR_26,     // 0x26
    ADR_27,     // 0x27
};

/**
 * port address
 */
enum {
    PORT_A = 0, // addresses port A
	PORT_B,		// addresses port B
	PORT_AB,	// addresses port A and B
    PORT_8,     // addresses port of mcp23008
};

/**
 * port mode
 */
enum {
    INPUT = 0, 		// pin is input (default on reset)
    INPUT_INV,		// pin is inverted input
    INPUT_PULL,		// pin is input with pullup-resistor
    INPUT_PULL_INV,	// pin is input inverted with pullup-resistor
    OUTPUT, 		// pin is output set inactive
};

/**
 * interrupt mode
 */
enum {
    INT_OFF = 0,  // interrupt off (default on reset)
    INT_ON,       // interrupt on
};

/**
 * @brief gets error text after call functions
 * @returns error text
 */
const char* error_text();

/**
 * @brief sets mcp23017 port mode for each pin
 * @param i2c_port i2c port (0..9)
 * @param adr i2c address (ADR_..)
 * @param port_adr selects port (PORT_A ..)
 * @param mode_arr mode values (INPUT..) as array
 * @returns true: ok, false: error
 *
 * @note INT pin is set to open-drain (set on active to low)
 * @note resets also interrupt
 *
 * @note if port_adr = PORT_A modes_arr array where index 0=GPA0..7=GPA7
 * @note if port_adr = PORT_B modes_arr array where index 0=GPB0..7=GPB7
 * @note if port_adr = PORT_AB modes_arr array where index 0=GPA0..7=GPA7, 8=GPB0 15=GPB7
 * @note if port_adr = PORT_8 modes_arr array where index 0=GP0..7=GP7 (mcp23008)
 */
bool set_mode(uint8_t i2c_port, uint8_t adr, uint8_t port_adr, vector<uint8_t>& mode_arr);

/**
 * @brief sets mcp23017 port mode for all pins
 * @param i2c_port i2c port (0..9)
 * @param adr i2c address (ADR_..)
 * @param port_adr selects port (PORT_A ..)
 * @param mode value (INPUT..) as number
 * @returns true: ok, false: error
 *
 * @note INT pin is set to open-drain (set on active to low)
 * @note resets also interrupt
 *
 * @note if port_adr = PORT_A port A is set
 * @note if port_adr = PORT_B port B is set
 * @note if port_adr = PORT_AB port A and port B is set
 * @note if port_adr = PORT_8 port is set (mcp23008)
 */
bool set_mode(uint8_t i2c_port, uint8_t adr, uint8_t port_adr, uint8_t mode);

/**
 * @brief sets mcp23017 interrupt mode for each pin
 * @param i2c_port i2c port (0..9)
 * @param adr i2c address (ADR_..)
 * @param port_adr selects port (PORT_A ..)
 * @param mode_arr interrupt mode values (INT_OFF, INT_ON) as array
 * @returns true: ok, false: error
 *
 * @note INT pin is set to open-drain (set on active to low)
 * @note resets also interrupt
 *
 * @note if port_adr = PORT_A modes_arr array where index 0=GPA0..7=GPA7
 * @note if port_adr = PORT_B modes_arr array where index 0=GPB0..7=GPB7
 * @note if port_adr = PORT_AB modes_arr array where index 0=GPA0..7=GPA7, 8=GPB0 15=GPB7
 * @note if port_adr = PORT_8 modes_arr array where index 0=GP0..7=GP7 (mcp23008)
 */
bool set_interrupt_mode(uint8_t i2c_port, uint8_t adr, uint8_t port_adr, vector<uint8_t>& mode_arr);

/**
 * @brief sets mcp23017 interrupt mode for all pins
 * @param i2c_port i2c port (0..9)
 * @param adr i2c address (ADR_..)
 * @param port_adr selects port (PORT_A ..)
 * @param mode interrupt mode value (INT_OFF, INT_ON)
 * @returns true: ok, false: error
 *
 * @note INT pin is set to open-drain
 * @note resets also interrupt
 *
 * @note if port_adr = PORT_A port A is set
 * @note if port_adr = PORT_B port B is set
 * @note if port_adr = PORT_AB port A and port B is set
 * @note if port_adr = PORT_8 port is set (mcp23008)
 */
bool set_interrupt_mode(uint8_t i2c_port, uint8_t adr, uint8_t port_adr, uint8_t mode);

/**
 * @brief reads mcp23017 interrupt state and returns array
 * @param i2c_port i2c port (0..9)
 * @param adr i2c address (ADR_..)
 * @param port_adr selects port (PORT_A ..)
 * @param int_state interrupt state as array
 * @returns true: ok, false: error
 *
 * @note if array element is 1 then interrupt occurs on that pin
 *
 * @note if port_adr = PORT_A int_data array where index 0=GPA0..7=GPA7
 * @note if port_adr = PORT_B int_data array where index 0=GPB0..7=GPB7
 * @note if port_adr = PORT_AB int_data array where index 0=GPA0..7=GPA7, 8=GPB0 15=GPB7
 * @note if port_adr = PORT_8 int_data array where index 0=GP0..7=GP7 (mcp23008)
 */
bool get_interrupt_state(uint8_t i2c_port, uint8_t adr, uint8_t port_adr, vector<uint8_t>& int_state);

/**
 * @brief reads mcp23017 interrupt state and returns number
 * @param i2c_port i2c port (0..9)
 * @param adr i2c address (ADR_..)
 * @param port_adr selects port (PORT_A ..)
 * @param int_state interrupt state as number
 * @returns true: ok, false: error
 *
 * @note if bit is 1 then interrupt occurs on that pin
 *
 * @note if port_adr = PORT_A int_data is bit0=GPA0..bit7=GPA7
 * @note if port_adr = PORT_B int_data is bit0=GPB0..bit7=GPB7
 * @note if port_adr = PORT_AB int_data is bit0=GPA0..bit7=GPA7, bit8=GPB0..bit15=GPB7
 * @note if port_adr = PORT_8 int_data is bit0=GP0..bit7=GP7 (mcp23008)
 */
bool get_interrupt_state(uint8_t i2c_port, uint8_t adr, uint8_t port_adr, uint16_t& int_state);

/**
 * @brief reads mcp23017 port and returns array
 * @param i2c_port i2c port (0..9)
 * @param adr i2c address (ADR_..)
 * @param port_adr selects port (PORT_A ..)
 * @param port_data port values as array
 * @returns true: ok, false: error
 *
 * @note if array element is 1 then pin is high
 * @note resets also interrupt
 *
 * @note if port_adr = PORT_A port_data array where index 0=GPA0..7=GPA7
 * @note if port_adr = PORT_B port_data array where index 0=GPB0..7=GPB7
 * @note if port_adr = PORT_AB port_data array 16 where index 0=GPA0..7=GPA7, 8=GPB0 15=GPB7
 * @note if port_adr = PORT_8 port_data array where index 0=GP0..7=GP7 (mcp23008)
 */
bool read_port(uint8_t i2c_port, uint8_t adr, uint8_t port_adr, vector<uint8_t>& port_data);

/**
 * @brief reads mcp23017 port and returns number
 * @param i2c_port i2c port (0..9)
 * @param adr i2c address (ADR_..)
 * @param port_adr selects port (PORT_A ..)
 * @param port_data port values as number
 * @returns true: ok, false: error
 *
 * @note if bit is 1 then pin is high
 * @note resets also interrupt
 *
 * @note if port_adr = PORT_A port_data is bit0=GPA0..bit7=GPA7
 * @note if port_adr = PORT_B port_data is bit0=GPB0..bit7=GPB7
 * @note if port_adr = PORT_AB port_data is bit0=GPA0..bit7=GPA7, bit8=GPB0..bit15=GPB7
 * @note if port_adr = PORT_8 port_data is bit0=GP0..bit7=GP7 (mcp23008)
 */
bool read_port(uint8_t i2c_port, uint8_t adr, uint8_t port_adr, uint16_t& port_data);

/**
 * @brief writes to mcp23017 port from array
 * @param i2c_port i2c port (0..9)
 * @param adr i2c address (ADR_..)
 * @param port_adr selects port (PORT_A ..)
 * @param port_data port values as array
 * @returns true: ok, false: error
 *
 * @note if array element is 1 then pin is high
 *
 * @note if port_adr = PORT_A port_data array where index 0=GPA0..7=GPA7
 * @note if port_adr = PORT_B port_data array where index 0=GPB0..7=GPB7
 * @note if port_adr = PORT_AB port_data array where index 0=GPA0..7=GPA7, 8=GPB0 15=GPB7
 * @note if port_adr = PORT_8 port_data array where index 0=GP0..7=GP7 (mcp23008)
 */
bool write_port(uint8_t i2c_port, uint8_t adr, uint8_t port_adr, vector<uint8_t>& port_data);

/**
 * @brief writes to mcp23017 port from number
 * @param i2c_port i2c port (0..9)
 * @param adr i2c address (ADR_..)
 * @param port_adr selects port (PORT_A ..)
 * @param port_data port values as number
 * @returns true: ok, false: error
 *
 * @note if bit is 1 then pin is high
 *
 * @note if port_adr = PORT_A port_data is bit0=GPA0..bit7=GPA7
 * @note if port_adr = PORT_B port_data is bit0=GPB0..bit7=GPB7
 * @note if port_adr = PORT_AB port_data is bit0=GPA0..bit7=GPA7, bit8=GPB0..bit15=GPB7
 * @note if port_adr = PORT_8 port_data is bit0=GP0..bit7=GP7 (mcp23008)
 */
bool write_port(uint8_t i2c_port, uint8_t adr, uint8_t port_adr, uint16_t port_data);

/**
 * @brief interrupt callback function
 * @param gpio_pin gpio pin (0..27)
 */
typedef void (*interrupt_cb)(uint32_t gpio_pin);

/**
 * @brief init gpio interrupt
 * @param gpio_pin gpio pin (0..27)
 * @param cb interrupt callback function
 * @returns true: ok, false: error
 * @note gpio pin is initalized to input, pullup and sense falling edge
 */
bool init_gpio_interrupt(uint32_t gpio_pin, interrupt_cb cb);

/**
 * @brief stops interrupt and deinits gpio
 * @param gpio_pin gpio pin (0..27)
 * @returns true: ok, false: error
 */
bool deinit_gpio_interrupt(uint32_t gpio_pin);

} // namespace
