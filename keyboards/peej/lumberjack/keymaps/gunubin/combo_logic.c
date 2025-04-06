// combo_logic.c
#include "combo_logic.h"

static const combo_entry_t *combo_table = NULL;
static size_t combo_count = 0;

static uint16_t pending_key = KC_NO;
static uint16_t deadline = 0;

void init_combos(const combo_entry_t *entries, size_t count) {
    combo_table = entries;
    combo_count = count;
}

bool process_combo_keys(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) return true;

//     if (((get_mods() | get_oneshot_mods()) & ~MOD_MASK_SHIFT) != 0) {
    if ((get_mods() | get_oneshot_mods()) != 0) {

        pending_key = KC_NO;
        return true;
    }

    switch (keycode) {
        case QK_MOD_TAP ... QK_MOD_TAP_MAX:
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
            if (record->tap.count == 0) return true;
            keycode &= 0xFF;
            break;
    }

    switch (keycode) {
        case KC_A ... KC_SLASH:
        case KC_LPRN: case KC_RPRN:
        case KC_LCBR: case KC_RCBR:
        case KC_PLUS: case KC_PIPE:
            break;

        case KC_LSFT: case KC_RSFT:
        case QK_ONE_SHOT_MOD ... QK_ONE_SHOT_MOD_MAX:
            return true;

        default:
            pending_key = KC_NO;
            return true;
    }

    uint16_t now = timer_read();

    uint16_t raw_keycode = get_event_keycode(record->event, false);

    if (pending_key != KC_NO) {
        for (size_t i = 0; i < combo_count; ++i) {
            if (combo_table[i].first_key == pending_key && combo_table[i].second_key == raw_keycode) {
                tap_code16(combo_table[i].output_key);
                pending_key = KC_NO;
                return false;
            }
        }
        tap_code16(pending_key);
        pending_key = KC_NO;
        return true;
    }

    for (size_t i = 0; i < combo_count; ++i) {
        if (combo_table[i].first_key == raw_keycode) {
            pending_key = raw_keycode;
            deadline = now + COMBO_TIMEOUT_MS;
            return false;
        }
    }

    return true;
}

void combo_housekeeping(void) {
    if (pending_key != KC_NO && timer_expired(timer_read(), deadline)) {
        tap_code16(pending_key);
        pending_key = KC_NO;
    }
}
