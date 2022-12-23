#ifndef UART
#define UART

#include <avr/io.h>

void USART_Init(unsigned int ubrr);

unsigned char USART_Receive(void);

void USART_Transmit(unsigned char data);

void USART_Sendstring(char str[]);

void USART_Flush(void);
#endif