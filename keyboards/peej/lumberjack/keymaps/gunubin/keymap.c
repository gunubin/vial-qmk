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
#include "recent_keys.h"

const uint16_t PROGMEM one_shot_shift_combo[] = {KC_F, KC_J, COMBO_END};
combo_t key_combos[] = {
    COMBO(one_shot_shift_combo, OSM(MOD_LSFT)),
};

enum layers {
  _QWERTY = 0,
  _FUNCTION
};


#define A_SPC LALT_T(KC_SPC)
#define G_TAB LGUI_T(KC_TAB)

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
    _______, KC_LALT,G_TAB,   A_SPC, _______,  KC_SPC,  A_BSPC,_______, L1_BSPC,   OSM(MOD_LSFT),  _______,  _______
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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
 if (update_recent_keys(keycode, record)) {
//     // Expand "qem" to my email address.
//     if (recent[RECENT_SIZE - 3] == KC_Q &&
//         recent[RECENT_SIZE - 2] == KC_E &&
//         recent[RECENT_SIZE - 1] == KC_M) {
//       SEND_STRING(SS_TAP(X_BSPC) SS_TAP(X_BSPC) "myname@email.com");
//       return false;
//     }
    // double tap "|" to "\"
    if (recent[RECENT_SIZE - 2] == KC_PIPE &&
        recent[RECENT_SIZE - 1] == KC_PIPE) {
        tap_code(KC_BSPC);
        tap_code(KC_BSLS);
        return false;
    }
    // double tap "/" to "-"
    if (recent[RECENT_SIZE - 2] == KC_SLSH &&
        recent[RECENT_SIZE - 1] == KC_SLSH) {
        tap_code(KC_BSPC);
        tap_code(KC_MINS);
        return false;
    }
    // double tap "-" to "~"
    if (recent[RECENT_SIZE - 2] == KC_MINS &&
        recent[RECENT_SIZE - 1] == KC_MINS) {
        tap_code(KC_BSPC);
        tap_code16(LSFT(KC_GRV));
        return false;
    }
    // double tap ",," to ";"
    if (recent[RECENT_SIZE - 2] == KC_COMM &&
        recent[RECENT_SIZE - 1] == KC_COMM) {
        tap_code(KC_BSPC);
        tap_code(KC_SCLN);
        return false;
    }
    // double tap "." to ":"
    if (recent[RECENT_SIZE - 2] == KC_DOT &&
        recent[RECENT_SIZE - 1] == KC_DOT) {
        tap_code(KC_BSPC);
        tap_code16(LSFT(KC_SCLN));
        return false;
    }
    // double tap "'" to "`"
    if (recent[RECENT_SIZE - 2] == KC_QUOT &&
        recent[RECENT_SIZE - 1] == KC_QUOT) {
        tap_code(KC_BSPC);
        tap_code(KC_GRV);
        return false;
    }
    // double tap "+" to "-"
    if (recent[RECENT_SIZE - 2] == KC_PLUS &&
        recent[RECENT_SIZE - 1] == KC_PLUS) {
        tap_code(KC_BSPC);
        tap_code(KC_MINS);
        return false;
    }
    // double tap "(" to "[".
    if (recent[RECENT_SIZE - 2] == KC_LPRN &&
        recent[RECENT_SIZE - 1] == KC_LPRN) {
        tap_code(KC_BSPC);
        tap_code16(LSFT(KC_COMM));
        return false;
    }
    // double tap ")" to "]".
    if (recent[RECENT_SIZE - 2] == KC_RPRN &&
        recent[RECENT_SIZE - 1] == KC_RPRN) {
        tap_code(KC_BSPC);
        tap_code16(LSFT(KC_DOT));
        return false;
    }
    // double tap "{" to "[".
    if (recent[RECENT_SIZE - 2] == KC_LCBR &&
        recent[RECENT_SIZE - 1] == KC_LCBR) {
        tap_code(KC_BSPC);
        tap_code(KC_LBRC);
        return false;
    }
    // double tap "}" to "]".
    if (recent[RECENT_SIZE - 2] == KC_RCBR &&
        recent[RECENT_SIZE - 1] == KC_RCBR) {
        tap_code(KC_BSPC);
        tap_code(KC_RBRC);
        return false;
    }
  }


    return true;
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case S_Z:
        case C_A:
            return 170;
        case C_ENT:
            return 180;
        default:
            return 200;
    }
}

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case A_BSPC:
        case L1_BSPC:
            return 0;
        default:
            return QUICK_TAP_TERM;
    }
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case A_SPC:
        case G_TAB:
        case G_SPC:
        case LA_TAB:
        case A_BSPC:
        case L1_BSPC:
        case S_SLSH:
            return false;
        default:
           return PERMISSIVE_HOLD;
    }
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case A_SPC:
        case G_TAB:
        case G_SPC:
        case LA_TAB:
        case A_BSPC:
        case L1_BSPC:
        case S_SLSH:
            return true;
        default:
            return HOLD_ON_OTHER_KEY_PRESS;
    }
}

bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case A_SPC:
        case G_TAB:
        case G_SPC:
        case LA_TAB:
        case A_BSPC:
        case L1_BSPC:
        case S_SLSH:
            return false;
        default:
            return TAPPING_FORCE_HOLD;
    }
}

