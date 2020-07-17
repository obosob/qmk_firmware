/*
Copyright 2019 Danny Nguyen <danny@keeb.io>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xCB0E
#define PRODUCT_ID      0x1130
#define DEVICE_VER      0x0100
#define MANUFACTURER    David Barr
#define PRODUCT         Niop
#define DESCRIPTION     ASETNIOP board

/* key matrix size */
#define MATRIX_ROWS 1
#define MATRIX_COLS 10

/* key matrix pins */
#define DIRECT_PINS { \
    { E6,D7,C6,D4, B5,B6, F6,F7,B1,B2 } \
}

#define NO_ACTION_LAYER

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5
