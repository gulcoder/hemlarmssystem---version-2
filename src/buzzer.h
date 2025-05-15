#ifndef BUZZER_H
#define BUZZER_H

#include "pico/stdlib.h"

#define BUZZER_PIN 15

void buzzer_init();
void buzzer_beep(int duration);

#endif
