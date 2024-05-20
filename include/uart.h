#ifndef UART_H
#define UART_H

#include <stdint.h>

/**
 * Initialize UART1.
 * Mode: 8-N-1, flow-control: none.
 *
 * PD5 -> TX
 * PD6 -> RX
 * @param baudrate The baudrate to be used.
 * @return void
 */
void uart_init(uint32_t baudrate);
// inline uint8_t uart_available();
inline uint8_t uart_read();
void uart_write(uint8_t data);
// inline void uart_flush();

#endif /* UART_H */
