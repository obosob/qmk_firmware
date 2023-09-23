#include QMK_KEYBOARD_H
#include "analog.h"

#define BASE 0
#define KM1 1


bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return false;
}

const uint16_t PROGMEM combo_test[] = {KC_S, KC_E, KC_R, KC_T, KC_BSLS, COMBO_END};

combo_t key_combos[] = {
    COMBO(combo_test, QK_BOOT),
};

char arrow_keys[4] = {KC_UP, KC_LEFT, KC_DOWN, KC_RIGHT}; // up, left, down, right
static int actuation = 256; // actuation point for arrows (0-511)
bool arrows[4];

void matrix_scan_user(void) {
    switch (biton32(layer_state)) {
        case 0:
            if (!arrows[0] && analogReadPin(B5) - 512 > actuation) {
                arrows[0] = true;
                register_code16(KC_UP);
            } else if (arrows[0] && analogReadPin(B5) - 512 < actuation) {
                arrows[0] = false;
                unregister_code16(KC_UP);
            }

            if (!arrows[0] && analogReadPin(B5) - 512 > -actuation) {
                arrows[0] = true;
                register_code16(KC_DOWN);
            } else if (arrows[0] && analogReadPin(B5) - 512 < -actuation) {
                arrows[0] = false;
                unregister_code16(KC_DOWN);
            }

            if (!arrows[0] && analogReadPin(B4) - 512 > actuation) {
                arrows[0] = true;
                register_code16(KC_LEFT);
            } else if (arrows[0] && analogReadPin(B4) - 512 < actuation) {
                arrows[0] = false;
                unregister_code16(KC_LEFT);
            }

            if (!arrows[0] && analogReadPin(B4) - 512 > -actuation) {
                arrows[0] = true;
                register_code16(KC_RIGHT);
            } else if (arrows[0] && analogReadPin(B4) - 512 < -actuation) {
                arrows[0] = false;
                unregister_code16(KC_RIGHT);
            }
            break;
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT(
            KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5,                   KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC,
            KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T,                   KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSLS,
            KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_G, KC_GRV,              KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
            KC_LCTL, KC_Z, KC_X, KC_C, KC_V, KC_B,              KC_DEL, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
            TG(KM1),             KC_LGUI, LT(KM1, KC_SPC), KC_ENT,  KC_SPC, KC_ENT, KC_RALT
            ),

    [KM1] = LAYOUT(
            KC_ESC,  KC_6, KC_7,    KC_8,    KC_9,     KC_0,                KC_MINS, KC_EQL, KC_8, KC_LBRC, KC_RBRC, KC_BSPC,
            KC_TAB,  KC_Q, KC_BSPC, KC_UP,   KC_ENT,   KC_T,                KC_7, KC_8, KC_9, KC_O, KC_P, KC_BSLS,
            KC_LSFT, KC_A, KC_LEFT, KC_DOWN, KC_RIGHT, KC_G,  KC_GRV,               KC_4, KC_5, KC_6, KC_L, KC_SCLN, KC_QUOT,
            KC_LCTL, KC_Z, KC_X,    KC_C,    KC_V,     KC_B,            LGUI(KC_SCLN), KC_1, KC_2, KC_3, KC_DOT, KC_SLSH, KC_RSFT,
            TG(BASE),                KC_LGUI, KC_SPC,  KC_ENT,          KC_0, KC_ENT, KC_RALT
            ),
};
