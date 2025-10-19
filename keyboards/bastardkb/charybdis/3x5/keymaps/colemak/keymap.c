/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
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

//#include "keymap_colemak.h" // many special chars available
                            //
//#include "quantum_keycodes.h"

enum charybdis_keymap_layers {
    LAYER_BASE = 0,
    LAYER_SYMBOLS,
    LAYER_NUMERAL,
    LAYER_FUNCTION,
    LAYER_POINTER,
};


enum custom_keycodes {
//    OSM_LSFT_T0 = SAFE_RANGE,  // give it a name
//    OSM_LCTL_T0,
//    OSM_LALT_T0,
//    OSM_LGUI_T0,
//    OSM_CW_T0,
    OSM_DE_T0,
    OSM_SE_T0,
    FUN_TRIG_0,
    FUN_TRIG_1
};
//
static uint16_t fun_trig_1_timer = 0;
static uint16_t fun_trig_2_timer = 0;
#define CHORD_TIME 500  // ms window to count as "simultaneous"
//
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case OSM_LSFT_T0:
            if (record->event.pressed) {
                layer_move(LAYER_BASE);
                add_oneshot_mods(MOD_LSFT);
                rgblight_sethsv_noeeprom(0, 255, 255); // red to show shift active
            }
            return false;
        case OSM_LCTL_T0:
            if (record->event.pressed) {
                layer_move(LAYER_BASE);
                add_oneshot_mods(MOD_LCTL);
                rgblight_sethsv_noeeprom(0, 255, 255); // red to show mod active
            }
            return false;
        case OSM_LALT_T0:
            if (record->event.pressed) {
                layer_move(LAYER_BASE);
                add_oneshot_mods(MOD_LALT);
                rgblight_sethsv_noeeprom(0, 255, 255); // red to show mod active
            }
            return false;
        case OSM_LGUI_T0:
            if (record->event.pressed) {
                layer_move(LAYER_BASE);
                add_oneshot_mods(MOD_LGUI);
                rgblight_sethsv_noeeprom(0, 255, 255); // red to show mod active
            }
            return false;
        case OSM_CW_T0:
            if (record->event.pressed) {
                layer_move(LAYER_BASE);
                caps_word_toggle();
                rgblight_sethsv_noeeprom(0, 255, 255); // red to show mod active
            }
            return false;
        case OSM_DE_T0:
            if (record->event.pressed) {
                layer_move(LAYER_BASE);
                tap_code16(A(KC_D));
                rgblight_sethsv_noeeprom(0, 255, 255); // should be blue
            }
            return false;
        case OSM_SE_T0:
            if (record->event.pressed) {
                layer_move(LAYER_BASE);
                tap_code16(A(KC_K));
                rgblight_sethsv_noeeprom(0, 255, 255); // should be blue
            }
            return false;

        case FUN_TRIG_0:
            if (record->event.pressed) {
                fun_trig_1_timer = timer_read();
                if (timer_elapsed(fun_trig_2_timer) < CHORD_TIME) {
                    layer_on(LAYER_FUNCTION);
                }
            }
            return false;

        case FUN_TRIG_1:
            if (record->event.pressed) {
                fun_trig_2_timer = timer_read();
                if (timer_elapsed(fun_trig_1_timer) < CHORD_TIME) {
                    layer_on(LAYER_FUNCTION);
                }
            }
            return false;
    }
    return true;  // let all other keys process normally
}

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#    include "timer.h"
#endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE


// Automatically enable sniping-mode on the pointer layer.
#define CHARYBDIS_AUTO_SNIPING_ON_LAYER LAYER_POINTER

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
static uint16_t auto_pointer_layer_timer = 0;

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 1000
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 8
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#endif     // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

// layer activations
#define TO_BASE TO(LAYER_BASE)
#define TO_SYM TO(LAYER_SYMBOLS)
#define TO_PTR TO(LAYER_POINTER)
#define TO_NUM TO(LAYER_NUMERAL)

#ifndef POINTING_DEVICE_ENABLE
#    define DRGSCRL KC_NO
#    define DPI_MOD KC_NO
#    define S_D_MOD KC_NO
#    define SNIPING KC_NO
#endif // !POINTING_DEVICE_ENABLE

// clang-format off
/** \brief Colemak layout (3 rows, 10 columns). */
#define LAYOUT_LAYER_BASE                                                                     \
       KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,        KC_J,    KC_L,    KC_U,    KC_Y,    KC_ESC, \
       KC_A,    KC_R,    KC_S,    KC_T,    KC_D,        KC_H,    KC_N,    KC_E,    KC_I,    KC_O,   \
       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_K,    KC_M, KC_COMM,  KC_DOT,    KC_QUES,\
                         TO_SYM,  KC_SPC,  TO_PTR,      KC_ENT,  KC_NO

/**
 * \brief Symbols layer.
 */
