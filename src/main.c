#include "clock.h"
#include "config.h"
#include "gpio.h"
#include "uart.h"
#include "uart_debug.h"

#define LED_PORT sfr_PORTA
#define LED_PIN PIN2

ISR_HANDLER(TIM1_UPD_ISR, _TIM1_OVR_UIF_VECTOR_) {
  // clear timer interrupt flag
  sfr_TIM1.SR1.UIF = 0;

}  // TIM1_UPD_ISR

// lmao
void print_uint32(uint32_t value) {
  uint16_t high = value >> 16;
  uint16_t low = value & 0xFFFF;
  printf("counter: %u%05u\n", high, low);  // Print high and low parts
}

void main(void) {
  // Initialize the clock
  clock_init();
  // Initialize GPIO for the LED
  gpio_init(&LED_PORT, LED_PIN);

  // Initialize UART @ 115200
  uart_init(115200);

  // main loop
  uint32_t counter = 0;

  DISABLE_INTERRUPTS();

  // TIM1 setup: generate interrupt every 1000ms
  sfr_TIM1.CR1.byte = 0x00;
  sfr_TIM1.CR1.DIR = 1;  // Just for fun, let's count down (TIM1 can do that)
  sfr_TIM1.PSCRH.byte =
      0x0E;  // Prescaler: divide clock with 16000 (0x3E7F + 1) (to 1ms)
  sfr_TIM1.PSCRL.byte = 0x7F;
  sfr_TIM1.ARRH.byte = 0x13;  // Auto-reload registers. Count to 1000 (0x03E8)
  sfr_TIM1.ARRL.byte = 0xE8;
  sfr_TIM1.IER.UIE = 1;  // Update interrupt (UIE)
  sfr_TIM1.CR1.CEN = 1;  // Start TIM1

  // enable interrupts
  ENABLE_INTERRUPTS();

  while (1) {
    WAIT_FOR_INTERRUPT();

    // toggle LED. Pass port struct as pointer
    toggle_pin(&LED_PORT, LED_PIN);
    print_uint32(counter++);
    // printf("counter: %d\n", counter++);
  }
}