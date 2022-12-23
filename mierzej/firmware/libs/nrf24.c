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
#include <avr/io.h>
#include "nrf24.h"

void nrf24_init() {
    CE_lo;
    CSN_hi;
}

/* configure the module */
void nrf24_config(uint8_t channel) {

    // Set RF channel
    nrf24_configRegister(RF_CH, channel);

    // Set length of incoming payload 
    nrf24_configRegister(RX_PW_P0, 0x00); // Auto-ACK pipe ...
    nrf24_configRegister(RX_PW_P1, 0x01); // Data payload pipe
    nrf24_configRegister(RX_PW_P2, 0x01); // Pipe not used 
    nrf24_configRegister(RX_PW_P3, 0x00); // Pipe not used 
    nrf24_configRegister(RX_PW_P4, 0x00); // Pipe not used 
    nrf24_configRegister(RX_PW_P5, 0x00); // Pipe not used 

    // 256 kbps, TX gain: 0dbm
    nrf24_configRegister(RF_SETUP, (1 << RF_DR_LOW) | ((0x03) << RF_PWR));

    // CRC enable, 1 byte CRC length
    nrf24_configRegister(CONFIG, nrf24_CONFIG);

    // Auto Acknowledgment
    nrf24_configRegister(EN_AA, (1 << ENAA_P0) | (1 << ENAA_P1) | (1 << ENAA_P2) | (0 << ENAA_P3) | (0 << ENAA_P4) | (0 << ENAA_P5));

    // Enable RX addresses
    nrf24_configRegister(EN_RXADDR, (1 << ERX_P0) | (1 << ERX_P1) | (1 << ERX_P2) | (0 << ERX_P3) | (0 << ERX_P4) | (0 << ERX_P5));

    // Auto retransmit delay: 1000 us and Up to 15 retransmit trials
    nrf24_configRegister(SETUP_RETR, (0x04 << ARD) | (0xFF << ARC));

    // Dynamic length configurations: Dynamic length on 0 and 1 pipe
    nrf24_configRegister(DYNPD, (1 << DPL_P0) | (1 << DPL_P1) | (1 << DPL_P2) | (0 << DPL_P3) | (0 << DPL_P4) | (0 << DPL_P5));

    nrf24_configRegister(FEATURE, (1 << EN_DPL));

    // Start listening
    nrf24_powerUpRx();
}

/* Set the RX address */
void nrf24_rx_address(uint8_t * adr, uint8_t rx_addr_2) {
    USART_Sendstring("RX_ADDR_1: ");
    print_frame(adr, 5);
    USART_Sendstring("RX_ADDR_2: ");
    uint8_t rx2[] = {rx_addr_2};
    print_frame(rx2, 1);

    CE_lo;
    nrf24_writeRegister(RX_ADDR_P1, adr, nrf24_ADDR_LEN);
    nrf24_configRegister(RX_ADDR_P2, rx_addr_2);
    CE_hi;
}

/* Set the TX address */
void nrf24_tx_address(uint8_t* adr) {
    USART_Sendstring("SET_TX_ADDR: ");
    print_frame(adr, 5);
    /* RX_ADDR_P0 must be set to the sending addr for auto ack to work. */
    nrf24_writeRegister(RX_ADDR_P0, adr, nrf24_ADDR_LEN);
    nrf24_writeRegister(TX_ADDR, adr, nrf24_ADDR_LEN);

    _delay_ms(1);

    // takie cos tu trzeba dać  i bedzie lux
    uint8_t nop[] = {NOP__, 0xff, 0xff};
    nrf24_send(nop, 3);

    _delay_ms(50);
}

/* Checks if data is available for reading */

/* Returns 1 if data is ready ... */
uint8_t nrf24_dataReady() {
    // See note in getData() function - just checking RX_DR isn't good enough
    uint8_t status = nrf24_getStatus();

    // We can short circuit on RX_DR, but if it's not set, we still need
    // to check the FIFO for any pending packets
    if (status & (1 << RX_DR)) {
        CE_lo;
        nrf24_configRegister(STATUS, (1 << RX_DR));
        CE_hi;
        return 1;
    }

    return !nrf24_rxFifoEmpty();
    ;
}

/* Checks if receive FIFO is empty or not */
uint8_t nrf24_rxFifoEmpty() {
    uint8_t fifoStatus;

    nrf24_readRegister(FIFO_STATUS, &fifoStatus, 1);

    return (fifoStatus & (1 << RX_EMPTY));
}

/* Returns the length of data waiting in the RX fifo */
uint8_t nrf24_payloadLength() {
    uint8_t status;
    CSN_lo;
    spi_single(R_RX_PL_WID);
    status = spi_single(0x00);
    CSN_hi;
    return status;
}

