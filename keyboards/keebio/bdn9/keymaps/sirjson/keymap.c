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

enum encoder_names {
  _LEFT,
  _RIGHT,
  _MIDDLE,
};

#define _MAIN 0
#define _EXT  1
#define _CFG 2


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
        | F12     | F11 | MEDIA_PLAY_PAUSE |
        | F15     | F14 | F13              |
        | LAYER 1 | F17 | F16              |
     */
    [_MAIN] = LAYOUT(
        KC_F12, KC_F11, KC_MEDIA_PLAY_PAUSE,
        KC_F15, KC_F14, KC_F13,
        MO(_EXT), KC_F17, KC_F16
    ),
    /*
        |         |      |                  |
        | NUM2    | F18  | NUM1             |
        | NUM2    | NUM3 | NUM4             |
     */
    [_EXT] = LAYOUT(
        TO(_CFG), KC_P6, KC_P7,
        KC_F18, KC_P1, KC_P2,
        _______, KC_P3 , KC_P4
    ),
    [_CFG] = LAYOUT(
        TO(_MAIN), TO(_MAIN), TO(_MAIN),
        QK_BOOTLOADER, QK_REBOOT, QK_CLEAR_EEPROM,
        RGB_TOG,  RGB_SPD, RGB_SPI
    ),
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == _LEFT) {
        switch (get_highest_layer(layer_state)) {
            case _CFG:
                if (clockwise) {
                    rgb_matrix_increase_hue();
                } else {
                    rgb_matrix_decrease_hue();
                }
                break;
            case _MAIN:
            default:
                if (clockwise) {
                    tap_code(KC_F19);
                } else {
                    tap_code(KC_F20);
                }
                break;
        }

    } else if (index == _MIDDLE) {
        switch (get_highest_layer(layer_state)) {
            case _CFG:
                if (clockwise) {
                    rgb_matrix_increase_sat();
                } else {
                    rgb_matrix_decrease_sat();
                }
                break;
            case _MAIN:
            default:
                if (clockwise) {
                    tap_code(KC_F21);
                } else {
                    tap_code(KC_F22);
                }
                break;
        }
    } else if (index == _RIGHT) {
        switch (get_highest_layer(layer_state)) {
            case _CFG:
                if (clockwise) {
                    rgb_matrix_increase_val();
                } else {
                    rgb_matrix_decrease_val();
                }
                break;
            case _MAIN:
            default:
                if (clockwise) {
                    tap_code(KC_F23);
                } else {
                    tap_code(KC_F24);
                }
                break;
        }
    }
    return false;
}

void keyboard_post_init_user(void) {
    rgb_matrix_mode(DEFAULT_LAYER_RGB_MATRIX);
}

void eeconfig_init_user(void) {
    rgb_matrix_mode(DEFAULT_LAYER_RGB_MATRIX);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    #ifdef RGB_MATRIX_ENABLE
    switch (get_highest_layer(state)) {
    case _EXT:
        rgb_matrix_mode_noeeprom(EXT_LAYER_RGB_MATRIX);
        break;
    case _CFG:
        rgb_matrix_mode_noeeprom(CFG_LAYER_RGB_MATRIX);
        break;
    case _MAIN:
    default: //  for any other layers, or the default layer
        rgb_matrix_mode_noeeprom(DEFAULT_LAYER_RGB_MATRIX);
        break;
    }
    #endif
  return state;
}
