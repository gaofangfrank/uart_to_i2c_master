/*
 * i2c.h
 *
 * Created: 5/2/2019 1:02:52 AM
 *  Author: Frank
 */ 


#ifndef I2C_H_
#define I2C_H_

#include <avr/iom328.h>

typedef unsigned char u8;

void i2c_init(void);

void i2c_start(u8 addr);
void i2c_write(u8 data);
void i2c_stop(void);


#endif /* I2C_H_ */
