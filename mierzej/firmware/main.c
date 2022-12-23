
#define F_CPU 16000000 
#define UART_BAUD 9600				/* serial transmission speed */ 
#define UART_CONST F_CPU/16/UART_BAUD-1 

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h> 
#include <avr/pgmspace.h> 
#include <avr/interrupt.h> 

#include "libs/uart.h" 
#include "libs/noaproto.h" 

#define  PORT_ON(port,pin) port |= (1<<pin)
#define  PORT_OFF(port,pin)  port &=  ~(1<<pin)

// device constants
#define VREF 5
#define VREFmV 5000
#define R1 122
#define R2 22
#define RC 1000
#define PORT_COUNT 5

// opcodes
#define GET_VERSION					0x00
#define GET_STATE					0x01
#define READ_VOLTAGE				0x02
#define READ_RESISTANCE				0x03
#define READ_VALUE					0x04


#define VERSION_MAJOR	0
#define VERSION_MINOR	1

extern volatile uint8_t head;
extern volatile uint8_t tail;
extern uint8_t rx[128];
extern uint8_t tx[128];
uint32_t id = 0x00000009;
uint8_t no = 0;



	uint32_t temp_1 = 10;
	uint32_t temp_2 = 30;
	
void send_frame(uint8_t frame[], uint8_t length)
{
	uint8_t i = 0;
	for (; i < length; i++)
		USART_Transmit(frame[i]);
	USART_Flush();
}

uint32_t calculate_resistance(uint32_t adc_voltage) {
 	return RC * adc_voltage / (VREFmV - adc_voltage);
}

int  main(void) {

	USART_Sendstring("MIERZEJ\n\n");

	// USART_Init(UART_CONST); 
	USART_Init(103);


	// id = eeprom_read_dword(EE_ID_OFFSET);
	// eeprom_read_block(open_times, EE_OPEN_TIMES_OFFSET, 3);

	uint32_t adc_values[PORT_COUNT];	

	ADCSRA  = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS0);

	uint8_t port;



	sei();
	while(1) {	


		// Resistance channels 2-4 (avr ports 2-4)
		for(port = PORT_COUNT; port > 1; port--) {
			ADMUX = port;
			ADCSRA  |= (1<<ADSC);	// Start conversion
			while (ADCSRA &  (1<<ADSC));   // wait until conversion  completes; ADSC=0 means Complete

			adc_values[port] = ADCW;
			adc_values[port] = adc_values[port] * VREF * 1000 / 1023;
		}

		// Voltage meter channel 1 (avr port 5)
		ADMUX = 5;
		ADCSRA  |= (1<<ADSC);	// Start conversion
		while (ADCSRA &  (1<<ADSC));   // wait until conversion  completes; ADSC=0 means Complete

		adc_values[5] = ADCW;
		adc_values[5] = adc_values[5] * VREF * 1000 / 1023 * R1 / R2;



		// Serial Communication
		uint8_t frame_length = match();
		if(frame_length > 0)
		{	
			read(head,frame_length);
			uint8_t opcode = NP_RX_OPCODE;
			uint32_t mac = NP_RX_TARGET;
			// USART_Transmit(mac >> 24);
			
			{

				
			
				switch(opcode)
				{
					case GET_VERSION:
					{
						NP_TXDATA_UINT8(0) = VERSION_MAJOR;
						NP_TXDATA_UINT8(1) = VERSION_MINOR;
						NP_TX_OPCODE = opcode | NP_RESPONSE_BITMASK;
						NP_TX_LENGTH = NP_BASE_LENGTH + 2;
						break;
					}
					case READ_VOLTAGE:
					{
						NP_TXDATA_UINT32(0) = adc_values[5];
						NP_TXDATA_UINT32(4) = adc_values[4];
						NP_TXDATA_UINT32(8) = adc_values[3];
						NP_TXDATA_UINT32(12) = adc_values[2];
						NP_TXDATA_UINT32(16) = adc_values[1];
						NP_TX_OPCODE = opcode | NP_RESPONSE_BITMASK;
						NP_TX_LENGTH = NP_BASE_LENGTH + 40;
						break;
					}
					case READ_RESISTANCE:
					{
						NP_TXDATA_UINT32(0) = calculate_resistance(adc_values[5]);
						NP_TXDATA_UINT32(4) = calculate_resistance(adc_values[4]);
						NP_TXDATA_UINT32(8) = calculate_resistance(adc_values[3]);
						NP_TXDATA_UINT32(12) = calculate_resistance(adc_values[2]);
						NP_TXDATA_UINT32(16) = calculate_resistance(adc_values[1]);
						NP_TX_OPCODE = opcode | NP_RESPONSE_BITMASK;
						NP_TX_LENGTH = NP_BASE_LENGTH + 40;
						break;
					}
					case READ_VALUE:
					{
						NP_TXDATA_UINT32(0) = 13000; // calculate_resistance(adc_values[5]);
						NP_TXDATA_UINT32(4) = temp_1; // calculate_resistance(adc_values[4]);
						NP_TXDATA_UINT32(8) = temp_2; // calculate_resistance(adc_values[3]);
						NP_TXDATA_UINT32(12) = 23; // calculate_resistance(adc_values[2]);
						NP_TXDATA_UINT32(16) = 140; // calculate_resistance(adc_values[1]);
						NP_TX_OPCODE = opcode | NP_RESPONSE_BITMASK;
						NP_TX_LENGTH = NP_BASE_LENGTH + 40;
						temp_1++;
						temp_2++;
						break;
					}
					default:
						NP_TX_OPCODE = opcode | NP_RESPONSE_BITMASK | NP_ERROR_BITMASK;
						NP_TX_LENGTH = NP_BASE_LENGTH + 0;
				
				}
			
				NP_TX_TARGET = id;
				send();
				
			}
			discard(frame_length);
		}
	}
}










					
  	// while (1) {

	// 	// Resistance channels 2-4 (avr ports 2-4)
	// 	for(port = PORT_COUNT; port > 1; port--) {
	// 		ADMUX = port;
	// 		ADCSRA  |= (1<<ADSC);	// Start conversion
	// 		while (ADCSRA &  (1<<ADSC));   // wait until conversion  completes; ADSC=0 means Complete

	// 		adc_values[port] = ADCW;
	// 		adc_values[port] = adc_values[port] * VREF * 1000 / 1023;
	// 	}

	// 	// Voltage meter channel 1 (avr port 5)
	// 	ADMUX = 5;
	// 	ADCSRA  |= (1<<ADSC);	// Start conversion
	// 	while (ADCSRA &  (1<<ADSC));   // wait until conversion  completes; ADSC=0 means Complete

	// 	adc_values[5] = ADCW;
	// 	adc_values[5] = adc_values[5] * VREF * 1000 / 1023 * R1 / R2;



		


	// 	USART_Sendstring("Mierzej: ");
	// 	char string_result[32];
	// 	sprintf(string_result, "%lu mV, %lu mV, %lu mV, %lu mV, ", adc_values[5], adc_values[4], adc_values[3], adc_values[2]);
	// 	USART_Sendstring(string_result);
	// 	USART_Sendstring("\n\r");

	// 	_delay_ms(1000); 

  	// }
