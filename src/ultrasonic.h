// ultrasonic.h
#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <stdint.h>
#include "pico/stdlib.h"

void ultrasonic_init(uint trigger_pin, uint echo_pin);
double ultrasonic_read_cm();

#endif

