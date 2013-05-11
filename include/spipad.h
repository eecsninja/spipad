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

#ifndef __SPIPAD_H__
#define __SPIPAD_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// These are arranged to match to the SNES gamepad's button data order.
// They're backwards compatible with the NES controller, which doesn't have the
// last four buttons.
typedef struct {
  // Low byte: present on both SNES and NES.
  union {
    struct {
      uint8_t B:1;          // "A" button on the NES.
      uint8_t Y:1;          // "B" button on the NES.
      uint8_t SELECT:1;
      uint8_t START:1;
      uint8_t UP:1;
      uint8_t DOWN:1;
      uint8_t LEFT:1;
      uint8_t RIGHT:1;
    };
    uint8_t low_byte;
  };
  // High byte: present on SNES only.
  union {
    struct {
      uint8_t A:1;
      uint8_t X:1;
      uint8_t L:1;
      uint8_t R:1;
    };
    uint8_t high_byte;
  };
} SpiPadButtons;

// Sets up SPIpad.
void spipad_init(void);

// Reads and returns current state of NES or SNES buttons.
SpiPadButtons spipad_read(void);

#ifdef __cplusplus
}  // extern "C"
#endif

#endif  // __SPIPAD_H__