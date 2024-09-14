// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "quantum.h"
#include "common.h"

// OLED animation
#include "lib/logo.h"

void suspend_power_down_kb(void) {
    // code will run multiple times while keyboard is suspended
}

void suspend_wakeup_init_kb(void) {
    // code will run on keyboard wakeup
}

// Default timeout for displaying boot logo.
#ifndef OLED_LOGO_TIMEOUT
#    define OLED_LOGO_TIMEOUT 3500
#endif

#ifdef OLED_ENABLE
uint16_t startup_timer;

oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    startup_timer = timer_read();
    return rotation;
}

bool oled_task_kb(void) {
    static bool finished_logo = false;

    if (!finished_logo) {
        finished_logo = render_logo();
    } else {
        if (!oled_task_user()) {
            return false;
        }
    }

    return true;
}
#endif
