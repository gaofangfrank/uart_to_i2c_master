/*
 * uart2i2c.c
 *
 * Created: 5/1/2019 11:32:37 PM
 * Author : Frank
 */ 

#include <avr/iom328.h>
#include <util/delay.h>
#include "uart.h"
#include "i2c.h"


int main(void)
{
  unsigned n;
  u8 buf[16];

  i2c_init();
  uart_init();
  while (1) {
    n = uart_getline(buf, 16);
    // TODO
  }
}

