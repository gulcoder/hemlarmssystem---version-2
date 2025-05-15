#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "wifi.h"

bool connect_to_wifi(const char* ssid, const char* password) {
    if (cyw43_arch_init()) {
        return false;
    }

    cyw43_arch_enable_sta_mode();

    if (cyw43_arch_wifi_connect_timeout_ms(ssid, password, CYW43_AUTH_WPA2_AES_PSK, 30000)) {
        return false;
    }

    return true;
}

