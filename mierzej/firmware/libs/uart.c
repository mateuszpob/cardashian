#include "uart.h"

void USART_Init(unsigned int ubrr) {
    UBRRH = (unsigned char) (ubrr >> 8);
    UBRRL = (unsigned char) ubrr;
    UCSRB = (1 << RXCIE) | (1 << RXEN) | (1 << TXEN);
    UCSRC = (1 << URSEL) | (3 << UCSZ0); /* Set frame format: 8data, no parity, 1stop bit */
    // PORTD = 0x02; //pullup na TXC 
}

unsigned char USART_Receive(void) {
    while (!(UCSRA & (1 << RXC)));
    return UDR;
}

void USART_Transmit(unsigned char data) {
    /* Wait for empty transmit buffer */
    while (!(UCSRA & (1 << UDRE))); /* Put data into buffer, sends the data */
    UDR = data;
}

void USART_Sendstring(char str[]) {
    int i = 0;
    while (str[i]) {
        USART_Transmit(str[i]);
        i++;
    }
}

void USART_Flush(void) {

}