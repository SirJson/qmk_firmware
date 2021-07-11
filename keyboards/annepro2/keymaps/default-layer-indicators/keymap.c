#include <stdint.h>
#include <memory.h>
#include "annepro2.h"
#include "qmk_ap2_led.h"
#include "config.h"
#include "raw_hid.h"
#include "usb_descriptor.h"
#include "annepro2_ble.h"

enum anne_pro_layers {
  _BASE_LAYER,
  _FN1_LAYER,
  _FN2_LAYER,
};

// Key symbols are based on QMK. Use them to remap your keyboard
/*
* Layer _BASE_LAYER
* ,-----------------------------------------------------------------------------------------.
* | esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |    Bksp   |
* |-----------------------------------------------------------------------------------------+
* | Tab    |  q  |  w  |  e  |  r  |  t  |  y  |  u  |  i  |  o  |  p  |  [  |  ]  |   \    |
* |-----------------------------------------------------------------------------------------+
* | Caps    |  a  |  s  |  d  |  f  |  g  |  h  |  j  |  k  |  l  |  ;  |  '  |    Enter    |
* |-----------------------------------------------------------------------------------------+
* | Shift      |  z  |  x  |  c  |  v  |  b  |  n  |  m  |  ,  |  .  |  /  |    Shift       |
* |-----------------------------------------------------------------------------------------+
* | Ctrl  |  L1   |  Alt  |               space             |  Alt  |  FN1  |  FN2  | Ctrl  |
* \-----------------------------------------------------------------------------------------/
* Layer TAP in _BASE_LAYER
* ,-----------------------------------------------------------------------------------------.
* |     |     |     |     |     |     |     |     |     |     |     |     |     |           |
* |-----------------------------------------------------------------------------------------+
* |        |     |     |     |     |     |     |     |     |     |     |     |     |        |
* |-----------------------------------------------------------------------------------------+
* |         |     |     |     |     |     |     |     |     |     |     |     |             |
* |-----------------------------------------------------------------------------------------+
* |            |     |     |     |     |     |     |     |     |     |     |       UP       |
* |-----------------------------------------------------------------------------------------+
* |       |       |       |                                 |       |  LEFT | DOWN  | RIGHT |
* \-----------------------------------------------------------------------------------------/
*/
 const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 [_BASE_LAYER] = KEYMAP( /* Base */
    KC_GESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC,
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
    OSL(_FN1_LAYER), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
    KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSHIFT,
    KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, OSL(_FN1_LAYER), OSL(_FN2_LAYER), KC_RCTRL
),
  /*
  * Layer _FN1_LAYER
  * ,-----------------------------------------------------------------------------------------.
  * |  `  |  F1 |  F2 |  F3 |  F4 |  F5 |  F6 |  F7 |  F8 |  F9 | F10 | F11 | F12 |  DELETE   |
  * |-----------------------------------------------------------------------------------------+
  * | Tab    |  q  | UP  |  e  |  r  |  t  |  y  |  u  |  i  |  o  | PS | HOME | END |   \    |
  * |-----------------------------------------------------------------------------------------+
  * | Esc     |LEFT |DOWN |RIGHT|  f  |  g  |  h  |  j  |  k  |  l  | PGUP|PGDN |    Enter    |
  * |-----------------------------------------------------------------------------------------+
  * | Shift      |V-UP |V-DWN|MUTE |  v  |  b  |  n  |  m  |  ,  |INSRT| DEL |    Shift       |
  * |-----------------------------------------------------------------------------------------+
  * | Ctrl  |  L1   |  Alt  |               space             |  Alt  |  FN1  |  FN2  | Ctrl  |
  * \-----------------------------------------------------------------------------------------/
  *
  */
 [_FN1_LAYER] = KEYMAP( /* Base */
    KC_TILDE, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL,
    KC_TRNS, KC_PGUP, KC_UP, KC_PGDN, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PSCR, KC_INS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP, KC_PGDN, KC_TRNS,
    KC_TRNS, KC_HOME, KC_TRNS, KC_END, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_DEL, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
),
  /*
  * Layer _FN2_LAYER
  * ,-----------------------------------------------------------------------------------------.
  * |  ~  | BT1 | BT2 | BT3 | BT4 |  F5 |  F6 |  F7 |LEDOF|LEDON| F10 | F11 | F12 |    Bksp   |
  * |-----------------------------------------------------------------------------------------+
  * | Tab    |  q  | UP  |  e  |  r  |  t  |  y  |  u  |  i  |  o  | PS | HOME | END |   \    |
  * |-----------------------------------------------------------------------------------------+
  * | Esc     |LEFT |DOWN |RIGHT|  f  |  g  |  h  |  j  |  k  |  l  | PGUP|PGDN |    Enter    |
  * |-----------------------------------------------------------------------------------------+
  * | Shift      |  z  |  x  |  c  |  v  |  b  |  n  |  m  |  ,  |INSRT| DEL |    Shift       |
  * |-----------------------------------------------------------------------------------------+
  * | Ctrl  |  L1   |  Alt  |               space             |  Alt  |  FN1  |  FN2  | Ctrl  |
  * \-----------------------------------------------------------------------------------------/
  *
  */
 [_FN2_LAYER] = KEYMAP( /* Base */
    KC_GRAVE, KC_F13, KC_F14, KC_F15, KC_F16, KC_F17, KC_F18, KC_F19, KC_F20, KC_F21, KC_F22, KC_F23, KC_F24, KC_AP2_BT_UNPAIR,
    KC_AP2_USB, KC_PGUP, KC_UP, KC_PGDN, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_AP_LED_OFF, KC_AP_LED_PREV_PROFILE, KC_AP_LED_NEXT_PROFILE, KC_AP_LED_ON,
    KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_AP_LED_NEXT_INTENSITY, KC_AP_LED_SPEED, KC_TRNS,
    KC_TRNS, KC_HOME, KC_TRNS, KC_END, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_INS, KC_DEL, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
 ),
};
const uint16_t keymaps_size = sizeof(keymaps);

