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

#include "spipad.h"

// These are system-specific functions, implemented differently on every system.

// Initializes SPI interface with the settings necessary for SPIpad operation.
extern void spipad_spi_init(void);

// SPI transmit function.  Sends a byte over MOSI and returns the value that was
// returned through MISO.  Does not manipulate the SS pin.
extern uint8_t spipad_spi_tx(uint8_t value);

// This sets the SS pin of the SPI interface.  |pin_value| is the physical value
// of the SS pin, regardless of whether it is active high or low.
extern void spipad_spi_set_ss(uint8_t pin_value);

void spipad_init(void) {
  spipad_spi_init();
  spipad_spi_set_ss(1);
}

// The main gamepad read function.
SpiPadButtons spipad_read(void) {
  spipad_spi_set_ss(0);

  // Send two bytes to read two bytes back.  The sent value doesn't matter.
  SpiPadButtons pad_buttons;
  pad_buttons.low_byte = spipad_spi_tx(0);
  pad_buttons.high_byte = spipad_spi_tx(0);

  spipad_spi_set_ss(1);

  return pad_buttons;
}
