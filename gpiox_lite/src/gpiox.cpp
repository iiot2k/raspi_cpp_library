/*
 * gpiox functions
 *
 * (c) Derya Y. iiot2k@gmail.com
 *
 * gpiox.cpp
 *
 */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <poll.h>
#include <sys/ioctl.h>
#include <string.h>

#include "gpio.h"
#include "gpiox.h"
#include "gpiox_def.h"

//******* chip
// since kernel 6.6.45 all chip address is 0
#define CHIPNAME_CHIP0 "/dev/gpiochip0"

class c_chip
{
public:
    c_chip()
    {
        m_fd = -1;

        m_fd = open(CHIPNAME_CHIP0, O_RDWR | O_CLOEXEC);

        if (m_fd != -1)
        {
            memset(&m_info, 0, sizeof(m_info));

            if (ioctl(m_fd, GPIO_GET_CHIPINFO_IOCTL, &m_info) == -1)
            {
                close(m_fd);
                m_fd = -1;
            }
        }
    };

    ~c_chip()
    {
        if (m_fd != -1)
            close(m_fd);
    };


    inline int32_t get_fd() { return m_fd; }
    inline const char* get_name() { return m_info.name; }
    inline const char* get_label() { return m_info.label; }

private:
    int32_t m_fd;
    gpiochip_info m_info;
};

static c_chip chip;

//******* gpio

static void set_line_debounce_us(gpio_v2_line_config& line_config, uint32_t debounce_us)
{
    line_config.num_attrs = 1;
    line_config.attrs[0].mask = 1;
    line_config.attrs[0].attr.id = GPIO_V2_LINE_ATTR_ID_DEBOUNCE;
    line_config.attrs[0].attr.debounce_period_us = debounce_us;
}

static void set_line_value(gpio_v2_line_config& line_config, uint32_t setval)
{
    line_config.num_attrs = 1;
    line_config.attrs[0].mask = 1;
    line_config.attrs[0].attr.id = GPIO_V2_LINE_ATTR_ID_OUTPUT_VALUES;
    line_config.attrs[0].attr.values = setval > 0 ? 1 : 0;
}

static void set_mode(uint32_t mode, gpio_v2_line_config& line_config, uint32_t setval)
{
    switch(mode)
    {
    case GPIO_MODE_INPUT_NOPULL:
        line_config.flags = GPIO_V2_LINE_FLAG_INPUT + GPIO_V2_LINE_FLAG_BIAS_DISABLED;
        set_line_debounce_us(line_config, setval);
        break;

    default:
    case GPIO_MODE_INPUT_PULLDOWN:
        line_config.flags = GPIO_V2_LINE_FLAG_INPUT + GPIO_V2_LINE_FLAG_BIAS_PULL_DOWN;
        set_line_debounce_us(line_config, setval);
        break;

    case GPIO_MODE_INPUT_PULLUP:
        line_config.flags = GPIO_V2_LINE_FLAG_INPUT + GPIO_V2_LINE_FLAG_BIAS_PULL_UP + GPIO_V2_LINE_FLAG_ACTIVE_LOW;
        set_line_debounce_us(line_config, setval);
        break;

    case GPIO_MODE_OUTPUT:
        line_config.flags = GPIO_V2_LINE_FLAG_OUTPUT;
        set_line_value(line_config, setval);
        break;

    case GPIO_MODE_OUTPUT_SOURCE:
        line_config.flags = GPIO_V2_LINE_FLAG_OUTPUT + GPIO_V2_LINE_FLAG_OPEN_SOURCE;
        setval = 0;
        set_line_value(line_config, setval);
        break;

    case GPIO_MODE_OUTPUT_SINK:
        line_config.flags = GPIO_V2_LINE_FLAG_OUTPUT + GPIO_V2_LINE_FLAG_OPEN_DRAIN + GPIO_V2_LINE_FLAG_ACTIVE_LOW;
        set_line_value(line_config, setval);
        break;
    }
}

class c_gpio
{
public:
    c_gpio()
    {
        m_fd = -1;
    }

    ~c_gpio()
    {
        deinit();
    }

    void deinit();
    bool init(uint32_t pin, uint32_t mode, uint32_t setval);

    bool read(uint32_t& val);
    bool write(uint32_t val);

    inline int32_t get_fd() { return m_fd; }
    inline void set_fd(int32_t fd) { m_fd = fd; }

private:
    int32_t m_fd;
};

void c_gpio::deinit()
{
    if (get_fd() != -1)
        close(get_fd());

    set_fd(-1);
}

bool c_gpio::init(uint32_t pin, uint32_t mode, uint32_t setval)
{
    if (chip.get_fd() == -1)
        return false;

    deinit();

    gpio_v2_line_request line_request;

    memset(&line_request, 0, sizeof(line_request));

    line_request.num_lines = 1;
    line_request.offsets[0] = pin;

    set_mode(mode, line_request.config, setval);

    if (ioctl(chip.get_fd(), GPIO_V2_GET_LINE_IOCTL, &line_request) == -1)
        return false;

    if (line_request.fd < 0)
        return false;

    set_fd(line_request.fd);

    return true;
}

bool c_gpio::read(uint32_t& val)
{
    if (get_fd() == -1)
        return false;

    gpio_v2_line_values line_values;
    line_values.mask = 1;
    line_values.bits = 0;

    if (ioctl(get_fd(), GPIO_V2_LINE_GET_VALUES_IOCTL, &line_values) == -1)
        return false;

    val = (line_values.bits == 1) ? 1 : 0;

    return true;
}

bool c_gpio::write(uint32_t val)
{
    if (get_fd() == -1)
        return false;

    gpio_v2_line_values line_values;
    line_values.mask = 1;
    line_values.bits = val > 0 ? 1 : 0;

    if (ioctl(get_fd(), GPIO_V2_LINE_SET_VALUES_IOCTL, &line_values) == -1)
        return false;

    return true;
}

// pin
#define N_PIN 28
#define CHECKPIN(p) (p < N_PIN)

static c_gpio gpio_pin[N_PIN];

const char* gpiox_get_chipname()
{
    return chip.get_name();
}

const char* gpiox_get_chiplabel()
{
    return chip.get_label();
}

bool gpiox_init(uint32_t pin, uint32_t mode, uint32_t setval)
{
    if (!CHECKPIN(pin))
        return false;

    return gpio_pin[pin].init(pin, mode, setval);
}

bool gpiox_deinit(uint32_t pin)
{
    if (!CHECKPIN(pin))
        return false;

    gpio_pin[pin].deinit();

    return true;
}

bool gpiox_read(uint32_t pin, uint32_t& val)
{
    if (!CHECKPIN(pin))
        return false;

    return gpio_pin[pin].read(val);
}

bool gpiox_write(uint32_t pin, uint32_t val)
{
    if (!CHECKPIN(pin))
        return false;

    return gpio_pin[pin].write(val);
}