//  } 



// /**
// * Button na enkoderze podpiety do INT0 (PD2)
// * Button na płytce podpięty do PB0
// * Enkoder podpięty do PD5 i PD3
// */

// uint8_t read_gray_code_from_encoder(void ) 
// { 
//  uint8_t val=0; 

//   if(!bit_is_clear(PIND, PD5)) 
// 	val |= (1<<1); 

//   if(!bit_is_clear(PIND, PD3)) 
// 	val |= (1<<0); 

//   return val; 
// } 

// ISR(INT0_vect ) 
// {
// 	_delay_ms(10); 
// 	if(bit_is_clear(PIND, PD2)) {
// 		USART_Transmit(PUSH); 
// 	} else {
// 		USART_Transmit(POP); 
// 	}
	
// }

// int main(void) 
// { 
//   /* init uart */ 
//   USART_Init(UART_CONST);
//  uint8_t val=0, val_tmp =0; 


//   /* set PD5 and PD3 as input */ 
//   DDRD &=~ (1 << PD5);				/* PD2, PD5 and PD3 as input */ 
//   DDRD &=~ (1 << PD3);        
//   DDRD &=~ (1 << PD2);        
//   PORTD |= (1 << PD2)|(1 << PD3)|(1 << PD5);   /* PD5 and PD3 pull-up enabled   */        
  
//   DDRB &=~ (1 << PB0);
//   PORTB |= (1 << PB0);

// 	GICR |= (1<<INT0); // int
// 	MCUCR |= (1<<ISC00); // int

// 	sei(); 
//   /* ready start value */ 
//   val = read_gray_code_from_encoder(); 

//    while(1) 
//    { 

// 	   USART_Sendstring("Ole!\n");

// 	   _delay_ms(1000); 
//    } 

//   return 0; 
// }
