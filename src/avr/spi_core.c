// Copyright (C) 2013 Simon Que
//
// This file is part of SPIpad.
//
// SPIpad is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// SPIpad is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with SPIpad.  If not, see <http://www.gnu.org/licenses/>.

#include <avr/io.h>

// NOTE: These settings are for the Atmega128A and similar devices.  It may not
// work for all AVR devices.

void spipad_spi_init(void) {
  DDRB = (1 << DDRB0) | (1 << DDRB1);
  PORTB |= 1;
  SPCR = (1 << SPE) | (1 << MSTR) | (1 << CPOL) | (1 << CPHA) | (1 << DORD);
  SPSR = (1 << SPI2X);
}

uint8_t spipad_spi_tx(uint8_t value) {
  SPDR = value;
  while(!(SPSR & (1 << SPIF)));
  return SPDR;
}

// This sets the SS pin of the SPI interface.  |pin_value| is the physical value
// of the SS pin, regardless of whether it is active high or low.
void spipad_spi_set_ss(uint8_t pin_value) {
  if (pin_value)
    PORTB |= (1 << DDRB0);
  else
    PORTB &= ~(1 << DDRB0);
}
