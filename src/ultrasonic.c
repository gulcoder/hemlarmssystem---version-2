// ultrasonic.c
#include "ultrasonic.h"
#include "pico/stdlib.h"
#include <stdio.h>

static uint trigger;
static uint echo;

void ultrasonic_init(uint trigger_pin, uint echo_pin) {
    trigger = trigger_pin;
    echo = echo_pin;
    
    gpio_init(trigger);
    gpio_init(echo);
    gpio_set_dir(trigger, 1); // output
    gpio_set_dir(echo, 0);    // input
}

double ultrasonic_read_cm() {
    absolute_time_t start_time, end_time;
    uint64_t duration;
    double distance_cm;

    gpio_put(trigger, 1);
    sleep_us(10);
    gpio_put(trigger, 0);

    while (!gpio_get(echo)) {
        tight_loop_contents();
    }
    start_time = get_absolute_time();

    while (gpio_get(echo)) {
        tight_loop_contents();
    }
    end_time = get_absolute_time();

    duration = absolute_time_diff_us(start_time, end_time);
    distance_cm = (duration * 0.0343) / 2;

    return distance_cm;
}

