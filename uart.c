/*
 * uart.c
 *
 * Created: 5/1/2019 11:35:19 PM
 *  Author: Frank
 */ 
#define SYSCLK 1000000
#include "uart.h"

void uart_init(unsigned baud){
	unsigned ubrr = SYSCLK/16/baud-1;
	
	// set baud
	UBRR0H = (u8)(ubrr>>8);
	UBRR0L = (u8)ubrr;
	
	// enable tx and rx
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
	
	// set format - 1 stop bit, no parity, 8 bit data
	UCSR0C = 0x3 << UCSZ00;
}

void uart_send(u8 data){
	// wait for empty transmit buffer
	while (!(UCSR0A & (1<<UDRE0)));
	
  // use CRLF for line termination
  if (data == '\n'){
    // send LF
    UDR0 = '\r';

    while (!(UCSR0A & (1<<UDRE0)));

    // send CR
    UDR0 = '\n';
  }
  else 
    // write data to send register
    UDR0 = data;

}

u8 uart_recv(void){
  u8 data;
	// poll rx bit 
	while (!(UCSR0A & (1<<RXC0)));
	
  u8 = UDR0;

  // echo input 
  uart_send(data);

	return u8;
}

void uart_getline(u8 *buf, unsigned len){
	unsigned count;
	
	// read up to len chars
	for (count=0; count<len; count++){
		// again, poll recieve flag
    while (!(UCSR0A & (1<<RXC0)));
    buf[count] = UDR0;

    // echo input
    uart_send(buf[count]);
    // check against both CR and LF just to be sure
    // return number of bytes recieved
    if (buf[count] == '\n' || buf[count] == '\r')
      return count;
	}

  return count;
}


void uart_prints(u8 *buf, unsigned len){
  unsigned count;

  // send len chars
  for (count=0; count<len; count++){
    // poll send buffer
    while (!(UCSR0A & (1<<UDRE0)));

    //write byte to uart
    UDR0 = buf[count];
  }
}
