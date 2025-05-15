#include "pico/stdlib.h"
#include "led.h"

void led_init() {
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
}

void led_on(void) {
       	gpio_put(LED_PIN, 1);
}

void led_off(void) {
    gpio_put(LED_PIN, 0);
}


