/*
 * i2c.c
 *
 * Created: 5/2/2019 1:03:07 AM
 *  Author: Frank
 */ 

#include "i2c.h"

#define TWSTATUS (TWSR & 0xf8)

#define C_START ((1<<TWINT) | (1<<TWSTA) | (1<<TWEN))
#define C_DATA ((1<<TWINT) | (1<<TWEN))
#define C_DATA_ACK ((1<<TWINT) | (1<<TWEN) | (1<<TWEA))
#define C_STOP ((1<<TWINT) | (1<<TWSTO) | (1<<TWEN))

void i2c_init(void){
  // set TWBR and prescaler to as low as can be
  // since 1MHz / 16 < 100kHz
  // bitrate register
  TWBR = 0;
  // TWPS in status register
  TWSR = 0;
}

u8 i2c_start(void){
  // send start command 
  // wait until TWINT is set
  while (!(TWCR & (1<<TWINT)));

  // send command 
  TWCR = C_START;
  
  // wait for TWINT again
  while (!(TWCR & (1<<TWINT)));

  // return status
  return TWSTATUS;
}


u8 i2c_write(u8 data){
  // wait for twint
  while (!(TWCR & (1<<TWINT)));

  // write data
  TWDR = data;
  
  // send command and wait for TWINT
  TWCR = C_DATA;
  while (!(TWCR & (1<<TWINT)));
  
  // return status
  return TWSTATUS;
}

u8 i2c_read(u8 *data, u8 ack){
  while (!(TWCR & (1<<TWINT)));
  
  // send read command 
  if (ack)
    TWCR = C_DATA_ACK;
  else 
    TWCR = C_DATA;

  // wait for transaction to finish`
  while (!(TWCR & (1<<TWINT)));

  // write back data
  *data = TWDR;
  
  // return status
  return TWSTATUS;
}

void i2c_stop(void){
  while (!(TWCR & (1<<TWINT)));

  TWCR = C_STOP;
  
}

unsigned i2c_strerr(u8 status, u8 *strbuf){
  unsigned len;
  
  switch (status) {
    case S_START: 
      len = 21;
      strncpy(strbuf, "START condition sent\n", len);
      break;
      
    case S_RSTART: 
      len = 30;
      strncpy(strbuf, "Repeated START condition sent\n", len);
      break;
      
    case S_SLA_W_ACK: 
      len = 23;
      strncpy(strbuf, "Write to slave got ACK\n", len);
      break;

    case S_SLA_W_NACK: 
      len = 24;
      strncpy(strbuf, "Write to slave got NACK\n", len);
      break;
      
    case S_SLA_R_ACK: 
      len = 22;
      strncpy(strbuf, "Read to slave got ACK\n", len);
      break;

    case S_SLA_R_NACK: 
      len = 23;
      strncpy(strbuf, "Read to slave got NACK\n", len);
      break;

    case S_W_ACK: 
      len = 18;
      strncpy(strbuf, "Data sent got ACK\n", len);
      break;

    case S_W_NACK: 
      len = 19;
      strncpy(strbuf, "Data sent got NACK\n", len);
      break;
      
    case S_R_ACK: 
      len = 19;
      strncpy(strbuf, "Data read sent ACK\n", len);
      break;

    case S_R_NACK: 
      len = 20;
      strncpy(strbuf, "Data read sent NACK\n", len);
      break;

    case S_ARB_LOST: 
      len = 18;
      strncpy(strbuf, "Arbitration lost!\n", len);
      break;

    default: 
      len = 16;
      strncpy(strbuf, "Undefined Error\n", len);
  }

  return len;
}
