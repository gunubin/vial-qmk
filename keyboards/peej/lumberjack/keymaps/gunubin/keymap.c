/* Copyright 2020 Paul James
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
  _QWERTY = 0,
  _FUNCTION
};

#define LA_TAB LALT_T(KC_TAB)
#define G_SPC LGUI_T(KC_SPC)
#define A_BSPC RALT_T(KC_BSPC)
#define L1_BSPC LT(1, KC_BSPC)

#define C_A LCTL_T(KC_A)
#define C_ENT LCTL_T(KC_ENT)

#define S_Z LSFT_T(KC_Z)
#define S_SLSH LSFT_T(KC_SLSH)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty レイヤー
 * ,-----------------------------------------. ,-----------------------------------------.
 * |  1   |  2   |  3   |  4   |  5   |      | |      |  6   |  7   |  8   |  9   |  0   |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * |  Q   |  W   |  E   |  R   |  T   |      | |      |  Y   |  U   |  I   |  O   |  P   |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * |  A   |  S   |  D   |  F   |  G   |      | |      |  H   |  J   |  K   |  L   | ENT  |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * |  Z   |  X   |  C   |  V   |  B   |      | |      |  N   |  M   |  ,   |  .   |  /   |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * |      |      | Alt  | Cmd  |      | Tab  | | Bksp | Alt  | Entr | Fn   |      |      |
 * `-----------------------------------------' `-----------------------------------------'
 */
[_QWERTY] = LAYOUT_ortho_5x12(
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5, KC_LCTL, _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T, _______, _______, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
    C_A,     KC_S,    KC_D,    KC_F,    KC_G, _______, _______, KC_H,    KC_J,    KC_K,    KC_L,    C_ENT,
    S_Z,     KC_X,    KC_C,    KC_V,    KC_B, _______, _______, KC_N,    KC_M, KC_COMM,   KC_DOT,   S_SLSH,
    _______, _______,LA_TAB, G_SPC, _______,  KC_TAB,  A_BSPC,_______, L1_BSPC,   MO(1),  _______,  _______
),

/* Function レイヤー
 * ,-----------------------------------------. ,-----------------------------------------.
 * |  !   |  @   |  #   |  $   |  %   |      | |      |  ^   |  &   |  *   |  (   |  )   |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * |  1   |  2   |  3   |  4   |  5   |      | |      |  6   |  7   |  8   |  9   |  0   |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * |  +   |  (   |  )   |  =   |  :   |      | |      | Bksp |  +   |  -   |  :   |  ;   |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * |  \   |  {   |  }   |  '   |  "   |      | |      |  |   |  _   |  [   |  ]   |  -   |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * |      |      | Bksp | Space|      |      | |      |      | Space|      |      |      |
 * `-----------------------------------------' `-----------------------------------------'
 */
[_FUNCTION] = LAYOUT_ortho_5x12(
    KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, _______, _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
    KC_1,     KC_2,      KC_3,   KC_4,     KC_5, _______, _______, KC_6,       KC_7,    KC_8,    KC_9,    KC_0,
    KC_PLUS, KC_LPRN, KC_RPRN, KC_EQL,  KC_COLN, _______, _______, KC_BSPC, KC_PLUS, KC_MINS, KC_COLN, KC_SCLN,
    KC_BSLS, KC_LCBR, KC_RCBR, KC_QUOT, KC_DQT,  _______, _______, KC_PIPE, KC_UNDS, KC_LBRC, KC_RBRC, KC_MINS,
    _______, _______, KC_BSPC, KC_SPC,  _______, _______, _______, _______,  KC_SPC, _______, _______, _______
)

};

// Ctrl+enter -> Ctrl+;
// for IME
// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//     switch (keycode) {
//     case C_ENT:
//         if (record->event.pressed) {
//             if (get_mods() & MOD_BIT(KC_LCTL)) {
//                 register_code(KC_SCLN);
//                 return false;
//             }
//         } else {
//             unregister_code(KC_SCLN);
//         }
//         return true;
//     }
//     return true;
// };

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case C_ENT:
        case S_Z:
        case C_A:
            return 180;
        default:
            return 200;
    }
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case G_SPC:
        case A_BSPC:
        case L1_BSPC:
        case LA_TAB:
        case S_SLSH:
            return false;
        default:
            return true;
    }
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case G_SPC:
        case A_BSPC:
        case L1_BSPC:
        case LA_TAB:
        case S_SLSH:
            return true;
        default:
            return false;
    }
}

bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case G_SPC:
        case A_BSPC:
        case L1_BSPC:
        case LA_TAB:
        case S_SLSH:
            return false;
        default:
            return true;
    }
}

