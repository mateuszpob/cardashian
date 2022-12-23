#include "spi.h"

void spi_master_init(void) {
    /* Set MOSI and SCK output, all others input */
    DDRB = (1 << MOSI) | (1 << SCK) | (1 << SS);
    /* Enable SPI, Master, set clock rate */
    SPCR = (1 << SPE) | (0 << SPIE) | (1 << MSTR) | (1 << SPR0) | (0 << SPR1);
}

uint8_t spi_single(uint8_t byte) {
    SPDR = byte;
    while (!(SPSR & (1 << SPIF)));
    return SPDR;
}

void spi_multiple(uint8_t* dataout, uint8_t* datain, uint8_t len) {
    uint8_t i;

    for (i = 0; i < len; i++) {
        datain[i] = spi_single(dataout[i]);
    }

}

void spi_write(uint8_t* data, uint8_t length) {
    uint8_t i;
    for (i = 0; i < length; i++) {
        spi_single(data[i]);
    }
}

void spi_read(uint8_t* data, uint8_t length) {
    uint8_t i;
    for (i = 0; i < length; i++) {
        data[i] = spi_single(0);
    }
}
