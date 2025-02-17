/*
 * example turns output on and
 * depends of input after 3s or 1s off
 *
 * gpiox_lite.js
 *
 */

"use strict";

const gpiox_lite = require( "bindings" )( "gpiox_lite.node" );

const INPUT_PIN = 21;
const OUTPUT_PIN = 20;
const DEBOUNCE = 10 * 1000; // 10ms

console.log("chip name", gpiox_lite.chip_name());
console.log("chip label", gpiox_lite.chip_label());
console.log("*** on/off node.js example ***");
console.log("output pin is gpio", OUTPUT_PIN);
console.log("input pin is gpio", INPUT_PIN);

gpiox_lite.init_gpio(OUTPUT_PIN, gpiox_lite.GPIO_MODE_OUTPUT, 1);
gpiox_lite.init_gpio(INPUT_PIN, gpiox_lite.GPIO_MODE_INPUT_PULLUP, DEBOUNCE);

var ret = gpiox_lite.get_gpio(INPUT_PIN);

if (ret)
    console.log("output pin turns after 3s off");
else
    console.log("output pin turns after 1s off");

setTimeout(() => {
    gpiox_lite.set_gpio(OUTPUT_PIN, 0);
    gpiox_lite.deinit_gpio(OUTPUT_PIN);
    gpiox_lite.deinit_gpio(INPUT_PIN);
}, ret ? 3000 : 1000);
