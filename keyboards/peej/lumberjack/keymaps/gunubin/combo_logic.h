// combo_logic.h
#pragma once

#include "quantum.h"

#define COMBO_TIMEOUT_MS 200

typedef struct {
    uint16_t first_key;
    uint16_t second_key;
    uint16_t output_key;
} combo_entry_t;

void init_combos(const combo_entry_t *entries, size_t count);
bool process_combo_keys(uint16_t keycode, keyrecord_t *record);
void combo_housekeeping(void);
