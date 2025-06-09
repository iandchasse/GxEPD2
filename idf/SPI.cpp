#include "SPI.h"

#ifdef __cplusplus
SPIClass SPI;
#endif

SPIClass::SPIClass(spi_host_device_t h) : handle(NULL), host(h),
    sck_pin(-1), miso_pin(-1), mosi_pin(-1), cs_pin(-1),
    cur_speed(0), cur_mode(0) {}

void SPIClass::begin(int sck, int miso, int mosi, int ss)
{
    sck_pin = sck; miso_pin = miso; mosi_pin = mosi; cs_pin = ss;
    spi_bus_config_t buscfg = {};
    buscfg.miso_io_num = (miso >= 0) ? miso : -1;
    buscfg.mosi_io_num = (mosi >= 0) ? mosi : -1;
    buscfg.sclk_io_num = (sck >= 0) ? sck : -1;
    buscfg.quadwp_io_num = -1;
    buscfg.quadhd_io_num = -1;
    buscfg.max_transfer_sz = 4096;

    spi_bus_initialize(host, &buscfg, SPI_DMA_CH_AUTO);
}

void SPIClass::end()
{
    if (handle) {
        spi_bus_remove_device(handle);
        handle = NULL;
    }
    spi_bus_free(host);
}

void SPIClass::beginTransaction(SPISettings settings)
{
    // recreate device if parameters changed
    if (handle && (cur_speed != settings.clock_speed_hz || cur_mode != settings.mode)) {
        spi_bus_remove_device(handle);
        handle = NULL;
    }
    if (!handle) {
        spi_device_interface_config_t devcfg = {};
        devcfg.clock_speed_hz = settings.clock_speed_hz;
        devcfg.mode = settings.mode;
        devcfg.spics_io_num = -1; // CS handled manually
        devcfg.queue_size = 1;
        spi_bus_add_device(host, &devcfg, &handle);
        cur_speed = settings.clock_speed_hz;
        cur_mode = settings.mode;
    }
    spi_device_acquire_bus(handle, portMAX_DELAY);
}

void SPIClass::endTransaction()
{
    if (handle) {
        spi_device_release_bus(handle);
    }
}

uint8_t SPIClass::transfer(uint8_t data)
{
    spi_transaction_t t = {};
    uint8_t rx = 0;
    t.length = 8;
    t.tx_buffer = &data;
    t.rx_buffer = &rx;
    spi_device_polling_transmit(handle, &t);
    return rx;
}

uint16_t SPIClass::transfer16(uint16_t data)
{
    spi_transaction_t t = {};
    uint16_t rx = 0;
    t.length = 16;
    t.tx_buffer = &data;
    t.rx_buffer = &rx;
    spi_device_polling_transmit(handle, &t);
    return rx;
}

