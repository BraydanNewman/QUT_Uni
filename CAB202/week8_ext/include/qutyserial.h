#include <stdint.h>

// SERIAL
//
// Uses 
//   Pins: PB2, PB3
//   Peripherals: USART0
void serial_init();                             // Initialise UART as stdin/stdout
uint8_t serial_bytes_available(void);           // Returns number of bytes in receive buffer