#define UCOM_OK 0xa0
#define UCOM_ERR 0xee
#define UCOM_NDEF 0x0d
#define UCOM_REPORT 0x00
#define UCOM_RETURN_LEN RAW_EPSIZE

#define UCOM_SETLED 0x01
#define UCOM_GETLEDS 0x02
#define UCOM_FLASH 0x03
#define UCOM_LEDSPEED 0x04
#define UCOM_LEDBRIGHT 0x05
#define UCOM_SETSLEDCOL 0x06
#define UCOM_UNSETSLED 0x07
#define UCOM_BTMODE 0x08
#define UCOM_USBMODE 0x09
#define UCOM_BTUNPAIR 0x10

static uint8_t raw_output[RAW_EPSIZE];

void matrix_init_user(void) {

}

void matrix_scan_user(void) {
}

// Code to run after initializing the keyboard
void keyboard_post_init_user(void) {
    annepro2LedEnable();
    annepro2LedSetProfile(7);

    memset(raw_output, 0x00, UCOM_RETURN_LEN*sizeof(uint8_t)); // alloc buffer for usermode config app
}



void raw_hid_receive(uint8_t *data, uint8_t length) {
    uint8_t status = UCOM_OK;
    uint8_t topic = UCOM_NDEF;
     int8_t extra = 0xFE;
    if(length == UCOM_RETURN_LEN) {
        topic = data[0];
        switch (topic)
        {
            case UCOM_SETLED:
                annepro2LedSetProfile(data[1]);
                break;
            case UCOM_GETLEDS:
                extra = annepro2LedGetNumProfiles();
                break;
            case UCOM_FLASH:
                raw_output[0] = UCOM_REPORT;  // NULL report ID. IMPORTANT!
                raw_output[1] = status;
                raw_output[2] = topic;
                raw_hid_send(raw_output,UCOM_RETURN_LEN);
                reset_keyboard();
                break;
            case UCOM_LEDSPEED:
                annepro2LedNextAnimationSpeed();
                break;
            case UCOM_LEDBRIGHT:
                annepro2LedNextIntensity();
                break;
            case UCOM_SETSLEDCOL:
                annepro2LedSetForegroundColor(data[1], data[2], data[3]);
                break;
            case UCOM_UNSETSLED:
                annepro2LedResetForegroundColor();
                break;
            case UCOM_BTMODE:
                if(data[1] > 3 || data[1] < 0)
                {
                    status = UCOM_ERR;
                    break;
                }
                annepro2_ble_broadcast(data[1]);
                break;
            case UCOM_USBMODE:
                annepro2_ble_disconnect();
                break;
            case UCOM_BTUNPAIR:
                annepro2_ble_unpair();
                break;
        default:
            status = UCOM_ERR;
            break;
        }
    }

    raw_output[0] = UCOM_REPORT;  // NULL report ID. IMPORTANT!
    raw_output[1] = status;
    raw_output[2] = topic;
    raw_output[3] = extra;
    raw_output[31] = length;
    raw_hid_send(raw_output,UCOM_RETURN_LEN);
}

layer_state_t layer_state_set_user(layer_state_t layer) {
  switch(get_highest_layer(layer)) {
    case _FN1_LAYER:
      // Set the leds to green
      annepro2LedSetForegroundColor(0x00, 0xFF, 0x00);
      break;
    case _FN2_LAYER:
      // Set the leds to blue
      annepro2LedSetForegroundColor(0x00, 0x00, 0xFF);
      break;
    default:
      // Reset back to the current profile
      annepro2LedResetForegroundColor();
      break;
  }
  return layer;
}

// The function to handle the caps lock logic
bool led_update_user(led_t leds) {
  if (leds.caps_lock) {
    // Set the leds to red
    annepro2LedSetForegroundColor(0xFF, 0x00, 0x00);
  } else {
    // Reset back to the current profile if there is no layer active
    if(!layer_state_is(_FN1_LAYER) && !layer_state_is(_FN2_LAYER)) {
      annepro2LedResetForegroundColor();
    }
  }

  return true;
}
