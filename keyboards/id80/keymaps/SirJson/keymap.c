/* Copyright 2020 Sergey Vlasov <sigprof@gmail.com>
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,    KC_F1,   KC_F2,   KC_F3,   KC_F4,     KC_F5,   KC_F6,   KC_F7,   KC_F8,     KC_F9,   KC_F10,  KC_F11,  KC_F12,     AL_LOCK,     KC_DEL,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,            KC_PGUP,
        KC_TAB,      KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,        KC_PGDOWN,
        HYPR_T(KC_ESC),       KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT,            KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RSFT_T(KC_LEAD),          KC_UP,
        KC_LCTL,   KC_LGUI,   KC_LALT,                       KC_SPC,                              KC_RALT,     OSL(1),        KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [1] = LAYOUT(
        RESET,      KC_F13,     KC_F14,     KC_F15,     KC_F16,     KC_F17,     KC_F18,     KC_F19,     KC_F20,     KC_F21,     KC_F22,     KC_F23,     KC_F24,     KC_TRNS,    KC_PSCR,
        DEBUG,      KC_MUTE,    KC_MSTP,    KC_MPLY,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_MPRV,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_EXEC,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_UNDO,    KC_INSERT,    KC_TRNS,    KC_PAUSE,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_MNXT,
        KC_TRNS,    KC_AGIN,    KC_SLCT,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_CUT,    KC_COPY,    KC_PSTE,   KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_MENU,    KC_TRNS,    KC_TRNS,    KC_TRNS,                         KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,                    KC_TRNS,                            KC_TRNS,    KC_TRNS,                                                   KC_TRNS, KC_TRNS,  KC_TRNS
    ),
};
LEADER_EXTERNS();

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    SEQ_ONE_KEY(KC_LEFT) {
        tap_code(KC_HOME);
    }
    SEQ_ONE_KEY(KC_RIGHT) {
        tap_code(KC_END);
    }
    SEQ_TWO_KEYS(KC_L, KC_DELETE) {
      register_code(KC_LCTL);
      register_code(KC_LSFT);
      register_code(KC_K);
      unregister_code(KC_K);
      unregister_code(KC_LSFT);
      unregister_code(KC_LCTL);
    }
    SEQ_TWO_KEYS(KC_D, KC_D) {
      SEND_STRING(SS_LCTL("a") SS_LCTL("c"));
    }
    SEQ_TWO_KEYS(KC_Q, KC_A) {
      SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_F4) SS_UP(X_LALT));
    }
    SEQ_ONE_KEY(KC_P) {
      SEND_STRING(SS_LCTL("v"));
    }
    SEQ_ONE_KEY(KC_W) {
      SEND_STRING(SS_LCTL("s"));
    }
  }
}
