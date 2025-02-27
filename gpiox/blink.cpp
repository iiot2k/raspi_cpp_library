/*
 * example blinks output, blink period is switch with input
 *
 * build:
 * > make
 *
 * run:
 * > ./blink
 *
 * blink.cpp
 *
 */

#include <stdio.h>
#include <csignal>
#include <cstdlib>

#include "gpiox_lib.h"
using namespace gpiox;

#define INPUT_PIN  21
#define OUTPUT_PIN 20

#define DEBOUNCE_US 10000 // us
#define BLINK_TIME_MS_1 500 // ms
#define BLINK_TIME_MS_2 2500 // ms

// signal handler
void onCtrlC(int signum)
{
    puts("\nprogram stopped");
    exit(signum);
}

int main()
{
    signal(SIGINT, onCtrlC);

    puts("*** blink C++ example ***");
    puts("stop program with Ctrl+C");

    // init output pin
    init_gpio(OUTPUT_PIN, GPIO_MODE_OUTPUT, 0);

    // init input pin
    init_gpio(INPUT_PIN, GPIO_MODE_INPUT_PULLUP, DEBOUNCE_US);

    // blinks output depends on input
    if (get_gpio(INPUT_PIN))
        blink_gpio(OUTPUT_PIN, BLINK_TIME_MS_1);
    else
        blink_gpio(OUTPUT_PIN, BLINK_TIME_MS_2);

    while(1)
    {

    }
}
