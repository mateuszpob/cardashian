#include "noaproto.h"

volatile uint8_t queue[256];
volatile uint8_t head = 255;
volatile uint8_t tail = 0;

uint8_t rx[128];
uint8_t tx[128];

uint8_t match(void)
{
	// Discard bytes until STX is found
	while(head != (uint8_t)(tail-1) && queue[head] != STX)
	head++;
	
	uint8_t offset = head;
	uint8_t available = (uint8_t)(tail-offset);
	
	// If there is not enough bytes for frame, try next time
	if(available < NP_BASE_LENGTH)
	return 0;
	
	// Check if entire frame is already received, if not - try next time
	uint8_t length = queue[(uint8_t)(offset + 1)];
	if(available < length)
	return 0;
	
	// If last byte is not ETX, discard until next STX
	if(queue[(uint8_t)(offset+length-1)] != ETX)
	{
		head++;
		return 0;
	}
	
	// If checksum not correct, discard until next STX
	if(checksum(queue,offset,length-1) != 0)
	{
		head++;
		return 0;
	}
	
	return length;
}

void discard(uint8_t length)
{
	uint8_t endpoint = (uint8_t)(head+length-1);
	while(head != (uint8_t)(tail-1) && head != endpoint)
	head++;
}

void read(uint8_t offset, uint8_t length)
{
	uint8_t index = 0;
	uint8_t i;
	for(i=offset; i!=(uint8_t)(offset+length); i++)
	rx[index++] = queue[i];
}

void send()
{
	uint8_t length = tx[NP_LENGTH_OFFSET];
	tx[0] = STX;
	tx[length-2] = checksum(tx,0,length-2);
	tx[length-1] = ETX;
	
	uint8_t i;
	for(i=0;i<length;i++)
	{
		while(!(UCSRA & (1<<UDRE)));
		UDR = tx[i];
	}
}

uint8_t checksum(volatile uint8_t *buffer, uint8_t offset, uint8_t length)
{
	uint8_t lrc = 0;
	uint8_t endpoint = (uint8_t)(offset+length);
	while(offset != endpoint)
		lrc ^= buffer[offset++];
	return lrc;
}

ISR(USART_RXC_vect)
{
	if(tail != head)
		queue[tail++] = UDR;
}