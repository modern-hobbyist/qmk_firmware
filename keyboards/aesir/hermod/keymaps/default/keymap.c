// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┐   ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┐
     * │Esc│   │F1 │F2 │F3 │F4 │ │F5 │F6 │F7 │F8 │ │F9 │F10│F11│F12│ │PSc│Scr│Pse│
     * └───┘   └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┘
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐ ┌───┬───┬───┐ ┌───┬───┬───┬───┐
     * │ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ Backsp│ │Ins│Hom│PgU│ │Num│ / │ * │ - │
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤ ├───┼───┼───┤ ├───┼───┼───┼───┤
     * │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │  \  │ │Del│End│PgD│ │ 7 │ 8 │ 9 │   │
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤ └───┴───┴───┘ ├───┼───┼───┤ + │
     * │ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │  Enter │               │ 4 │ 5 │ 6 │   │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤     ┌───┐     ├───┼───┼───┼───┤
     * │ Shift  │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │    Shift │     │ ↑ │     │ 1 │ 2 │ 3 │   │
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤ ┌───┼───┼───┐ ├───┴───┼───┤Ent│
     * │Ctrl│GUI │Alt │                        │ Alt│ GUI│Menu│Ctrl│ │ ← │ ↓ │ → │ │   0   │ . │   │
     * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘ └───┴───┴───┘ └───────┴───┴───┘
     */
    [0] = LAYOUT(
                // Left Half
                KC_NO,  KC_ESC,     KC_NO,      KC_NO,  KC_NO,  KC_NO,          KC_NO,                              KC_NUM, KC_PSLS, KC_PAST,   KC_PMNS,
                KC_NO,  KC_GRV,     KC_1,       KC_2,   KC_3,   KC_4,           KC_5,                               KC_P7,  KC_P8,   KC_P9,     KC_PPLS,
                KC_NO,  KC_TAB,     KC_Q,       KC_W,   KC_E,   KC_R,           KC_T,                               KC_P4,  KC_P5,   KC_P6,     KC_PEQL,
                KC_NO,  KC_LSFT,    KC_A,       KC_S,   KC_D,   KC_F,           KC_G,                               KC_P1,  KC_P2,   KC_P3,     KC_NO,
                KC_NO,  KC_CAPS,    KC_Z,       KC_X,   KC_C,   KC_V,           KC_B,                               KC_NO,  KC_P0,   KC_PDOT,   KC_PENT,
                                                                                        KC_LALT,        KC_LCTL,
                                                                                        KC_LGUI,    KC_SPACE,

                // Right Half
                KC_NO,          KC_NO,      KC_NO,      KC_NO,      KC_NO,      KC_DEL,     KC_BSPC,                KC_NUM,   KC_PSLS, KC_PAST,   KC_PMNS,
                KC_6,           KC_7,       KC_8,       KC_9,       KC_0,       KC_MINS,    KC_EQL,                 KC_P7,    KC_P8,   KC_P9,     KC_PPLS,
                KC_Y,           KC_U,       KC_I,       KC_O,       KC_P,       KC_LBRC,    KC_RBRC,                KC_P4,    KC_P5,   KC_P6,     KC_PEQL,
                KC_H,           KC_J,       KC_K,       KC_L,       KC_SCLN,    KC_QUOT,    KC_NO,                  KC_P1,    KC_P2,   KC_P3,     KC_NO,
                KC_N,           KC_M,       KC_COMM,    KC_DOT,     KC_SLSH,    KC_MINS,    KC_RSFT,                KC_PENT,  KC_P0,   KC_PDOT,   KC_PENT,
                KC_LALT,        KC_LCTL,                KC_UP,
                                            KC_LEFT,    KC_DOWN,    KC_RIGHT,
                KC_LGUI,  KC_SPACE
            )
};
