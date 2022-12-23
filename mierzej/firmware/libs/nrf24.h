/*
* ----------------------------------------------------------------------------
* “THE COFFEEWARE LICENSE” (Revision 1):
* <ihsan@kehribar.me> wrote this file. As long as you retain this notice you
* can do whatever you want with this stuff. If we meet some day, and you think
* this stuff is worth it, you can buy me a coffee in return.
* -----------------------------------------------------------------------------
* This library is based on this library: 
*   https://github.com/aaronds/arduino-nrf24l01
* Which is based on this library: 
*   http://www.tinkerer.eu/AVRLib/nRF24L01
* -----------------------------------------------------------------------------
*/
#ifndef NRF24
#define NRF24

#include "spi.h"
#include "nRF24L01.h"
#include "common.h"
#include <stdint.h>
#include <util/delay.h>

#define CSN_hi          PORTC |= (1<<PC1)
#define CSN_lo          PORTC &= ~(1<<PC1)
#define CE_hi           PORTC |= (1<<PC0)
#define CE_lo           PORTC &= ~(1<<PC0)
#define NRF_ON          PORTC |= (1<<PC2)
#define NRF_OFF         PORTC &= ~(1<<PC2)

#define nrf24_ADDR_LEN 5
#define nrf24_CONFIG ((1<<EN_CRC)|(0<<CRCO))

#define NRF24_TRANSMISSON_OK 0
#define NRF24_MESSAGE_LOST   1

/* adjustment functions */
void    nrf24_init(void);
void    nrf24_rx_address(uint8_t* adr, uint8_t rx_addr_2);
void    nrf24_tx_address(uint8_t* adr);
void    nrf24_config(uint8_t channel);

/* state check functions */
uint8_t nrf24_dataReady(void);
uint8_t nrf24_isSending(void);
uint8_t nrf24_getStatus(void);
uint8_t nrf24_rxFifoEmpty(void);

/* core TX / RX functions */
void    nrf24_send(uint8_t* value, uint8_t len);
uint8_t nrf24_getData(uint8_t* data);

/* post transmission analysis */
uint8_t nrf24_lastMessageStatus(void);
uint8_t nrf24_retransmissionCount(void);

/* Returns the payload length */
uint8_t nrf24_payload_length(void);

/* power management */
void    nrf24_powerUpRx(void);
void    nrf24_powerUpTx(void);
void    nrf24_powerDown(void);

/* low level interface ... */
uint8_t spi_transfer(uint8_t tx);
void    nrf24_transmitSync(uint8_t* dataout,uint8_t len);
void    nrf24_transferSync(uint8_t* dataout,uint8_t* datain,uint8_t len);
void    nrf24_configRegister(uint8_t reg, uint8_t value);
void    nrf24_readRegister(uint8_t reg, uint8_t* value, uint8_t len);
void    nrf24_writeRegister(uint8_t reg, uint8_t* value, uint8_t len);

uint8_t hack;

/* -------------------------------------------------------------------------- */
/* You should implement the platform spesific functions in your code */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* In this function you should do the following things:
 *    - Set MISO pin input
 *    - Set MOSI pin output
 *    - Set SCK pin output
 *    - Set CSN pin output
 *    - Set CE pin output     */
/* -------------------------------------------------------------------------- */
extern void nrf24_setupPins(void);

/* -------------------------------------------------------------------------- */
/* nrf24 CE pin control function
 *    - state:1 => Pin HIGH
 *    - state:0 => Pin LOW     */
/* -------------------------------------------------------------------------- */
extern void nrf24_ce_digitalWrite(uint8_t state);

/* -------------------------------------------------------------------------- */
/* nrf24 CE pin control function
 *    - state:1 => Pin HIGH
 *    - state:0 => Pin LOW     */
/* -------------------------------------------------------------------------- */
extern void nrf24_csn_digitalWrite(uint8_t state);

/* -------------------------------------------------------------------------- */
/* nrf24 SCK pin control function
 *    - state:1 => Pin HIGH
 *    - state:0 => Pin LOW     */
/* -------------------------------------------------------------------------- */
extern void nrf24_sck_digitalWrite(uint8_t state);

/* -------------------------------------------------------------------------- */
/* nrf24 MOSI pin control function
 *    - state:1 => Pin HIGH
 *    - state:0 => Pin LOW     */
/* -------------------------------------------------------------------------- */
extern void nrf24_mosi_digitalWrite(uint8_t state);

/* -------------------------------------------------------------------------- */
/* nrf24 MISO pin read function
/* - returns: Non-zero if the pin is high */
/* -------------------------------------------------------------------------- */
extern uint8_t nrf24_miso_digitalRead(void);

#endif
