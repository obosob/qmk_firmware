/* Copyright 2023 Colin Lam (Ploopy Corporation)
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2019 Sunjun Kim
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#ifndef PLOOPY_DRAGSCROLL_DIVISOR_H
#    define PLOOPY_DRAGSCROLL_DIVISOR_H 8.0
#endif
#ifndef PLOOPY_DRAGSCROLL_DIVISOR_V
#    define PLOOPY_DRAGSCROLL_DIVISOR_V 8.0
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
            MO(1),   KC_BTN4, KC_BTN5, DRAG_SCROLL,
            KC_BTN1,                   KC_BTN2
          ),
    [1] = LAYOUT(
            _______, XXXXXXX, XXXXXXX, DPI_CONFIG,
            XXXXXXX,                   XXXXXXX
          )
};

bool was_scrolled = false;
bool my_is_drag_scroll = false;

float my_scroll_accumulated_h = 0;
float my_scroll_accumulated_v = 0;

// SIZE x FREQ = TIME window
#ifndef SCROLL_HISTORY_SIZE
#  define SCROLL_HISTORY_SIZE 30
#endif
#ifndef SCROLL_HISTORY_FREQ
#  define SCROLL_HISTORY_FREQ 10
#endif

int8_t scroll_history_x[SCROLL_HISTORY_SIZE];
int8_t scroll_history_y[SCROLL_HISTORY_SIZE];
uint16_t scroll_history_t[SCROLL_HISTORY_SIZE];
uint8_t scroll_history_head = 0;
uint8_t scroll_history_tail = 0;

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    static uint16_t drag_scroll_timer;
    switch(keycode) {
        case DRAG_SCROLL:
            my_is_drag_scroll = record->event.pressed;
            if(record->event.pressed) {
                was_scrolled = false;
                my_scroll_accumulated_h = my_scroll_accumulated_v = 0;
                scroll_history_tail = scroll_history_head; // reset buffer
                drag_scroll_timer = scroll_history_t[scroll_history_head] = timer_read();
                scroll_history_x[scroll_history_head] = scroll_history_y[scroll_history_head] = 0;
            } else {
                if (!was_scrolled && timer_elapsed(drag_scroll_timer) < TAPPING_TERM) {
                    // if we didn't scroll, it's a middle click
                    tap_code(KC_BTN3);
                }
            }
            return false;
    }
    return true;
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (my_is_drag_scroll) {
        my_scroll_accumulated_h += (float)mouse_report.x / PLOOPY_DRAGSCROLL_DIVISOR_H;
        my_scroll_accumulated_v += (float)mouse_report.y / PLOOPY_DRAGSCROLL_DIVISOR_V;

        // if it's been more than the sampling frequency: advance the head of
        // the buffer, initialise that frame to zero, and take a timer reading
        if (timer_elapsed(scroll_history_t[scroll_history_head]) > SCROLL_HISTORY_FREQ)
        {
            scroll_history_head = (scroll_history_head + 1) % SCROLL_HISTORY_SIZE;

            // if head has met the tail, advance the tail by one
            if(scroll_history_head == scroll_history_tail) {
                scroll_history_tail = (scroll_history_tail + 1) % SCROLL_HISTORY_SIZE;
            }

            scroll_history_t[scroll_history_head] = timer_read();
            scroll_history_x[scroll_history_head] = 0;
            scroll_history_y[scroll_history_head] = 0;
        }

        // add the mouse report to the sample (note that this is signed, it
        // results in the total amount the cursor would have moved from the
        // start to end of the frame
        scroll_history_x[scroll_history_head] += mouse_report.x;
        scroll_history_y[scroll_history_head] += mouse_report.y;

        // iterate over the history buffer, calculate the velocity for each time
        // step (average velocity for the sample frequency)
        float vel_x = 0.0, vel_y = 0.0;
        uint8_t count = 0;
        int8_t i0 = scroll_history_tail;
        int8_t i1 = (scroll_history_tail + 1) % SCROLL_HISTORY_SIZE;

        while ( i1 != (scroll_history_head + 1) % SCROLL_HISTORY_SIZE ) {
            uint16_t t0 = scroll_history_t[i0];
            uint16_t t1 = scroll_history_t[i1];

            int8_t x = scroll_history_x[i1];
            int8_t y = scroll_history_y[i1];

            uint8_t t = timer_elapsed(t1) - timer_elapsed(t0);

            vel_x += (float)abs(x) / (float)t;
            vel_y += (float)abs(y) / (float)t;

            ++count;
            i0 = i1;
            i1 = (i1 + 1) % SCROLL_HISTORY_SIZE;
        }

        // take an average of the absolute x and y components of velocity over
        // the sample period
        vel_x = vel_x / (float)count;
        vel_y = vel_y / (float)count;


        // default to using vertical scroll
#ifdef PLOOPY_DRAGSCROLL_INVERT
        mouse_report.v = -(int8_t)my_scroll_accumulated_v;
#else
        mouse_report.v = (int8_t)my_scroll_accumulated_v;
#endif

        // if and only if the average horizontal velocity over all samples is
        // greater than the vertical component, scroll horizontally
        if (vel_x > vel_y) {
            mouse_report.v = 0;
            mouse_report.h = (int8_t)my_scroll_accumulated_h;
        }

        // Update accumulated scroll values by subtracting the integer parts
        my_scroll_accumulated_h -= (int8_t)my_scroll_accumulated_h;
        my_scroll_accumulated_v -= (int8_t)my_scroll_accumulated_v;

        if(mouse_report.h != 0 || mouse_report.v != 0) {
            was_scrolled = true;
        }

        // Clear the X and Y values of the mouse report
        // so that the cursor doesn't move
        mouse_report.x = 0;
        mouse_report.y = 0;
    }

    return mouse_report;
}
