/*
 * i2c.h
 *
 * Created: 5/2/2019 1:02:52 AM
 *  Author: Frank
 */ 


#ifndef I2C_H_
#define I2C_H_

#include <avr/io.h>
#include <string.h>
#include "defines.h"


// status codes in TWSR
#define S_START 0x08
#define S_RSTART 0x10 // repeated start
#define S_SLA_W_ACK 0x18 // addr+write
#define S_SLA_W_NACK 0x20
#define S_SLA_R_ACK 0x40 // addr+read
#define S_SLA_R_NACK 0x48
#define S_W_ACK 0x28 //data write
#define S_W_NACK 0x30
#define S_R_ACK 0x50 // data recieved
#define S_R_NACK 0x58
#define S_ARB_LOST 0x38 // applicable to multi master - probably not important?

typedef unsigned char u8;

void i2c_init(void);

// returns status codes
u8 i2c_start(void);
u8 i2c_write(u8 data);

// precondition: i2c is in write mode
u8 i2c_read(u8 *data, u8 ack);
void i2c_stop(void);

// returns string length
unsigned i2c_strerr(u8 status, u8 *strbuf);


#endif /* I2C_H_ */
