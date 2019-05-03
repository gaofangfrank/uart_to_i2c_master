/*
 * uart2i2c.c
 *
 * Created: 5/1/2019 11:32:37 PM
 * Author : Frank
 */ 

#include <avr/io.h>
#include <stdlib.h>
#include "uart.h"
#include "i2c.h"

#define WADDR 0x78
#define RADDR 0x79

int main(void)
{
  unsigned n;
  char buf[8];
  char returnbuf[64];
  u8 status;
  unsigned len;
  u8 data;
  char *cptr;

  i2c_init();
  uart_init(9600);
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
	
    // send stop condition
    else if (buf[0] == 'p'){
	    i2c_stop();
      uart_prints("Written Stop Command\n", 21);
	}
	
    // send data
    else if (buf[0] == 'w'){
      data = (u8)strtoul(buf+2, &cptr, 16);

      status = i2c_write(data);
      // print status
      len = i2c_strerr(status, returnbuf);
      uart_prints(returnbuf, len);
    }
	
    // read data
    else if (buf[0] == 'r'){
      if (buf[1] == 'a')
        status = i2c_read(&data, 1);
      else if (buf[1] == 'n')
        status = i2c_read(&data, 0);
	  else 
		  continue;

      uart_send(data);
      uart_send('\n');

      // print status
      len = i2c_strerr(status, returnbuf);
      uart_prints(returnbuf, len);
    }
  }
}

