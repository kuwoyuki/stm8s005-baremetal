#include "uart_debug.h"

#include "mini_printf.h"
#include "uart.h"

// Helper function to write a string to UART
static int uart_puts(char* s, int len, void* buf) {
  (void)buf;  // unused
  for (int i = 0; i < len; ++i) {
    uart_write((uint8_t)s[i]);
  }
  return len;
}

int printf(const char* format, ...) {
  va_list args;
  va_start(args, format);
  int result = mini_vpprintf(uart_puts, 0, format, args);
  va_end(args);
  return result;
}

int vprintf(const char* format, va_list args) {
  return mini_vpprintf(uart_puts, 0, format, args);
}

int snprintf(char* buffer, unsigned int buffer_len, const char* format, ...) {
  va_list args;
  va_start(args, format);
  int result = mini_vsnprintf(buffer, buffer_len, format, args);
  va_end(args);
  return result;
}
