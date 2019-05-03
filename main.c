/*
 * uart2i2c.c
 *
 * Created: 5/1/2019 11:32:37 PM
 * Author : Frank
 */ 

#include <avr/iom328.h>
#include <util/delay.h>
#include <stdlib.h>
#include "uart.h"
#include "i2c.h"

#define RADDR 0x78
#define WADDR 0x79

int main(void)
{
  unsigned n;
  u8 buf[8];
  u8 returnbuf[64];
  u8 status;
  unsigned len;
  u8 data;
  u8 *cptr;

  i2c_init();
  uart_init();
  while (1) {
    uart_prints("=>", 2);
    n = uart_getline(buf, 8);

    // start command
    if (buf[0] == 's'){
      status = i2c_start();
      // print status
      len = i2c_strerr(status, returnbuf);
      uart_prints(returnbuf, len);
    }
    // send data
    else if (buf[0] == 'd'){
      data = (char)strtoul(buf+2, cptr, 16);

      status = i2c_write(data);
      // print status
      len = i2c_strerror(status, returnbuf);
      uart_prints(returnbuf, len);
    }
    // send data
    else if (buf[0] == 'r'){
      if (buf[1] == 'a')
        status = i2c_read(&data, 1);
      else if (buf[1] == 'n')
        status = i2c_read(&data, 0);

      uart_send(data);
      uart_send('\n');

      // print status
      len = i2c_strerror(status, returnbuf);
      uart_prints(returnbuf, len);
    }
  }
}

