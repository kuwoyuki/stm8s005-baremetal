#include "clock.h"

#include "config.h"

void clock_init(void) {
  // switch to 16MHz (default is 2MHz)
  sfr_CLK.CKDIVR.byte = 0x00;
}
