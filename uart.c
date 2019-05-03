/*
 * uart.c
 *
 * Created: 5/1/2019 11:35:19 PM
 *  Author: Frank
 */ 
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
  if (data == '\n' || data == '\r'){
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
	
  data = UDR0;

  // echo input 
  uart_send(data);

	return data;
}

unsigned uart_getline(u8 *buf, unsigned len){
	unsigned count;
	
	// read up to len chars
	for (count=0; count<len; count++){
    buf[count] = uart_recv();

    // check against both CR and LF just to be sure
    // return number of bytes received
    if (buf[count] == '\n' || buf[count] == '\r')
      return count + 1;

    // backspace
    else if (buf[count] == '\b' && count > 0){
      // blank out backspaced char
      uart_prints(" \b", 2);
      count--;
    }
	}

  return count;
}


void uart_prints(u8 *buf, unsigned len){
  unsigned count;

  // send len chars
  for (count=0; count<len; count++){
    uart_send(buf[count]);
  }
}
