#include "buzzer.h"
#include "pico/stdlib.h"
#include "hardware/pwm.h"

// Funktion för att initiera buzzer (använd rätt GPIO-pin definierad som BUZZER_PIN)
void buzzer_init() {
    gpio_init(BUZZER_PIN);  // Initiera pinnen
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);

}
void buzzer_beep(int duration) {
	gpio_put(BUZZER_PIN, 1);
	sleep_ms(duration);
	gpio_put(BUZZER_PIN, 0);
}

