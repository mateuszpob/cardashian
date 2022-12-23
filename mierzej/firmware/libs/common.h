/* 
 * File:   common.h
 * Author: mp
 *
 * Created on 17 lipca 2019, 20:14
 */

#ifndef COMMON_H
#define COMMON_H

// LED
#define LED_G_ON        PORTC |= (1<<PC3)
#define LED_G_OFF       PORTC &= ~(1<<PC3)
#define LED_Y_ON        PORTC |= (1<<PC4)
#define LED_Y_OFF       PORTC &= ~(1<<PC4)
#define LED_R_ON        PORTC |= (1<<PC5)
#define LED_R_OFF       PORTC &= ~(1<<PC5)

#define BTN_PIN         PB0

#define CAN_ON          PORTD |= (1<<PD2)
#define CAN_OFF         PORTD &= ~(1<<PD2)

#define NRF_ON          PORTC |= (1<<PC2)
#define NRF_OFF         PORTC &= ~(1<<PC2)

#define HC_BYTE_ADDR 0x0F

// Memory 
#define DEV_ADDR_OFFSET 0
#define HC_STEPS 1
#define FIRST_PROXY_ADDR 2
#define FIRST_PROXY_HC_STEPS 3

#define NOP__           0x00
#define BRD_REQ         0x01
#define BRD_RES         0x02
#define TO_HC           0x03

#endif /* COMMON_H */

