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

#define _LAYER_IDX_MAX 4
#define _LAYER_FN 2
#define _LAYER_MEDIA 3

#define _MAGIC_HUE 63

static uint8_t _layernum = 0;

enum encoder_names {
  _LEFT,
  _RIGHT,
  _MIDDLE,
};

void custom_set_layercolor(void);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_MS_BTN1, KC_MS_BTN3, KC_MS_BTN2,
        KC_F13, KC_W,KC_F14,
        KC_A, KC_S, KC_D
    ),
    [1] = LAYOUT(
        _______, _______, _______,
        KC_DELETE, KC_PGUP, KC_PSCREEN,
        KC_END, KC_PGDOWN , KC_HOME
    ),
    [2] = LAYOUT(
        _______, _______, _______,
        KC_F15 ,KC_F16, KC_F17,
        KC_F18, KC_F19, KC_F20
    ),
    [3] = LAYOUT(
        KC_MPLY  ,KC_STOP, KC_MUTE,
        KC_MRWD, KC_MSEL, KC_MFFD,
        KC_LEFT, KC_STOP , KC_RIGHT
    ),
    [4] = LAYOUT(
        RGB_TOG ,KC_SYSTEM_POWER, RESET,
        XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX , XXXXXXX
    )
};

void custom_set_layercolor(void) {
    if(!rgblight_is_enabled()) {
        rgblight_enable();
    }
    switch (_layernum)
    {
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
    }
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == _LEFT) {
        if(_layernum == _LAYER_MEDIA) {
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
        }
        else {
            if (clockwise) {
                tap_code(KC_MS_LEFT);
            } else {
                tap_code(KC_MS_RIGHT);
            }
        }
    }
    else if (index == _RIGHT) {
        if(_layernum == _LAYER_MEDIA) {
            if (clockwise) {
                tap_code(KC_MNXT);
            } else {
                tap_code(KC_MPRV);
            }
        }
        else {
            if (clockwise) {
                tap_code(KC_MS_UP);
            } else {
                tap_code(KC_MS_DOWN);
            }
        }
    }
    else if (index == _MIDDLE) {
        if (clockwise) {
            _layernum = _layernum + 1;
            if(_layernum > _LAYER_IDX_MAX) {
                _layernum = 0;
            }

        } else {
            if(_layernum == 0) {
                _layernum = _LAYER_IDX_MAX;
            }
            else {
                _layernum = _layernum - 1;
            }
        }
        custom_set_layercolor();
        layer_move(_layernum);
    }
    return true;
}

void keyboard_post_init_user(void) {
    custom_set_layercolor();
    rgblight_set_speed(192);
}