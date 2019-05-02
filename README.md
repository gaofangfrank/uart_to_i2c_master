# UART to I2C Master

Using an 8-bit AVR ATMega328 for the job. 

Implements a interpreter which takes four commands (as of now) to control a I2C master. 

### Commands

| Command      | Description                                                  |
|--------------|--------------------------------------------------------------|
| s <hex addr> | Send the start bit along with the device address e.g. `s a7` |
| d <hex data> | Send data - must come  after start command                   |
| r            | Reads a byte - must  come after start command                |
| p            | Sends stop bit                                               |

#### Why? 

TL;DR: Bought a small oled display - uses i2c interface, no documentation whatsoever. Trying to figure out the command structure. 
