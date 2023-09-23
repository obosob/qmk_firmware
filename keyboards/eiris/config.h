#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x0000
#define DEVICE_VER      0x0001
#define MANUFACTURER    "foo"
#define PRODUCT         "bar"

#define SOFT_SERIAL_PIN D3

/* key matrix size */
#define MATRIX_ROWS 10
#define MATRIX_COLS 7

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
 */
#define MATRIX_ROW_PINS { F6, F7, B1, B3, B2}
#define MATRIX_COL_PINS { E6, D7, C6, D4, D0, D1, B6}
#define MATRIX_ROW_PINS_RIGHT { F7, B1, B3, B2, B6}
#define MATRIX_COL_PINS_RIGHT { B5, B4, E6, D7, C6, D4, NO_PIN}


#define DIODE_DIRECTION COL2ROW

#define ENCODERS_PAD_A { F5 }
#define ENCODERS_PAD_B { F4 }

// #define JOYSTICK_BUTTON_COUNT 0
// #define JOYSTICK_AXES_COUNT 2
