/* Copyright 2022 DOIO
 * Copyright 2022 HorrorTroll <https://github.com/HorrorTroll>
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

// OLED animation
#include "lib/layer_status/layer_status.h"
#include "secrets.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum layer_names {
    _BASE,
    _EMOJIS,
    _FN1,
    _FN2
};

bool set_scrolling = false;

// Modify these values to adjust the scrolling speed
#define SCROLL_DIVISOR_H 8.0
#define SCROLL_DIVISOR_V 8.0

// Variables to store accumulated scroll values
float scroll_accumulated_h = 0;
float scroll_accumulated_v = 0;

// enum layer_keycodes { };
enum custom_keycodes {
    PWONE = SAFE_RANGE,
    PWTWO,
    PWTHREE,
    PWFOUR,
    HARDPASTE,
    LOCK_SCREEN,
    INTELLIJ_BACK,
    INTELLIJ_FORWARD,
    CMD_SHIFT_T,
    CMD_SHIFT_P,
    DRAG_SCROLL,
    COPY_PASTA,
    DRAGON_DROP,
    FRY_DANCE,
    BENDER_DANCE,
    ITS_DONE,
    MARGED,
    MVP,
    LOL,
    MONKEY_LOOK,
    COPY_PATH,
    COPY_FILENAME,
    TICK_TICK_TASK,
    TICK_TICK_MINI,
    REFACTOR,
    RUN,
    EXTRACT_METHOD,
    INSPECT,
    DISTRACTION_FREE_MODE
};

// Define a type for as many tap dance states as you need
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
    uint16_t single_tap_keycode;
    uint16_t double_tap_keycode;
    uint16_t held;
    uint16_t hold;
} td_tap_t;

enum {
    TASK_EMOJI_LAYER, // Our custom tap dance key; add any other tap dance keys to this enum
    TD_PW_ONE,
    TD_PW_TWO,
    TD_PW_THREE,
    TD_PW_FOUR,
};

// Function associated with all tap dances
td_state_t cur_dance(tap_dance_state_t *state);

// Functions associated with individual tap dances
void ql_finished(tap_dance_state_t *state, void *user_data);
void ql_reset(tap_dance_state_t *state, void *user_data);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*  Row:    0         1        2        3         4      */
    [_BASE] = LAYOUT(
                TD(TD_PW_ONE),     TD(TD_PW_TWO),    TD(TD_PW_THREE),    TD(TD_PW_FOUR),     QK_BOOT,
                REFACTOR,     RUN,    EXTRACT_METHOD,    INSPECT,     TO(_EMOJIS),
                INTELLIJ_BACK,     INTELLIJ_FORWARD,    COPY_PATH,   COPY_FILENAME,  RGB_TOG,
                TD(TASK_EMOJI_LAYER), TICK_TICK_MINI, DISTRACTION_FREE_MODE, CMD_SHIFT_T
            ),

    /*  Row:    0        1        2        3        4       */
    [_EMOJIS] = LAYOUT(
                _______, _______, _______, _______, _______,
                DRAGON_DROP, COPY_PASTA, _______, _______, TO(_FN1),
                ITS_DONE, MARGED, LOL, MONKEY_LOOK, _______,
                TD(TASK_EMOJI_LAYER),     FRY_DANCE,    BENDER_DANCE,    KC_ENT
            ),

    /*  Row:    0        1        2        3        4       */
    [_FN1] = LAYOUT(
                _______, _______, _______, _______, _______,
                _______, _______, _______, _______, TO(_FN2),
                _______, _______, _______, _______, _______,
                _______, _______, _______, _______
            ),

    /*  Row:    0        1        2        3        4        */
    [_FN2] = LAYOUT(
                RGB_SPI, RGB_SPD, _______, QK_BOOT, _______,
                RGB_SAI, RGB_SAD, _______, _______, TO(_BASE),
                RGB_TOG, RGB_MOD, RGB_HUI, _______, _______,
                _______, RGB_VAI, RGB_HUD, RGB_VAD
            ),
};

