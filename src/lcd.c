#include "lcd.h"
#include "hardware/i2c.h"
#include "pico/stdlib.h"
#include <string.h>

#define LCD_ADDR 0x27
#define I2C_PORT i2c0
#define SDA_PIN 4
#define SCL_PIN 5

#define LCD_BACKLIGHT 0x08
#define ENABLE 0x04

static void lcd_send_byte(uint8_t val, int mode);
static void lcd_toggle_enable(uint8_t val);
static void lcd_send_cmd(uint8_t cmd);
static void lcd_send_data(uint8_t data);

void lcd_init() {
    i2c_init(I2C_PORT, 100 * 1000);
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);

    sleep_ms(50);

    lcd_send_cmd(0x33);
    lcd_send_cmd(0x32);
    lcd_send_cmd(0x28);
    lcd_send_cmd(0x0C);
    lcd_send_cmd(0x06);
    lcd_send_cmd(0x01);
    sleep_ms(5);
}

void lcd_clear() {
    lcd_send_cmd(0x01);
    sleep_ms(2);
}

void lcd_set_cursor(uint8_t col, uint8_t row) {
    uint8_t row_offsets[] = {0x00, 0x40};
    lcd_send_cmd(0x80 | (col + row_offsets[row]));
}

void lcd_print(const char *str) {
    while (*str) {
        lcd_send_data(*str++);
    }
}

// Interna funktioner
static void lcd_send_byte(uint8_t val, int mode) {
    uint8_t high = (val & 0xF0) | LCD_BACKLIGHT | mode;
    uint8_t low = ((val << 4) & 0xF0) | LCD_BACKLIGHT | mode;
    lcd_toggle_enable(high);
    lcd_toggle_enable(low);
}

static void lcd_toggle_enable(uint8_t val) {
    i2c_write_blocking(I2C_PORT, LCD_ADDR, &val, 1, true);
    sleep_us(500);
    uint8_t en = val | ENABLE;
    i2c_write_blocking(I2C_PORT, LCD_ADDR, &en, 1, true);
    sleep_us(500);
    en &= ~ENABLE;
    i2c_write_blocking(I2C_PORT, LCD_ADDR, &en, 1, true);
    sleep_us(500);
}

static void lcd_send_cmd(uint8_t cmd) {
    lcd_send_byte(cmd, 0);
}

static void lcd_send_data(uint8_t data) {
    lcd_send_byte(data, 1);
}

