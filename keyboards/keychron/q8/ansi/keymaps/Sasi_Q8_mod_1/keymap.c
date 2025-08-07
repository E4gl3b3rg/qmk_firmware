/* Copyright 2021 @ Keychron (https://www.keychron.com)
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

// clang-format off

enum layers {
    WIN_BASE,
    _FN1,
    _FN2,
    _FN3,
    _FN4,
};

// ---------------------------
// Tap Dance declarations
// ---------------------------
enum {
    TD_HOME_UP,   // Page Up és Home között váltás
    TD_END_DOWN,  // Page Down és End között váltás
};

// Definiálj egyedi keycode-okat
// A többi elem automatikusan a következő értékeket kapja.
enum custom_keycodes {
    CUSTOM_COPY = SAFE_RANGE,  // pl. 1000 (példa)
    CUSTOM_PASTE,              // 1001
};
// ---------------------------
// Tap Dance definitions
// ---------------------------
tap_dance_action_t tap_dance_actions[] = {
    [TD_HOME_UP]  = ACTION_TAP_DANCE_DOUBLE(KC_PAGE_UP,KC_HOME),  // Page Up és Home között váltás
    [TD_END_DOWN] = ACTION_TAP_DANCE_DOUBLE(KC_PAGE_DOWN,KC_END),  // Page Down és End között váltás    
};

// Időzítő és időtartam definiálása
#define HOLD_THRESHOLD 200  // ms, mennyi ideig kell tartani a gombot hosszan tartásnak
static uint16_t custom_copy_timer;
static uint16_t custom_paste_timer;
static bool custom_copy_active = false;
static bool custom_paste_active = false;
static bool custom_copy_held = false;
static bool custom_paste_held = false;

#define KC_TASK LGUI(KC_TAB)
#define KC_FLXP LGUI(KC_E)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [WIN_BASE] = LAYOUT_ansi_69(
        KC_ESC,  KC_1,     KC_2,     KC_3,    KC_4,    KC_5,    KC_6,     KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL         ,  KC_BSPC,          KC_RCTL,
        KC_TAB,  KC_Q,     KC_W,     KC_E,    KC_R,    KC_T,    KC_Y,     KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC,  KC_RBRC        ,  KC_BSLS,          TD(TD_HOME_UP),
        MO(_FN3),KC_A,     KC_S,     KC_D,    KC_F,    KC_G,              KC_H,    KC_J,    KC_K,    KC_L,     KC_SCLN,  KC_QUOT        ,  KC_ENT,           TD(TD_END_DOWN),
        KC_LSFT      ,   KC_Z, KC_X, CUSTOM_COPY, CUSTOM_PASTE, KC_B,     KC_B,    KC_N,    KC_M,    KC_COMM,  KC_DOT,   RCTL_T(KC_SLSH),  KC_RSFT, KC_UP,
        KC_LCTL      ,  KC_LWIN,  KC_LALT,           KC_SPC,           MO(_FN1), MO(_FN2),         KC_SPC,            KC_RALT,                    KC_LEFT, KC_DOWN, KC_RGHT),

    [_FN1] = LAYOUT_ansi_69(
        KC_GRV       ,  KC_F1  ,  KC_F2  ,  KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7   , KC_F8  , KC_F9  , KC_F10 ,  KC_F11 ,  KC_F12 ,  KC_NO  ,          KC_NO  ,
        KC_NO        , KC_NO  ,  KC_NO  ,  KC_NO  , KC_NO  , KC_NO  , KC_NO  ,  KC_NO  , KC_NO  , KC_NO  , KC_NO  ,  KC_NO  ,  KC_NO  ,  KC_NO  ,          KC_NO  ,
        KC_NO        , KC_NO  ,  KC_NO  ,  KC_NO  , KC_NO  , KC_NO  ,           KC_NO  , KC_NO  , KC_NO  , KC_NO  ,  KC_NO  ,  KC_NO  ,  KC_NO  ,          KC_NO  ,
        KC_NO        ,           KC_NO  ,  KC_NO  , KC_NO  , KC_NO  , KC_NO  ,  KC_NO  , KC_NO  , KC_NO  , KC_NO  ,  KC_NO  ,  KC_NO  ,  KC_NO  , KC_NO  ,
        KC_NO        , KC_NO  ,  KC_NO  ,           KC_NO  ,          KC_NO  ,  KC_NO  ,          KC_NO  ,           KC_NO  ,            KC_NO  , KC_NO  , KC_NO  ),

    [_FN2] = LAYOUT_ansi_69(
        KC_NO        , KC_F1  ,  KC_F2  ,  KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7   , KC_F8  , KC_F9  , KC_F10 ,  KC_F11 ,  KC_F12 ,  KC_NO  ,          QK_BOOT,
        KC_NO        , KC_NO  ,  KC_NO  ,  KC_NO  , KC_NO  , KC_NO  , KC_NO  ,  KC_NO  , KC_NO  , KC_NO  , KC_NO  ,  KC_NO  ,  KC_NO  ,  KC_NO  ,          RGB_TOG,
        KC_NO        , KC_NO  ,  KC_NO  ,  KC_NO  , KC_NO  , KC_NO  ,           KC_NO  , KC_NO  , KC_NO  , KC_NO  ,  KC_NO  ,  KC_NO  ,  KC_NO  ,          KC_NO  ,
        KC_NO        ,           KC_NO  ,  KC_NO  , KC_NO  , KC_NO  , KC_NO  ,  KC_NO  , KC_NO  , KC_NO  , KC_NO  ,  KC_NO  ,  KC_NO  ,  KC_NO  , KC_NO  ,
        KC_NO        , KC_NO  ,  KC_NO  ,           KC_NO  ,          KC_NO  ,  KC_NO  ,          KC_NO  ,           KC_NO  ,            KC_NO  , KC_NO  , KC_NO  ),

    [_FN3] = LAYOUT_ansi_69(
        KC_TILD, KC_F1,    KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,    KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,   KC_F12,   KC_DEL ,          KC_INS  ,
        KC_NO  , KC_NO  ,  KC_NO  ,  KC_NO  , KC_NO  , KC_NO  , KC_PGUP,  KC_HOME, KC_UP  , KC_END  ,KC_PGUP,  KC_NO  ,  KC_NO  ,                    KC_NO  ,
        KC_NO  , KC_NO  ,  KC_NO  ,  KC_NO  , KC_NO  , KC_NO  , KC_NO  ,  KC_PGDN,  KC_LEFT, KC_DOWN, KC_RIGHT,KC_PGDN,  KC_NO  ,  KC_NO  ,          KC_NO  ,
        KC_NO  ,           KC_NO  ,  KC_NO  , KC_NO  , KC_NO  , KC_NO  ,  KC_NO  , KC_NO  , KC_NO  , KC_NO  ,  KC_NO  ,  KC_NO  ,  KC_NO  , KC_NO  ,
        KC_NO  , KC_NO  ,  KC_NO  ,           KC_NO  ,          KC_NO  ,  KC_NO  ,          KC_NO  ,           KC_NO  ,            KC_NO  , KC_NO  , KC_NO  ),

    [_FN4] = LAYOUT_ansi_69(
        KC_TILD, KC_F1,    KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,    KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,   KC_F12,   KC_NO  ,          KC_NO  ,
        KC_NO  , KC_NO  ,  KC_NO  ,  KC_NO  , KC_NO  , KC_NO  , KC_NO  ,  KC_NO  , KC_NO  , KC_NO  , KC_NO  ,  KC_NO  ,  KC_NO  ,  KC_NO  ,          KC_NO  ,
        KC_NO  , KC_NO  ,  KC_NO  ,  KC_NO  , KC_NO  , KC_NO  ,           KC_NO  , KC_NO  , KC_NO  , KC_NO  ,  KC_NO  ,  KC_NO  ,  KC_NO  ,          KC_NO  ,
        KC_NO  ,           KC_NO  ,  KC_NO  , KC_NO  , KC_NO  , KC_NO  ,  KC_NO  , KC_NO  , KC_NO  , KC_NO  ,  KC_NO  ,  KC_NO  ,  KC_NO  , KC_NO  ,
        KC_NO  , KC_NO  ,  KC_NO  ,           KC_NO  ,          KC_NO  ,  KC_NO  ,          KC_NO  ,           KC_NO  ,            KC_NO  , KC_NO  , KC_NO  )

};

// process_record_user implementációja
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CUSTOM_COPY:
            if (record->event.pressed) {
                custom_copy_timer = timer_read();
                custom_copy_active = true;
                custom_copy_held = false;
            } else {
                if (!custom_copy_held) {
                    tap_code(KC_C); // rövid nyomás
                }
                custom_copy_active = false;  // vége a gombnyomásnak
            }
            return false;

        case CUSTOM_PASTE:
            if (record->event.pressed) {
                custom_paste_timer = timer_read();
                custom_paste_active = true;
                custom_paste_held = false;
            } else {
                if (!custom_paste_held) {
                    tap_code(KC_V); // rövid nyomás
                }
                custom_paste_active = false;
            }
            return false;
    }
    return true;
}

// timer-rel figyelés: matrix_scan_user
void matrix_scan_user(void) {
    if (custom_copy_active && !custom_copy_held &&
        timer_elapsed(custom_copy_timer) > HOLD_THRESHOLD &&
        (get_mods() & MOD_MASK_CTRL) == 0) {
        // hosszú nyomás és még mindig nyomva van
        register_code(KC_LCTL);
        tap_code(KC_C);
        unregister_code(KC_LCTL);
        custom_copy_held = true;
    }

    if (custom_paste_active && !custom_paste_held &&
        timer_elapsed(custom_paste_timer) > HOLD_THRESHOLD &&
        (get_mods() & MOD_MASK_CTRL) == 0) {
        register_code(KC_LCTL);
        tap_code(KC_V);
        unregister_code(KC_LCTL);
        custom_paste_held = true;
    }
}



