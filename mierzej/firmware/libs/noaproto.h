#ifndef NOAPROTO_H_
#define NOAPROTO_H_

#include <avr/io.h>
#include <avr/interrupt.h>

#define STX								0x02
#define ETX								0x03

#define NP_LENGTH_OFFSET				0x01
#define NP_TARGET_OFFSET				0x02
#define NP_PAYLOAD_OFFSET				0x06
#define NP_DATA_OFFSET					0x07
#define NP_OPCODE_BITMASK				0x3F
#define NP_RESPONSE_BITMASK				0x80
#define NP_ERROR_BITMASK				0x40
#define NP_BASE_LENGTH					0x09

#define NP_TXDATA_UINT8(offset)			*(tx+NP_DATA_OFFSET+offset)
#define NP_RXDATA_UINT8(offset)			*(rx+NP_DATA_OFFSET+offset)
#define NP_TXDATA_UINT16(offset)		*((uint16_t*)(tx+NP_DATA_OFFSET+offset))
#define NP_RXDATA_UINT16(offset)		*((uint16_t*)(rx+NP_DATA_OFFSET+offset))
#define NP_TXDATA_UINT32(offset)		*((uint32_t*)(tx+NP_DATA_OFFSET+offset))
#define NP_RXDATA_UINT32(offset)		*((uint32_t*)(rx+NP_DATA_OFFSET+offset))

#define NP_TX_TARGET					*((uint32_t*)(tx+NP_TARGET_OFFSET))
#define NP_TX_OPCODE					*(tx+NP_PAYLOAD_OFFSET)
#define NP_TX_LENGTH					*(tx+NP_LENGTH_OFFSET)
#define NP_RX_TARGET					*((uint32_t*)(rx+NP_TARGET_OFFSET))
#define NP_RX_OPCODE					*(rx+NP_PAYLOAD_OFFSET)
#define NP_RX_LENGTH					*(rx+NP_LENGTH_OFFSET)


uint8_t match();
void discard(uint8_t length);
void read(uint8_t offset, uint8_t length);
void send();
uint8_t checksum(volatile uint8_t *buffer, uint8_t offset, uint8_t length);

#endif /* NOAPROTO_H_ */