#include "uart.h"

#include "config.h"

void uart_init(uint32_t baudrate) {
  // reset UART
  // sfr_UART2.CR1.byte = 0x00;
  // sfr_UART2.CR2.byte = 0x00;
  // sfr_UART2.CR3.byte = 0x00;

  /* round to nearest integer */
  uint16_t div = (F_CPU + baudrate / 2) / baudrate;
  /* madness.. */
  // set baudrate (note: BRR2 must be written before BRR1!)
  sfr_UART2.BRR2.byte = (uint8_t)(((div & 0xF000) >> 8) | (div & 0x000F));
  sfr_UART2.BRR1.byte = (uint8_t)(div >> 4);

  /* enable transmitter and receiver */
  sfr_UART2.CR2.REN = 1;  // enable receiver
  sfr_UART2.CR2.TEN = 1;  // enable sender
  // sfr_UART.CR2.TIEN = 1;  // enable transmit interrupt
  // sfr_UART2.CR2.RIEN = 1;  // enable receive interrupt
}

/**
 * Check if there is data available in UART.
 * @return 1 if there is data available, 0 otherwise.
 */
inline uint8_t uart_available() { return sfr_UART2.SR.RXNE; }

/// read received byte from UART
/**
 * Read a byte from UART.
 * @return The byte read.
 */
inline uint8_t uart_read() { return sfr_UART2.DR.byte; }

/**
 * Write a byte to UART.
 * @param data The byte to be written.
 * @return void
 */
void uart_write(uint8_t data) {
  while (!(sfr_UART2.SR.TXE));
  sfr_UART2.DR.byte = data;
  while (!(sfr_UART2.SR.TC));
}

/**
 * Wait until UART Tx buffer is empty.
 * @return void
 */
inline void uart_flush() { while (!(sfr_UART2.SR.TC)); }
