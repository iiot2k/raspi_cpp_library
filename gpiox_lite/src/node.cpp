/*
 * n-api C++ node.js interface
 *
 * (c) Derya Y. iiot2k@gmail.com
 *
 * node.cpp
 *
 */

#include <napi.h>
using namespace Napi;

#include "gpiox.h"
#include "gpiox_def.h"

Value chip_name(const CallbackInfo &info)
{
    return String::New(info.Env(), gpiox_get_chipname());
}

Value chip_label(const CallbackInfo &info)
{
    return String::New(info.Env(), gpiox_get_chiplabel());
}

Value init_gpio(const CallbackInfo &info)
{
    uint32_t pin    = info[0].ToNumber().Uint32Value();
    uint32_t mode   = info[1].ToNumber().Uint32Value();
    uint32_t setval = info[2].ToNumber().Uint32Value();

    return Boolean::New(info.Env(), gpiox_init(pin, mode, setval));
}

Value deinit_gpio(const CallbackInfo &info)
{
    uint32_t pin = info[0].ToNumber().Uint32Value();

    return Boolean::New(info.Env(), gpiox_deinit(pin));
}

Value get_gpio(const CallbackInfo &info)
{
    uint32_t pin = info[0].ToNumber().Uint32Value();
    uint32_t val;

    if (!gpiox_read(pin, val))
        return info.Env().Undefined();

    return Boolean::New(info.Env(), val > 0);
}

Value set_gpio(const CallbackInfo &info)
{
    uint32_t pin = info[0].ToNumber().Uint32Value();
    uint32_t val = info[1].ToNumber().Uint32Value();

    return Boolean::New(info.Env(), gpiox_write(pin, val));
}

#define ADDFN(fn) exports.Set(#fn, Function::New(env, fn))
#define ADDNUM(num) exports.Set(#num, Number::New(env, num))

// exports functions and constants
Object export_all(Env env, Object exports)
{
    ADDFN(chip_name);
    ADDFN(chip_label);
    ADDFN(init_gpio);
    ADDFN(deinit_gpio);
    ADDFN(get_gpio);
    ADDFN(set_gpio);

    ADDNUM(GPIO_MODE_INPUT_NOPULL);
    ADDNUM(GPIO_MODE_INPUT_PULLDOWN);
    ADDNUM(GPIO_MODE_INPUT_PULLUP);
    ADDNUM(GPIO_MODE_OUTPUT);
    ADDNUM(GPIO_MODE_OUTPUT_SINK);
    ADDNUM(GPIO_MODE_OUTPUT_SOURCE);

    return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, export_all);



