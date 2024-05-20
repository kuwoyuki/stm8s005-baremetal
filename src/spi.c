#include "spi.h"

#include "config.h"

void SPI_init() {
  sfr_SPI.CR1.byte =
      (1 << sfr_SPI.CR1.MSTR) | (1 << sfr_SPI.CR1.SPE) | (1 << sfr_SPI.CR1.BR);
  sfr_SPI.CR2.byte = (1 << sfr_SPI.CR2.SSM) | (1 << sfr_SPI.CR2.SSI) |
                     (1 << sfr_SPI.CR2.BDM) | (1 << sfr_SPI.CR2.BDOE);
}

uint8_t SPI_read() {
  SPI_write(0xFF);
  while (!(sfr_SPI.SR.byte & (1 << sfr_SPI.SR.RXNE)));
  return sfr_SPI.DR.byte;
}

void SPI_write(uint8_t data) {
  sfr_SPI.DR.byte = data;
  while (!(sfr_SPI.SR.byte & (1 << sfr_SPI.SR.TXE)));
}