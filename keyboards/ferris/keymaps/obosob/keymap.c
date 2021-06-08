/* Copyright 2020 Obosob <obosob@riseup.net>
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

enum layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
    _GAME,
    _GN,
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

#define HM_A LGUI_T(KC_A)
#define HM_S LALT_T(KC_S)
#define HM_D LCTL_T(KC_D)
#define HM_F LSFT_T(KC_F)

#define HM_SCLN RGUI_T(KC_SCLN)
#define HM_L LALT_T(KC_L)
#define HM_K RCTL_T(KC_K)
#define HM_J RSFT_T(KC_J)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
      
[_QWERTY] =  LAYOUT_split_3x5_2(
KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
HM_A,    HM_S,    HM_D,    HM_F,    KC_G,        KC_H,    HM_J,    HM_K,    HM_L,    HM_SCLN,
KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
                           LOWER,   KC_BSPC,     KC_SPC,  RAISE
),


[_RAISE] = LAYOUT_split_3x5_2(
XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_PSCR, 
KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,     KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_INS, 
XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, 
                           _______, KC_DEL,      _______, _______
),


[_LOWER] = LAYOUT_split_3x5_2(
KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_NLCK,     KC_PPLS, KC_P7,   KC_P8,   KC_P9,  KC_PAST, 
KC_F5,   KC_F6,   KC_F7,   KC_F8,   XXXXXXX,     KC_PDOT, KC_P4,   KC_P5,   KC_P6,  KC_P0, 
KC_F9,   KC_F10,  KC_F11,  KC_F12,  XXXXXXX,     KC_PMNS, KC_P1,   KC_P2,   KC_P3,  KC_PSLS, 
                           _______, _______,     KC_PENT, _______
),

[_ADJUST] = LAYOUT_split_3x5_2(
_______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, 
_______, _______, _______, _______, DF(_GAME),   _______, _______, _______, _______, _______, 
_______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, 
                           _______, _______,     _______, _______
),
[_GAME] = LAYOUT_split_3x5_2(
KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,        _______, _______, _______, _______, _______, 
KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,        _______, _______, _______, _______, _______, 
KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,        _______, _______, _______, _______, _______, 
                           MO(_GN), KC_SPC,      _______, _______
),
[_GN] = LAYOUT_split_3x5_2(
KC_1,    KC_2,    KC_3,    KC_4,    KC_5,     _______, _______, _______, _______, _______, 
_______, _______, _______, _______, DF(_QWERTY),   _______, _______, _______, _______, _______, 
_______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, 
                           _______, _______,     _______, _______
)
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

#ifdef COMBO_ENABLE
enum combos {
COMBO_1,
COMBO_2,
COMBO_3,
COMBO_4,
COMBO_5,
COMBO_6,
COMBO_7,
COMBO_8,
COMBO_9,
COMBO_0,
COMBO_LPRN,
COMBO_RPRN,
COMBO_LBRC,
COMBO_RBRC,
COMBO_LCBR,
COMBO_RCBR,
COMBO_LT,
COMBO_GT,
COMBO_TAB,
COMBO_NUBS,
COMBO_CAPS,
COMBO_ENT,
COMBO_MINS,
COMBO_EQL,
COMBO_QUOT,
COMBO_NUHS,
COMBO_ESC,
COMBO_GRV,
};

const uint16_t PROGMEM combo_1[] = {KC_Q, HM_A, COMBO_END};
const uint16_t PROGMEM combo_2[] = {KC_W, HM_S, COMBO_END};
const uint16_t PROGMEM combo_3[] = {KC_E, HM_D, COMBO_END};
const uint16_t PROGMEM combo_4[] = {KC_R, HM_F, COMBO_END};
const uint16_t PROGMEM combo_5[] = {KC_T, KC_G, COMBO_END};
const uint16_t PROGMEM combo_6[] = {KC_Y, KC_H, COMBO_END};
const uint16_t PROGMEM combo_7[] = {KC_U, HM_J, COMBO_END};
const uint16_t PROGMEM combo_8[] = {KC_I, HM_K, COMBO_END};
const uint16_t PROGMEM combo_9[] = {KC_O, HM_L, COMBO_END};
const uint16_t PROGMEM combo_0[] = {KC_P, HM_SCLN, COMBO_END};
const uint16_t PROGMEM combo_lprn[] = {HM_D, HM_F, COMBO_END};
const uint16_t PROGMEM combo_rprn[] = {HM_J, HM_K, COMBO_END};
const uint16_t PROGMEM combo_lcbr[] = {HM_A, HM_S, COMBO_END};
const uint16_t PROGMEM combo_rcbr[] = {HM_L, HM_SCLN, COMBO_END};
const uint16_t PROGMEM combo_lbrc[] = {HM_F, KC_G, COMBO_END};
const uint16_t PROGMEM combo_rbrc[] = {KC_H, HM_J, COMBO_END};
const uint16_t PROGMEM combo_lt[] = {HM_S, HM_D, COMBO_END};
const uint16_t PROGMEM combo_gt[] = {HM_K, HM_L, COMBO_END};
const uint16_t PROGMEM combo_tab[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM combo_nubs[] = {HM_A, KC_Z, COMBO_END};
const uint16_t PROGMEM combo_caps[] = {KC_Z, KC_X, KC_C, KC_V, COMBO_END};
const uint16_t PROGMEM combo_ent[] = {HM_A, HM_F, COMBO_END};
const uint16_t PROGMEM combo_mins[] = {KC_M, KC_COMM, COMBO_END};
const uint16_t PROGMEM combo_eql[] = {KC_COMM, KC_DOT, COMBO_END};
const uint16_t PROGMEM combo_quot[] = {HM_SCLN, KC_SLSH, COMBO_END};
const uint16_t PROGMEM combo_nuhs[] = {HM_L, KC_DOT, COMBO_END};
const uint16_t PROGMEM combo_esc[] = {HM_S, HM_F, COMBO_END};
const uint16_t PROGMEM combo_grv[] = {HM_S, KC_X, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    [COMBO_1] = COMBO(combo_1, KC_1),
    [COMBO_2] = COMBO(combo_2, KC_2),
    [COMBO_3] = COMBO(combo_3, KC_3),
    [COMBO_4] = COMBO(combo_4, KC_4),
    [COMBO_5] = COMBO(combo_5, KC_5),
    [COMBO_6] = COMBO(combo_6, KC_6),
    [COMBO_7] = COMBO(combo_7, KC_7),
    [COMBO_8] = COMBO(combo_8, KC_8),
    [COMBO_9] = COMBO(combo_9, KC_9),
    [COMBO_0] = COMBO(combo_0, KC_0),
    [COMBO_LPRN] = COMBO(combo_lprn, KC_LPRN),
    [COMBO_RPRN] = COMBO(combo_rprn, KC_RPRN),
    [COMBO_LBRC] = COMBO(combo_lbrc, KC_LBRC),
    [COMBO_RBRC] = COMBO(combo_rbrc, KC_RBRC),
    [COMBO_LCBR] = COMBO(combo_lcbr, KC_LCBR),
    [COMBO_RCBR] = COMBO(combo_rcbr, KC_RCBR),
    [COMBO_LT] = COMBO(combo_lt, KC_LT),
    [COMBO_GT] = COMBO(combo_gt, KC_GT),
    [COMBO_TAB] = COMBO(combo_tab, KC_TAB),
    [COMBO_NUBS] = COMBO(combo_nubs, KC_NUBS),
    [COMBO_CAPS] = COMBO(combo_caps, KC_CAPS),
    [COMBO_ENT] = COMBO(combo_ent, KC_ENT),
    [COMBO_MINS] = COMBO(combo_mins, KC_MINS),
    [COMBO_EQL] = COMBO(combo_eql, KC_EQL),
    [COMBO_QUOT] = COMBO(combo_quot, KC_QUOT),
    [COMBO_NUHS] = COMBO(combo_nuhs, KC_NUHS),
    [COMBO_ESC] = COMBO(combo_esc, KC_ESC),
    [COMBO_GRV] = COMBO(combo_grv, KC_GRV),
};
#endif
