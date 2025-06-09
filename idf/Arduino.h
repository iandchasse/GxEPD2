#ifndef ARDUINO_COMPAT_H
#define ARDUINO_COMPAT_H

#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_timer.h"
#include "esp_rom_sys.h"
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

// Basic constants
#define HIGH 1
#define LOW  0

#define INPUT GPIO_MODE_INPUT
#define OUTPUT GPIO_MODE_OUTPUT
#define INPUT_PULLUP GPIO_MODE_INPUT

static inline void pinMode(int pin, int mode)
{
    gpio_config_t io_conf = {0};
    io_conf.pin_bit_mask = 1ULL << pin;
    if (mode == OUTPUT) io_conf.mode = GPIO_MODE_OUTPUT;
    else io_conf.mode = GPIO_MODE_INPUT;
    gpio_config(&io_conf);
}

static inline void digitalWrite(int pin, int level)
{
    gpio_set_level((gpio_num_t)pin, level);
}

static inline int digitalRead(int pin)
{
    return gpio_get_level((gpio_num_t)pin);
}

static inline void delay(unsigned long ms)
{
    vTaskDelay(ms / portTICK_PERIOD_MS);
}

static inline void delayMicroseconds(unsigned int us)
{
    esp_rom_delay_us(us);
}

static inline unsigned long millis(void)
{
    return esp_timer_get_time() / 1000ULL;
}

static inline unsigned long micros(void)
{
    return esp_timer_get_time();
}

static inline void yield(void)
{
    vTaskDelay(0);
}

#ifdef __cplusplus
}
#endif

#endif // ARDUINO_COMPAT_H
