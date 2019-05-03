# UART to I2C Master

Using an 8-bit AVR [ATMega328](http://ww1.microchip.com/downloads/en/DeviceDoc/ATmega48A-PA-88A-PA-168A-PA-328-P-DS-DS40002061A.pdf) for the job. 

Implements a interpreter which takes five commands (as of now) to control a I2C master. 

### Commands

| Command      | Description                                                  |
|--------------|--------------------------------------------------------------|
| s            | Send the start bit                                           |
| w <hex data> | Send data - must come after start command eg. `w a8`         |
| ra           | Reads a byte and send ACK - must  come after start command   |
| rn           | Reads a byte and send NACK - must  come after start command  |
| p            | Sends stop bit                                               |

#### Why? 

TL;DR: Bought a small oled display - uses i2c interface, no documentation whatsoever. Trying to figure out the command structure. 


