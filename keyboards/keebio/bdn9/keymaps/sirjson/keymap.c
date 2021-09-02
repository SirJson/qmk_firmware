/* Copyright 2019 Danny Nguyen <danny@keeb.io>
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
#include <stdint.h>

enum custom_keycodes {
    DCM_1 = SAFE_RANGE,


    DCM_2, DCM_3,

    DCM_4, DCM_5, DCM_6, DCM_7, DCM_8,
    DCM_9
};

#define _LAYER_IDX_MAX 5
#define _MPROFILE_IDX_MAX 2
#define _LAYER_FN 2
#define _LAYER_MEDIA 3
#define _LAYER_SYS 4
#define _LAYER_DISCORD 5
#define _LEDFLASH_TIME 1200
#define _MAGIC_HUE 63

static uint8_t _layernum = 0;
static uint8_t _macroprofile = 0;
static uint16_t led_flash_timer;

enum encoder_names {
    _LEFT,
    _RIGHT,
    _MIDDLE,
};

void custom_set_layercolor(int);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_MS_BTN1, KC_MS_BTN2, KC_F24,
        KC_LSHIFT, KC_W, KC_C,
        KC_A, KC_S, KC_D),
    [1] = LAYOUT(_______, _______, _______,
    KC_DELETE, KC_PGUP, KC_PSCREEN,
     KC_HOME, KC_PGDOWN, KC_END
     ), [2] = LAYOUT(_______, _______, _______, KC_F15, KC_F16, KC_F17, KC_F18, KC_F19, KC_F20),
    [3] = LAYOUT(KC_MPLY, KC_STOP, KC_MUTE, KC_MRWD, KC_MSEL, KC_MFFD, KC_LEFT, KC_STOP, KC_RIGHT),
    [4] = LAYOUT(RGB_TOG, KC_SYSTEM_POWER, RESET, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX),
    [5] = LAYOUT(
        DCM_1, DCM_2, DCM_3,
        DCM_4, DCM_5, DCM_6,
        DCM_7, DCM_8, DCM_9
    )
};

#define MRS(umes) (umes SS_TAP(X_RETURN) SS_TAP(X_ENTER))

const char* textmacros[_MPROFILE_IDX_MAX+1][9] = {
    {
        ".give",
        ".remind me 1h",
        ".br 100",
         MRS(".timely"),
         MRS(".xp"),
         MRS(".slot 100"),
         MRS(".$"),
         MRS(".pick"),
         MRS("hey what is up ya all")
    },
        {
        ".give",
        ".remind me 2h",".br 100",
         MRS(".timely"),
         MRS(".clubinfo"),
         MRS(".slot 200"),
         MRS(".$"),
         MRS(".pick"),
         MRS("nice")
    },
    { // TODO: ! commands?
        ".give",".remind me 5h",".br 100",
         MRS(".timely"), MRS(".xp"),  MRS(".slot 300"),
         MRS(".$"), MRS(".pick"), MRS("police")
    }
};

#define TXTMACRO(m,i) (textmacros[(i)][(m) - SAFE_RANGE])

void custom_set_layercolor(int newlayer) {
    if (!rgblight_is_enabled()) {
        rgblight_enable();
    }

    switch (newlayer) {
        case 0:
            rgblight_sethsv(0, 255, 255);
            rgblight_mode(RGBLIGHT_MODE_KNIGHT);
            break;
        case 1:
            rgblight_sethsv(196, 255, 255);
            rgblight_mode(RGBLIGHT_MODE_CHRISTMAS);
            break;
        case 2:
            rgblight_sethsv(85, 255, 255);
            rgblight_mode(RGBLIGHT_MODE_SNAKE + 1);
            break;
        case 3:
            rgblight_sethsv(169, 255, 255);
            rgblight_mode(RGBLIGHT_MODE_BREATHING + 2);
            break;
        case 4:
            rgblight_sethsv(30, 255, 255);
            rgblight_mode(RGBLIGHT_MODE_SNAKE + 3);
            break;
        case 5:
            rgblight_sethsv(HSV_GREEN);
            rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
            sethsv(HSV_RED, (LED_TYPE *)&led[6 + _macroprofile]);
            sethsv(HSV_BLUE, (LED_TYPE *)&led[3 + _macroprofile]);
            rgblight_set(); // Utility functions do not call rgblight_set() automatically, so they need to be called explicitly.
            break;
    }
}

inline int move_up(int clayer, int lmax) {
    int out = clayer + 1;
    if (out > lmax) {
        out =  0;
    }
    return out;
}

inline int move_down(int clayer, int lmax) {
    if(clayer > 0) {
        return clayer - 1;
    }
    else {
        return lmax;
    }
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == _LEFT) {
        if (_layernum == _LAYER_MEDIA) {
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
        } else {
            if (clockwise) {
                tap_code(KC_MS_LEFT);
            } else {
                tap_code(KC_MS_RIGHT);
            }
        }
    } else if (index == _MIDDLE) {
        if (_layernum == _LAYER_MEDIA) {
            if (clockwise) {
                tap_code(KC_MNXT);
            } else {
                tap_code(KC_MPRV);
            }
        } else if(_layernum == _LAYER_DISCORD) {
            _macroprofile = (clockwise) ? move_up(_macroprofile, _MPROFILE_IDX_MAX) : move_down(_macroprofile, _MPROFILE_IDX_MAX);
            custom_set_layercolor(_layernum);
        }
        else {
            if (clockwise) {
                tap_code(KC_MS_UP);
            } else {
                tap_code(KC_MS_DOWN);
            }
        }
    } else if (index == _RIGHT) {
        _layernum = (clockwise) ? move_up(_layernum, _LAYER_IDX_MAX) : move_down(_layernum, _LAYER_IDX_MAX);
        custom_set_layercolor(_layernum);
        layer_move(_layernum);
    }
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if(_layernum != _LAYER_DISCORD || keycode < DCM_1 || keycode > DCM_9) return true;
    if (record->event.pressed) {
        SEND_STRING(TXTMACRO(keycode,_macroprofile));

    }
    else {
        led_flash_timer = timer_read();
        rgblight_mode(RGBLIGHT_MODE_KNIGHT  + 2);
    }
    return true;
};

void matrix_scan_user(void) {
    if(led_flash_timer != 0 && timer_elapsed(led_flash_timer) > _LEDFLASH_TIME) {
        custom_set_layercolor(_layernum);
        led_flash_timer = 0; // Clear
    }
}

void keyboard_post_init_user(void) {
    custom_set_layercolor(_layernum);
    rgblight_set_speed(192);
}