#ifdef OLED_ENABLE
    bool oled_task_user(void) {
        render_layer_status();

        return true;
    }
#endif

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE] = { ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(KC_DOWN, KC_UP), ENCODER_CCW_CW(KC_PGDN, KC_PGUP) },
    [_EMOJIS]   = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_MS_WH_RIGHT, KC_MS_WH_LEFT) },
    [_FN1]  = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [_FN2]  = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
};
#endif

void keyboard_post_init_user(void) {
    // Set the RGB matrix to solid orange
    rgblight_mode(0);  // Static light mode
    rgblight_sethsv(8, 255, 255);  // Set to orange color
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case ITS_DONE:
        if (record->event.pressed) {
            SEND_STRING(":itsdoneintensifies:");
        } else {
        }
        break;
    case MARGED:
        if (record->event.pressed) {
            SEND_STRING(":marged:");
        } else {
        }
        break;
    case LOL:
        if (record->event.pressed) {
            SEND_STRING(":lol:");
        } else {
        }
        break;
    case MVP:
        if (record->event.pressed) {
            SEND_STRING(":mvp:");
        } else {
        }
        break;
    case COPY_PATH:
        if (record->event.pressed) {
            SEND_STRING(SS_LGUI(SS_LSFT(SS_TAP(X_C))));
        } else {
        }
        break;
    case COPY_FILENAME:
        if (record->event.pressed) {
            SEND_STRING(SS_LGUI(SS_LOPT(SS_LCTL(SS_LSFT(SS_TAP(X_C))))));
        } else {
        }
        break;
    case TICK_TICK_TASK:
        if (record->event.pressed) {
            SEND_STRING(SS_LOPT(SS_LSFT(SS_TAP(X_A))));
        } else {
        }
        break;
    case TICK_TICK_MINI:
        if (record->event.pressed) {
            SEND_STRING(SS_LGUI(SS_LSFT(SS_TAP(X_O))));
        } else {
        }
        break;
    case FRY_DANCE:
        if (record->event.pressed) {
            SEND_STRING(":frydance:");
        } else {
        }
        break;
    case BENDER_DANCE:
        if (record->event.pressed) {
            SEND_STRING(":benderdance:");
        } else {
        }
        break;
    case MONKEY_LOOK:
        if (record->event.pressed) {
            SEND_STRING(":monkey-look:");
        } else {
        }
        break;
    case HARDPASTE:
        if (record->event.pressed) {
            SEND_STRING(SS_LGUI(SS_LSFT(SS_DOWN(X_V))));
        } else {
            SEND_STRING(SS_LGUI(SS_LSFT(SS_UP(X_V))));
        }
        break;
    case LOCK_SCREEN:
        if (record->event.pressed) {
            SEND_STRING(SS_LGUI(SS_LCTL(SS_TAP(X_Q))));
        } else {
        }
        break;
    case INTELLIJ_BACK:
        if (record->event.pressed) {
            SEND_STRING(SS_LGUI(SS_TAP(X_LEFT_BRACKET)));
        } else {
        }
        break;
    case INTELLIJ_FORWARD:
        if (record->event.pressed) {
            SEND_STRING(SS_LGUI(SS_TAP(X_RIGHT_BRACKET)));
        } else {
        }
        break;
    case CMD_SHIFT_T:
        if (record->event.pressed) {
            SEND_STRING(SS_LGUI(SS_LSFT(SS_TAP(X_T))));
        } else {
        }
        break;
    case CMD_SHIFT_P:
        if (record->event.pressed) {
            SEND_STRING(SS_LGUI(SS_LSFT(SS_TAP(X_P))));
        } else {
        }
        break;
    case REFACTOR:
        if (record->event.pressed) {
            SEND_STRING(SS_LSFT(SS_TAP(X_F6)));
        } else {
        }
        break;
    case RUN:
        if (record->event.pressed) {
            SEND_STRING(SS_LGUI(SS_TAP(X_4)));
        } else {
        }
        break;
    case EXTRACT_METHOD:
        if (record->event.pressed) {
            SEND_STRING(SS_LGUI(SS_LOPT(SS_TAP(X_M))));
        } else {
        }
        break;
    case INSPECT:
        if (record->event.pressed) {
            SEND_STRING(SS_LGUI(SS_LOPT(SS_TAP(X_I))));
        } else {
        }
        break;
    case DISTRACTION_FREE_MODE:
        if (record->event.pressed) {
            SEND_STRING(SS_LGUI(SS_LSFT(SS_TAP(X_F12))));
        } else {
        }
        break;
    case DRAGON_DROP:
        if (record->event.pressed) {
            SEND_STRING(":dragon::droplet:");
        } else {
        }
        break;
    case COPY_PASTA:
        if (record->event.pressed) {
            SEND_STRING(":copyright::spaghetti:");
        } else {
        }
        break;
    }
    return true;
};

