/*
 * uart.h
 *
 * Created: 5/1/2019 11:35:31 PM
 *  Author: Frank
 */ 


#ifndef UART_H_
#define UART_H_

#include <avr/iom328.h>
#include "defines.h"

typedef unsigned char u8;


void uart_init(unsigned baud);

void uart_send(u8 data);

// gets a single char
u8 uart_recv(void);

// len sets the maximum buffer length
// returns number of chars read before a \n
unsigned uart_getline(u8 *buf, unsigned len);

// writes chars from buf to uart up to len bytes
void uart_prints(u8 *buf, unsigned len);

#endif /* UART_H_ */
