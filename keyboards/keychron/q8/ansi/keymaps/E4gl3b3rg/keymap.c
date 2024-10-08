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
//#include "debug.h"
//#include "print.h"
//#include "rgblight.h"

//bool shift_active = false;


// clang-format off

// ---------------------------
// Layer definitions
// ---------------------------
enum layers {
    MAC_BASE,  // Mac alapértelmezett réteg
    WIN_BASE,  // Windows alapértelmezett réteg
    _FN1,      // Funkció rétegek
    _FN2,
    _FN3		// Caps lock gombra
};

// ---------------------------
// Tap Dance declarations
// ---------------------------
enum {
    TD_Q_TAB,     // Q és Tab között váltás
    TD_UP_HOME,   // Page Up és Home között váltás
    TD_DOWN_END,  // Page Down és End között váltás
    TD_C_CTRL_C,
    TD_C_CTRL_V,
//    TD_FN3_ESC,

//    KC_MYSHIFT = SAFE_RANGE,  // A saját egyedi gombodat a SAFE_RANGE után definiáljuk
};

//// Tap Dance funkciók meghatározása
//void dance_fn3_esc_finished(tap_dance_state_t *state, void *user_data) {
//    if (state->count == 1) {
//        // Ha egyszer megnyomja, akkor váltás az _FN3 rétegre
//        layer_invert(_FN3);
//    } else if (state->count == 2) {
//        // Ha kétszer gyorsan megnyomja, akkor ESC
//        tap_code(KC_ESC);
//    }
//}
//
//void dance_fn3_esc_reset(tap_dance_state_t *state, void *user_data) {
//    // Reset funkció szükség esetén, itt nem kell speciális visszaállítás
//}

// ---------------------------
// Tap Dance definitions
// ---------------------------
tap_dance_action_t tap_dance_actions[] = {
    [TD_Q_TAB] = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_TAB),         // Q és Tab között váltás
    [TD_UP_HOME] = ACTION_TAP_DANCE_DOUBLE(KC_PAGE_UP, KC_HOME),// Page Up és Home között váltás
    [TD_DOWN_END] = ACTION_TAP_DANCE_DOUBLE(KC_PAGE_DOWN, KC_END),// Page Down és End között váltás
    [TD_C_CTRL_C] = ACTION_TAP_DANCE_DOUBLE(LCTL(KC_C), KC_END),// Page Down és End között váltás
    [TD_C_CTRL_V] = ACTION_TAP_DANCE_DOUBLE(LCTL(KC_V), KC_END),// Page Down és End között váltás
//    [TD_FN3_ESC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_fn3_esc_finished, dance_fn3_esc_reset),
};











// ---------------------------
// Combos declarations
// ---------------------------
enum combos {
    AB_ESC,       // A és B lenyomása ESC-t eredményez
    JK_TAB,       // J és K lenyomása Tab-ot eredményez
    QW_SFT,       // Q és W lenyomása Shift-et eredményez
    SD_LAYER,     // S és D lenyomása _FN2 rétegre vált
    SHIFTS_CAPS,  // Bal és jobb Shift együttes lenyomása Caps Lock-ot eredményez

};

// ---------------------------
// Combos key definitions
// ---------------------------
const uint16_t PROGMEM ab_combo[] = {KC_A, KC_B, COMBO_END};
const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM qw_combo[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM sd_combo[] = {KC_S, KC_D, COMBO_END};
const uint16_t PROGMEM shifts_combo[] = {KC_LSFT, KC_RSFT, COMBO_END};  // Bal és jobb Shift

// ---------------------------
// Combo actions
// ---------------------------
combo_t key_combos[] = {
    [AB_ESC] = COMBO(ab_combo, KC_ESC),    // A + B -> ESC
    [JK_TAB] = COMBO(jk_combo, KC_TAB),    // J + K -> Tab
    [QW_SFT] = COMBO(qw_combo, KC_LSFT),   // Q + W -> Left Shift
    [SD_LAYER] = COMBO(sd_combo, MO(_FN2)),// S + D -> _FN2 réteg váltás
    [SHIFTS_CAPS] = COMBO(shifts_combo, KC_CAPS),  // Bal és jobb Shift -> Caps Lock
};


//A két sor QMK makrót definiál, amelyek billentyűkombinációkat egyszerűsítenek egyedi billentyűkóddá. Nézzük meg a jelentésüket egyenként:
//#define KC_TASK LGUI(KC_TAB)
//#define KC_FLXP LGUI(KC_E)

#define SLSH_CTRL LT(KC_RCTL, KC_SLSH)

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}



uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD(TD_UP_HOME):
        case TD(TD_DOWN_END):
            return 300;
        default:
            return TAPPING_TERM;  // Az alapértelmezett időzítés
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_ansi_69(
        KC_ESC,   KC_1,     KC_2,     KC_3,    KC_4,    KC_5,    KC_6,     KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,     KC_EQL,           KC_BSPC,          KC_RCTL,
        KC_TAB,   KC_Q,     KC_W,     KC_E,    KC_R,    KC_T,    KC_Y,     KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC,     KC_RBRC,          KC_BSLS,          TD(TD_UP_HOME),
        MO(_FN3), KC_A,     KC_S,     KC_D,    KC_F,    KC_G,              KC_H,    KC_J,    KC_K,    KC_L,     KC_SCLN,     KC_QUOT,          RCTL_T(KC_ENT),   TD(TD_DOWN_END),
        KC_LSFT,           KC_Z,     KC_X,    KC_C,    KC_V,    KC_B,     KC_B,    KC_N,    KC_M,    KC_COMM,  KC_DOT,       RCTL_T(KC_SLSH),  KC_RSFT,  KC_UP,
        KC_LCTL,  KC_LWIN,  KC_LALT,           KC_SPC,           MO(_FN1), MO(_FN2),         KC_SPC,            KC_RALT,     KC_LEFT,          KC_DOWN, KC_RGHT),

   [WIN_BASE] = LAYOUT_ansi_69(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,          _______,          _______, _______,          _______,          _______,          _______, _______, _______),

    [_FN1] = LAYOUT_ansi_69(
        KC_GRV,                       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL, _______,
        _______, QK_UNDERGLOW_TOGGLE, _______, _______, _______, _______, _______, KC_7, KC_8, KC_9, _______, _______, _______, _______, RGB_HUI,
        _______,                      _______, _______, _______, _______, _______, _______, KC_4, KC_5, KC_6, _______, _______, _______, _______,
        _______,                      _______, _______, _______, _______, _______, _______, _______, KC_1, KC_2, KC_3, _______, _______, _______,
        _______,                      _______, _______,          _______,          _______, _______,      KC_GRAVE,    _______,          _______, _______, _______),

    [_FN2] = LAYOUT_ansi_69(
        _______,  KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, _______, _______, _______, QK_BOOT,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, TO(MAC_BASE),
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, TO(WIN_BASE),
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,          _______,          _______, _______,          _______,          _______,          _______, _______, _______),

    [_FN3] = LAYOUT_ansi_69(
        KC_ESC,  _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, KC_DEL,  _______,
        _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_UP,   KC_END,   KC_PGUP, _______, _______, _______, _______,
        _______, _______, _______, KC_LCTL, KC_LSFT, _______, _______, KC_LEFT, KC_DOWN, KC_RIGHT, KC_PGDN, _______, _______, _______,
        _______, _______, _______, LCTL(KC_C), LCTL(KC_V), _______, _______, _______, _______, _______,  _______, _______, _______, _______,
        _______, _______, _______,          _______,          _______, _______,          _______,           _______,          _______, _______, _______)

};


#define MODS_RALT  (MOD_BIT(KC_RALT))  // Jobb Alt modifikátor definiálása

