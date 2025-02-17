/*
 * 
 * (c) Derya Y. iiot2k@gmail.com
 *
 * Raspberry Pi ds18b20 sensor c++ library
 *
 * the library uses the gpio character devices interface (V2) from the Linux operating system
 * 
 * link library with your application
 * libds18b20_arm64.a on 64bit OS
 *
 * ds18b20_lib.h
 *
 * Note: all functions are thread-safe
 *
 */

#pragma once

#include <vector>
#include <string>
using namespace std;

#include <stdint.h>

namespace ds18b20 {

/**
 * @brief gets error text after call functions
 * @returns error text
 */
const char* error_text();

/************** Sensor Functions **************
 * the functions reads the DS18B20 sensor temperatures
 * you can connect multiple sensors in parallel
 * it is important that a 4.7k pullup resistor is connected
 * the library does not support the parasite mode
 * please do not activate the linux 1-wire subsystem of the raspberry pi
 * for high-performance reading, all sensors must have set to the same resolution
 *
 * Resolution|Conversion Time|Temp. Steps|
 * ----------|---------------|-----------|
 * 9 bit     |94ms           |0.5°       |
 * 10 bit    |187ms          |0.25°      |
 * 11 bit    |375ms          |0.125°     |
 * 12 bit    |750ms          |0.0625°    |
 */

// sensor resolution
enum {
    RES_SENSOR_9 = 0, // 9 bit
    RES_SENSOR_10,    // 10 bit
    RES_SENSOR_11,    // 11 bit
    RES_SENSOR_12,    // 12 bit
};

// ivalid temperature used in sensor functions
#define INV_TEMP -9999.0

/**
 * @brief deinits pin gpio
 * @param pin gpio sensor pin (0..27)
 * @note Normally the GPIO pin is initialized when it is first used and deinitialized when the program ends.
 * @note The function is necessary if the pin is needed for other functions.
 */
void deinit_gpio(uint32_t pin);

/**
 * @brief sets sensor resolution on all sensors on 1-wire bus
 * @param pin gpio sensor pin (0..27)
 * @param res RES_SENSOR_..
 * @returns true on ok, false on error (error_text() returns reason)
 * @note default is 12bit resolution set.
 */
bool set_resolution(uint32_t pin, uint32_t res);

/**
 * @brief scan for sensors on pin and stores in internal list
 * @param pin gpio sensor pin (0..27)
 * @returns true on ok, false on error (error_text() returns reason)
 */
bool scan_sensor(uint32_t pin);

/**
 * @brief list all found sensors in internal list
 * @param pin gpio sensor pin (0..27)
 * @param sensor_list list of sensors id's in format 28-HHHHHHHHHHHH (hex)
 * @returns true on ok, false on error (error_text() returns reason)
 * @note scan_sensor is called if it has not been called before
 */
bool list_sensor(uint32_t pin, vector<string>& sensor_list);

/**
 * @brief get count of found sensors in internal list
 * @param pin gpio sensor pin (0..27)
 * @returns true on ok, false on error (error_text() returns reason)
 * @note scan_sensor must called before for update internal sensor list
 */
bool get_sensor_count(uint32_t pin, uint32_t& sensor_count);

/**
 * @brief read all sensors in internal sensor list
 * @param pin gpio sensor pin (0..27)
 * @param fh false: output is celsius, true: output is fahrenheit
 * @param temp_data sensor temperatures array
 * @returns true on ok, false on error (error_text() returns reason)
 * @note call set_resolution before
 * @note scan_sensor is called if it has not been called before
 * @note if the sensor is not read, the item is set to INV_TEMP
 */
bool read_sensor(uint32_t pin, bool fh, vector<double>& temp_data);

/**
 * @brief read one sensor with given id
 * @param pin gpio sensor pin (0..27)
 * @param id id of sensor in format 28-HHHHHHHHHHHH (hex)
 * @param fh false: output is celsius, true: output is fahrenheit
 * @param temp_data sensor temperature
 * @returns true on ok, false on error (error_text() returns reason)
 * @note call set_resolution before
 */
bool read_one_sensor(uint32_t pin, const char* id, bool fh, double& temp_data);

} // namespace
