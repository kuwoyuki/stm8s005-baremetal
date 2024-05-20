#ifndef GPIO_H
#define GPIO_H

#include "stm8s005c6.h"

void gpio_init(PORT_t* port, uint8_t pin);
void toggle_pin(PORT_t* port, uint8_t pin);

#endif  // GPIO_H
