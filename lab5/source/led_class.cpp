#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>
#include <string.h>
#include <iostream>

class GPIOPin {
  public:
    GPIOPin(int pin, bool input = true, bool pullup = true,
            bool invert = false);
    GPIOPin(const GPIOPin &) = delete;
    bool read() { return gpio_get(pin) ^ invert; };
    bool operator()();
    void write(bool value) { gpio_put(pin, value); };
    void operator()(bool);
    operator int();

  private:
    const int pin;
    const bool input;
    const bool pullup;
    const bool invert;
};

GPIOPin::GPIOPin(int pin, bool input, bool pullup, bool invert)
    : pin(pin), input(input), pullup(pullup), invert(invert) {
    gpio_init(pin);
    if (input) {
        gpio_set_dir(pin, GPIO_IN);
        if (pullup) {
            gpio_pull_up(pin);
        }
    } else {
        gpio_init(pin);
        gpio_set_dir(pin, GPIO_OUT);
        if (invert) {
            gpio_set_outover(pin, GPIO_OVERRIDE_INVERT);
        }
    }
};

class Led {
  public:
    Led(const int pin_num, bool is_on = false)
        : led_pin(GPIOPin(pin_num, false, false, false)), is_on(is_on) {
        if (is_on) {
            led_pin.write(true);
        }
    };
    bool get_state() { return led_pin.read(); };
    bool set_state(bool state);
    bool toggle();

  private:
    GPIOPin led_pin;
    bool is_on;
};

bool Led::toggle() {
    is_on = !is_on;
    led_pin.write(is_on);
    return is_on;
}

bool Led::set_state(bool state) {
    is_on = state;
    led_pin.write(is_on);
    return is_on;
}

class Switch {
  public:
    Switch(const int pin_num) : pin(GPIOPin(pin_num, true, true, true)) {}
    bool is_pressed() { return pin.read(); }

  private:
    GPIOPin pin;
};

class LightSwitch {
  public:
    LightSwitch(const int sw_pin, const int led_pin)
        : led(Led(led_pin)), sw(Switch(sw_pin)) {last_pressed = 0;}
    void update_self();

  private:
    Led led;
    Switch sw;
    uint32_t last_pressed;
};

void LightSwitch::update_self() {
    if (sw.is_pressed() && (time_us_32() / 1000 - last_pressed) > 1000) {
        last_pressed = time_us_32();
        led.set_state(true);
    } else {
        led.set_state(false);
    }
}

int main() { 

    LightSwitch led1 = LightSwitch(9, 20);
    LightSwitch led2 = LightSwitch(8, 21);
    LightSwitch led3 = LightSwitch(7, 22);

    while (true) {
        printf("Hello world!\n");
        led1.update_self();
        led2.update_self();
        led3.update_self();
        sleep_ms(10);
    }
    return 0;
}