bool process_record_user(uint16_t keycode, keyrecord_t *record) {


    switch (keycode) {
//        case KC_A:
//            if (record->event.pressed) {
//                SEND_STRING("ez mi: árvíztűrő tükörfúrógép &*#$<>{[");
//            }
//            return false;
        case LALT(KC_COMM):  // bal Alt + , -> hosszú í
            if (record->event.pressed) {
                SEND_STRING(SS_RALT("í"));  // Hosszú "í"
            }
            return false;
        case LALT(KC_4):  // bal Alt + 4 -> $
            if (record->event.pressed) {
                SEND_STRING(">");
            }
            return false;
    }

    static uint16_t esc_timer;  // Timer for KC_ESC handling
    static bool grv_sent = false;  // Indicates whether KC_GRV has been sent

    uint8_t mod_state = get_mods();  // Jelenlegi modifikátorok lekérdezése

    switch (keycode) {
        case KC_ESC:
            if (record->event.pressed) {
                // Start the timer when ESC is pressed
                esc_timer = timer_read();
                grv_sent = false;  // Reset GRV sent flag
                // Optionally hold a modifier or other key here
            } else {
                // Check the duration of the ESC press when released
                if (timer_elapsed(esc_timer) < 500) {
                    // If short press, send ESC
                    tap_code(KC_ESC);
                } else if (!grv_sent) {
                    // If long press and GRV has not been sent, send KC_GRV
                    tap_code(KC_GRV);
                    grv_sent = true;
                }
                // Optionally release the held modifier or other key here
            }
            return false;  // We handled this keypress


	      	case KC_I:
	            if (record->event.pressed & mod_state & MODS_RALT ) {
    	            tap_code(KC_UP);  // Jobbra Alt + I = Fel
        	        return false;
            	}
            	break;
/*
			case KC_I:
				if (record->event.pressed) {
					if (get_mods() & MOD_BIT(KC_RALT)) {
						del_mods(MOD_BIT(KC_RALT));  // Távolítsd el a jobb Alt-ot
						register_code(KC_UP);        // Regisztrálja a fel kurzort
                    	set_mods(MOD_BIT(KC_RALT));  // Állítsd vissza a jobb Alt-ot
					} else {
						tap_code(KC_I);  // Ellenkező esetben írja be az 'i' betűt
					}
				} else {
					unregister_code(KC_UP);  // Amikor felengeded a gombot, állítsa le a kurzort
				}
				return false;
			case KC_J:
				if (record->event.pressed) {
					if (get_mods() & MOD_BIT(KC_RALT)) {
						del_mods(MOD_BIT(KC_RALT));  // Távolítsd el a jobb Alt-ot
						register_code(KC_LEFT);      // Regisztrálja a balra kurzort
						set_mods(MOD_BIT(KC_RALT));  // Állítsd vissza a jobb Alt-ot
					} else {
						tap_code(KC_J);  // Ellenkező esetben írja be a 'j' betűt
					}
				} else {
					unregister_code(KC_LEFT);  // Amikor felengeded a gombot, állítsa le a kurzort
				}
				return false;
			case KC_K:
				if (record->event.pressed) {
					if (get_mods() & MOD_BIT(KC_RALT)) {
						del_mods(MOD_BIT(KC_RALT));  // Távolítsd el a jobb Alt-ot
						register_code(KC_DOWN);      // Regisztrálja a le kurzort
						set_mods(MOD_BIT(KC_RALT));  // Állítsd vissza a jobb Alt-ot
					} else {
						tap_code(KC_K);  // Ellenkező esetben írja be a 'k' betűt
					}
				} else {
					unregister_code(KC_DOWN);  // Amikor felengeded a gombot, állítsa le a kurzort
				}
				return false;
			case KC_L:
				if (record->event.pressed) {
					if (get_mods() & MOD_BIT(KC_RALT)) {
						del_mods(MOD_BIT(KC_RALT));  // Távolítsd el a jobb Alt-ot
						register_code(KC_RIGHT);     // Regisztrálja a jobbra kurzort
						set_mods(MOD_BIT(KC_RALT));  // Állítsd vissza a jobb Alt-ot
					} else {
						tap_code(KC_L);  // Ellenkező esetben írja be az 'l' betűt
					}
				} else {
					unregister_code(KC_RIGHT);  // Amikor felengeded a gombot, állítsa le a kurzort
				}
				return false;


			case KC_U:
				if (record->event.pressed) {
					if (get_mods() & MOD_BIT(KC_RALT)) {
						del_mods(MOD_BIT(KC_RALT));  // Távolítsd el a jobb Alt-ot
//						register_code(KC_HOME);      // Regisztrálja a Home gombot
                    	tap_code(KC_UP);             // Küldd a fel kurzort
						set_mods(MOD_BIT(KC_RALT));  // Állítsd vissza a jobb Alt-ot
					} else {
						tap_code(KC_U);  // Ellenkező esetben írja be az 'u' betűt
					}
				} else {
					unregister_code(KC_HOME);  // Amikor felengeded a gombot, állítsa le a Home-ot
				}
				return false;

			case KC_O:
				if (record->event.pressed) {
					if (get_mods() & MOD_BIT(KC_RALT)) {
						del_mods(MOD_BIT(KC_RALT));  // Távolítsd el a jobb Alt-ot
						register_code(KC_END);       // Regisztrálja az End gombot
						set_mods(MOD_BIT(KC_RALT));  // Állítsd vissza a jobb Alt-ot
					} else {
						tap_code(KC_O);  // Ellenkező esetben írja be az 'o' betűt
					}
				} else {
					unregister_code(KC_END);  // Amikor felengeded a gombot, állítsa le az End-et
				}
				return false;

			case KC_P:
				if (record->event.pressed) {
					if (get_mods() & MOD_BIT(KC_RALT)) {
						del_mods(MOD_BIT(KC_RALT));  // Távolítsd el a jobb Alt-ot
						register_code(KC_PGUP);      // Regisztrálja a Page Up gombot
						set_mods(MOD_BIT(KC_RALT));  // Állítsd vissza a jobb Alt-ot
					} else {
						tap_code(KC_P);  // Ellenkező esetben írja be a 'p' betűt
					}
				} else {
					unregister_code(KC_PGUP);  // Amikor felengeded a gombot, állítsa le a Page Up-ot
				}
				return false;

        case KC_SCLN:
            if (record->event.pressed) {
                if (get_mods() & MOD_BIT(KC_RALT)) {
                    del_mods(MOD_BIT(KC_RALT));  // Távolítsd el a jobb Alt-ot
                    register_code(KC_PGDN);      // Regisztrálja a Page Down gombot
                    set_mods(MOD_BIT(KC_RALT));  // Állítsd vissza a jobb Alt-ot
                } else {
                    tap_code(KC_SCLN);  // Ellenkező esetben írja be a ';' karaktert
                }
            } else {
                unregister_code(KC_PGDN);  // Amikor felengeded a gombot, állítsa le a Page Down-t
            }
            return false;


        case KC_4:
            if (record->event.pressed) {
                if (get_mods() & MOD_BIT(KC_LGUI)) {
                    del_mods(MOD_BIT(KC_LGUI));  // Távolítsd el a jobb Alt-ot
                    register_code(KC_5);      // Regisztrálja a Page Down gombot
                    set_mods(MOD_BIT(KC_LGUI));  // Állítsd vissza a jobb Alt-ot
                } else {
                    tap_code(KC_4);  // Ellenkező esetben írja be a ';' karaktert
                }
            } else {
                unregister_code(KC_5);  // Amikor felengeded a gombot, állítsa le a Page Down-t
            }
            return false;
*/
        // Add other keycodes here if needed

    }

    return true;  // We didn't handle other keypresses
}