#define LAYOUT_LAYER_SYMBOLS                                                                  \
    KC_QUOT, KC_EQUAL, KC_AMPR, KC_DLR,  KC_ASTR,       KC_PLUS,  KC_MINUS, CW_TOGG, KC_CIRC, KC_EXLM,\
    KC_DQT,  KC_RPRN,  KC_UNDS, KC_RCBR, KC_RBRC,       KC_LBRC,  KC_LCBR,  OSM(MOD_LSFT), KC_LPRN, OSM(MOD_LCTL),\
    KC_TILD, KC_HASH,  KC_AT,   KC_RABK, KC_PIPE,       KC_GRAVE, KC_LABK,  KC_PERC, KC_BSLS, KC_SLSH,\
                       TO_NUM,  KC_TAB,  KC_BSPC,       KC_NO,    TO_BASE


/**
 * \brief Numeral layout.
 *
 * Primary right-hand layer is numerals and symbols. Numerals
 * are in the standard numpad locations with symbols in the remaining positions.
 */
#define LAYOUT_LAYER_NUMERAL                                                                  \
    KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,         KC_NO,    KC_7,     KC_8,    KC_9,    KC_RBRC, \
    OSM(MOD_LALT),  KC_NO,   KC_NO,   OSM(MOD_LGUI), KC_NO,         KC_NO,    KC_4,     KC_5,    KC_6,    OSM_DE_T0, \
    KC_NO,    KC_DEL,  KC_NO,   KC_NO,   KC_NO,         KC_0,     KC_1,     KC_2,    KC_3,   OSM_SE_T0, \
                       KC_NO,   KC_NO,   FUN_TRIG_0,    FUN_TRIG_1,    TO_BASE

/**
 * \brief Function layer.
 *
 * Secondary right-hand layer has function keys mirroring the numerals on the
 * primary layer with extras on the pinkie column, plus system keys on the inner
 * column. App is on the tertiary thumb key and other thumb keys are duplicated
 * from the base layer to enable auto-repeat.
 */
#define LAYOUT_LAYER_FUNCTION                                                                 \
    KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,         KC_F6,    KC_F7,    KC_F8,   KC_F9,   KC_F10,\
    KC_F11,   KC_F12,  KC_NO,   KC_NO,   KC_NO,         KC_PSCR,  KC_KB_MUTE, KC_KB_VOLUME_DOWN, KC_KB_VOLUME_UP, KC_NO, \
    QK_BOOT,  KC_NO,   KC_NO,   KC_NO,   KC_NO,         KC_NO,    KC_NO,    KC_NO,   KC_NO,   QK_BOOT,\
                       KC_NO,   KC_NO,   KC_NO,         KC_NO,    TO_BASE

/**
 * \brief Navigation layer.
 *
 * Mouse and arrows
 */
#define LAYOUT_LAYER_POINTER                                                               \
    QK_BOOT,    KC_NO,    KC_NO,   KC_NO,   KC_NO,        KC_NO,    KC_NO,    KC_NO,   KC_NO,   KC_NO, \
    SNIPING,  KC_BTN2, DRGSCRL, KC_BTN1, KC_NO,        KC_LEFT,  KC_DOWN,  KC_UP,   KC_RGHT, KC_NO, \
    KC_NO,    KC_NO,    KC_NO,   KC_NO,   KC_NO,        KC_NO,    KC_NO,    KC_NO,   KC_NO,   KC_NO, \
                        KC_NO,   KC_NO,   KC_NO,        KC_NO,    TO_BASE

#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE]     = LAYOUT_wrapper(LAYOUT_LAYER_BASE),
  [LAYER_SYMBOLS]  = LAYOUT_wrapper(LAYOUT_LAYER_SYMBOLS),
  [LAYER_NUMERAL]  = LAYOUT_wrapper(LAYOUT_LAYER_NUMERAL),
  [LAYER_FUNCTION] = LAYOUT_wrapper(LAYOUT_LAYER_FUNCTION),
  [LAYER_POINTER]  = LAYOUT_wrapper(LAYOUT_LAYER_POINTER),
};

// clang-format on

#ifdef POINTING_DEVICE_ENABLE
#    ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (abs(mouse_report.x) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD || abs(mouse_report.y) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD) {
        if (auto_pointer_layer_timer == 0) {
            layer_on(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
            rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
            rgb_matrix_sethsv_noeeprom(HSV_GREEN);
#        endif // RGB_MATRIX_ENABLE
        }
        auto_pointer_layer_timer = timer_read();
    }
    return mouse_report;
}

void matrix_scan_user(void) {
    if (auto_pointer_layer_timer != 0 && TIMER_DIFF_16(timer_read(), auto_pointer_layer_timer) >= CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS) {
        auto_pointer_layer_timer = 0;
        layer_off(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
        rgb_matrix_mode_noeeprom(RGB_MATRIX_DEFAULT_MODE);
#        endif // RGB_MATRIX_ENABLE
    }
}
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#    ifdef CHARYBDIS_AUTO_SNIPING_ON_LAYER
layer_state_t layer_state_set_user(layer_state_t state) {
    charybdis_set_pointer_sniping_enabled(layer_state_cmp(state, CHARYBDIS_AUTO_SNIPING_ON_LAYER));
    return state;
}
#    endif // CHARYBDIS_AUTO_SNIPING_ON_LAYER
#endif     // POINTING_DEVICE_ENABLE

#ifdef RGB_MATRIX_ENABLE
// Forward-declare this helper function since it is defined in
// rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);
#endif




