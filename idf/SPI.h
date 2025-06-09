#ifndef SPI_COMPAT_H
#define SPI_COMPAT_H

#include "driver/spi_master.h"
#include "Arduino.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MSBFIRST 1
#define LSBFIRST 0

#define SPI_MODE0 0
#define SPI_MODE1 1
#define SPI_MODE2 2
#define SPI_MODE3 3

typedef struct {
    uint32_t clock_speed_hz;
    uint8_t bit_order;
    uint8_t mode;
#ifdef __cplusplus
    SPISettings(uint32_t clock = 4000000, uint8_t order = MSBFIRST, uint8_t m = SPI_MODE0)
        : clock_speed_hz(clock), bit_order(order), mode(m) {}
#endif
} SPISettings;

#ifdef __cplusplus
}

class SPIClass {
public:
    spi_device_handle_t handle;
    spi_host_device_t host;
    int sck_pin, miso_pin, mosi_pin, cs_pin;
    uint32_t cur_speed;
    uint8_t cur_mode;

    explicit SPIClass(spi_host_device_t h=HSPI_HOST);
    void begin(int sck=-1, int miso=-1, int mosi=-1, int ss=-1);
    void end();
    void beginTransaction(SPISettings settings);
    void endTransaction();
    uint8_t transfer(uint8_t data);
    uint16_t transfer16(uint16_t data);
};

extern SPIClass SPI;
#endif

#endif // SPI_COMPAT_H
