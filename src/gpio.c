#include "gpio.h"

void gpio_init(PORT_t* port, uint8_t pin) {
  // configure pin as output
  port->DDR.byte = pin;  // input(=0) or output(=1)
  port->CR1.byte =
      pin;  // input: 0=float, 1=pull-up; output: 0=open-drain, 1=push-pull
  port->CR2.byte =
      pin;  // input: 0=no exint, 1=exint; output: 0=2MHz slope, 1=10MHz slope
}

void toggle_pin(PORT_t* port, uint8_t pin) { port->ODR.byte ^= pin; }
