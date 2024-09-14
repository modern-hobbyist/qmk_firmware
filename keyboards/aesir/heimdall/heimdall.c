// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "secrets.h"
#include "common.h"

#ifdef SELECT_WORD
#    include "features/select_word.h"
#endif // SELECT_WORD

static uint32_t key_timer;               // timer for last keyboard activity, use 32bit value and function to make longer idle time possible
static void     refresh_rgb(void);       // refreshes the activity timer and RGB, invoke whenever any activity happens
static void     check_rgb_timeout(void); // checks if enough time has passed for RGB to timeout
bool            is_rgb_timeout = false;  // store if RGB has timed out or not in a boolean

void refresh_rgb(void) {
    key_timer = timer_read32(); // store time of last refresh
    if (is_rgb_timeout) {
        is_rgb_timeout = false;
        rgb_matrix_enable_noeeprom();
    }
}

void check_rgb_timeout(void) {
    if (!is_rgb_timeout && timer_elapsed32(key_timer) > RGB_MATRIX_TIMEOUT) // check if RGB has already timeout and if enough time has passed
    {
        rgb_matrix_disable_noeeprom();
        is_rgb_timeout = true;
    }
}
/* Then, call the above functions from QMK's built in post processing functions like so */
/* Runs at the end of each scan loop, check if RGB timeout has occured or not */
void housekeeping_task_kb(void) {
#ifdef RGB_MATRIX_TIMEOUT
    check_rgb_timeout();
#endif
}

/* Runs after each encoder tick, check if activity occurred */
void post_encoder_update_kb(uint8_t index, bool clockwise) {
#ifdef RGB_MATRIX_TIMEOUT
    refresh_rgb();
#endif
}

void suspend_power_down_kb(void) {
    // code will run multiple times while keyboard is suspended
}

void suspend_wakeup_init_kb(void) {
    // code will run on keyboard wakeup
}

// Use this to clear eeprom
// void eeconfig_init_user(void) {
//     eeconfig_update_rgb_matrix_default();
//     rgb_matrix_enable_noeeprom();
// }

/*
 * Sets the CAPSLOCK LED to the capslock status. Needed since the LED is wired
 * in series with the rest of the RGB Matrix.
 */
bool rgb_matrix_indicators_kb(void) {
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(CAPSLOCK_LED, RGB_BLUE);
    } else {
        rgb_matrix_set_color(CAPSLOCK_LED, RGB_BLACK);
    }
    return false;
}

/* Runs after each key press, check if activity occurred */
void post_process_record_kb(uint16_t keycode, keyrecord_t *record) {
#ifdef RGB_MATRIX_TIMEOUT
    if (record->event.pressed) refresh_rgb();
#endif
}

// TODO update this to switch the keymap for mac/windows?
bool process_detected_host_os_kb(os_variant_t detected_os) {
    if (!process_detected_host_os_user(detected_os)) {
        return false;
    }
    switch (detected_os) {
        case OS_MACOS:
        case OS_IOS:
            rgb_matrix_set_color_all(RGB_WHITE);
            break;
        case OS_WINDOWS:
            rgb_matrix_set_color_all(RGB_BLUE);
            break;
        case OS_LINUX:
            rgb_matrix_set_color_all(RGB_ORANGE);
            break;
        case OS_UNSURE:
            rgb_matrix_set_color_all(RGB_RED);
            break;
    }

    return true;
}

/**
 * Default OLED driver, should show the default layer states, though may need to share those across keymaps?
 */
#ifdef OLED_ENABLE
bool oled_task_kb(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case _FN0:
            oled_write_P(PSTR("FN0\n"), false);
            break;
        case _FN1:
            oled_write_P(PSTR("FN1\n"), false);
            break;
        case _FN2:
            oled_write_P(PSTR("FN2\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);

    return false;
}
#endif
