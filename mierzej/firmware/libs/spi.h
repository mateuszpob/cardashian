#ifndef SPI
#define SPI

#include <avr/io.h>

#define SS              PB2
#define MOSI            PB3
#define MISO            PB4
#define SCK             PB5

void spi_master_init(void);

uint8_t spi_single(uint8_t byte);

void spi_multiple(uint8_t* dataout, uint8_t* datain, uint8_t len);

void spi_write(uint8_t* data, uint8_t length);

void spi_read(uint8_t* data, uint8_t length);

#endif