/* Reads payload bytes into data array */
uint8_t nrf24_getData(uint8_t* data) {
    /* Get payload length */
    uint8_t len;
    CSN_lo;
    spi_single(R_RX_PL_WID);
    len = spi_single(0x00);
    CSN_hi;

    /* Pull down chip select */
    CSN_lo;

    /* Send cmd to read rx payload */
    spi_single(R_RX_PAYLOAD);

    /* Read payload */
    spi_multiple(data, data, len);

    /* Pull up chip select */
    CSN_hi;

    /* Reset status register */
    nrf24_configRegister(STATUS, (1 << RX_DR));

    return len;
}

/* Returns the number of retransmissions occured for the last message */
uint8_t nrf24_retransmissionCount() {
    uint8_t rv;
    nrf24_readRegister(OBSERVE_TX, &rv, 1);
    rv = rv & 0x0F;
    return rv;
}
// Sends a data package to the default address. Be sure to send the correct
// amount of bytes as configured as payload on the receiver.

void nrf24_send(uint8_t* value, uint8_t len) {

    // print_frame(value, len);

    /* Go to Standby-I first */
    CE_lo;

    /* Set to transmitter mode , Power up if needed */
    nrf24_powerUpTx();

    /* Do we really need to flush TX fifo each time ? */
#if 1
    /* Pull down chip select */
    CSN_lo;

    /* Write cmd to flush transmit FIFO */
    spi_single(FLUSH_TX);

    /* Pull up chip select */
    CSN_hi;
#endif 

    /* Pull down chip select */
    CSN_lo;

    /* Write cmd to write payload */
    spi_single(W_TX_PAYLOAD);

    /* Write payload */
    spi_write(value, len);

    /* Pull up chip select */
    CSN_hi;

    /* Start the transmission */
    CE_hi;
    _delay_ms(1);
    CE_lo;
}

uint8_t nrf24_isSending() {
    uint8_t status = nrf24_getStatus();

    /* if sending successful (TX_DS) or max retries exceded (MAX_RT). */
    if ((status & ((1 << TX_DS) | (1 << MAX_RT)))) {

        uint8_t retr_count = nrf24_retransmissionCount();
        if (nrf24_lastMessageStatus() == NRF24_TRANSMISSON_OK && retr_count < 15) {
            // Success
            return 1;
        } else {
            // Message lost
            return 2;
        }
    }
    // sending
    return 0;
}

uint8_t nrf24_getStatus() {
    CSN_lo;
    uint8_t rv = spi_single(NOP);
    CSN_hi;
    return rv;
}

uint8_t nrf24_lastMessageStatus() {
    uint8_t rv = nrf24_getStatus();

    /* Transmission went OK */
    if ((rv & ((1 << TX_DS)))) {
        return NRF24_TRANSMISSON_OK;
    }/* Maximum retransmission count is reached */
        /* Last message probably went missing ... */
    else if ((rv & ((1 << MAX_RT)))) {
        return NRF24_MESSAGE_LOST;
    }/* Probably still sending ... */
    else {
        return 0xFF;
    }
}

void nrf24_powerUpRx() {
    CSN_lo;
    spi_single(FLUSH_RX);
    CSN_hi;

    nrf24_configRegister(STATUS, (1 << RX_DR) | (1 << TX_DS) | (1 << MAX_RT));

    CE_lo;
    nrf24_configRegister(CONFIG, nrf24_CONFIG | ((1 << PWR_UP) | (1 << PRIM_RX)));
    CE_hi;
}

void nrf24_powerUpTx() {
    nrf24_configRegister(STATUS, (1 << RX_DR) | (1 << TX_DS) | (1 << MAX_RT));

    nrf24_configRegister(CONFIG, nrf24_CONFIG | ((1 << PWR_UP) | (0 << PRIM_RX)));
}

void nrf24_powerDown() {
    CE_lo;
    nrf24_configRegister(CONFIG, nrf24_CONFIG);
}

/* Clocks only one byte into the given nrf24 register */
void nrf24_configRegister(uint8_t reg, uint8_t value) {
    CSN_lo;
    spi_single(W_REGISTER | (REGISTER_MASK & reg));
    spi_single(value);
    CSN_hi;
}

/* Read single register from nrf24 */
void nrf24_readRegister(uint8_t reg, uint8_t* value, uint8_t len) {
    CSN_lo;
    spi_single(R_REGISTER | (REGISTER_MASK & reg));
    spi_multiple(value, value, len);
    CSN_hi;
}

/* Write to a single register of nrf24 */
void nrf24_writeRegister(uint8_t reg, uint8_t* value, uint8_t len) {
    CSN_lo;
    spi_single(W_REGISTER | (REGISTER_MASK & reg));
    spi_write(value, len);
    CSN_hi;
}