// Determine the current tap dance state
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) return TD_DOUBLE_TAP;
    else return TD_UNKNOWN;
}

// Initialize tap structure associated with example tap dance key
static td_tap_t ql_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void task_layer_finished(tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:
            SEND_STRING(SS_LOPT(SS_LSFT(SS_TAP(X_A))));
        break;
        case TD_SINGLE_HOLD:
            layer_on(_EMOJIS);
        break;
        case TD_DOUBLE_TAP:
            // Check to see if the layer is already set
                if (layer_state_is(_EMOJIS)) {
                    // If already set, then switch it off
                    layer_off(_EMOJIS);
                } else {
                    // If not already set, then switch the layer on
                    layer_on(_EMOJIS);
                }
        break;
        default:
            break;
    }
}

// Functions that control what our tap dance key does
void pw_one_finished(tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:
            SEND_STRING(SS_TAP(X_SPC));
        break;
        case TD_SINGLE_HOLD:
            // TODO define a hold action for pw one
            layer_on(_EMOJIS);
        break;
        case TD_DOUBLE_TAP:
            SEND_STRING(PW_ONE_STRING);
        break;
        default:
            break;
    }
}

// Functions that control what our tap dance key does
void pw_two_finished(tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:

            break;
        case TD_SINGLE_HOLD:
            // TODO define a hold action for pw two
            layer_on(_EMOJIS);
        break;
        case TD_DOUBLE_TAP:
            SEND_STRING(PW_TWO_STRING);
        break;
        default:
            break;
    }
}

// Functions that control what our tap dance key does
void pw_three_finished(tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:

            break;
        case TD_SINGLE_HOLD:
            // TODO define a hold action for pw three
                layer_on(_EMOJIS);
        break;
        case TD_DOUBLE_TAP:
            SEND_STRING(PW_THREE_STRING);
        break;
        default:
            break;
    }
}

// Functions that control what our tap dance key does
void pw_four_finished(tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:

       break;
        case TD_SINGLE_HOLD:
            // TODO define a hold action for pw four
            layer_on(_EMOJIS);
        break;
        case TD_DOUBLE_TAP:
            SEND_STRING(PW_FOUR_STRING);
        break;
        default:
            break;
    }
}

void ql_reset(tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (ql_tap_state.state == TD_SINGLE_HOLD) {
        layer_on(_BASE);
        layer_off(_EMOJIS);
        layer_off(_FN1);
        layer_off(_FN2);
    }
        ql_tap_state.state = TD_NONE;
}

// Associate our tap dance key with its functionality
tap_dance_action_t tap_dance_actions[] = {
    [TASK_EMOJI_LAYER] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, task_layer_finished, ql_reset),
    [TD_PW_ONE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, pw_one_finished, ql_reset),
    [TD_PW_TWO] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, pw_two_finished, ql_reset),
    [TD_PW_THREE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, pw_three_finished, ql_reset),
    [TD_PW_FOUR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, pw_four_finished, ql_reset),
};

// Set a long-ish tapping term for tap-dance keys
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QK_TAP_DANCE ... QK_TAP_DANCE_MAX:
            return 275;
        default:
            return TAPPING_TERM;
    }
}