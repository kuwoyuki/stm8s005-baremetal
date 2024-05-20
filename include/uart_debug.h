#ifndef UART_DEBUG_H
#define UART_DEBUG_H

#include <stdarg.h>

static int uart_puts(char* s, int len, void* buf);
int printf(const char* format, ...);
int vprintf(const char* format, va_list args);
int snprintf(char* buffer, unsigned int buffer_len, const char* format, ...);

#endif  // UART_DEBUG_H
