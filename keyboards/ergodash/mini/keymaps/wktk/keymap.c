#include QMK_KEYBOARD_H
#include "pro_micro.h"

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _CUSTOM 3
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  CUSTOM,
  ADJUST,
};

bool led_status = false;
uint16_t time = 0;
bool in_custom_layer = false;

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define EISU LALT(KC_GRV)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,----------------------------------------------------------------------------------------------------------------------.
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |   `  |                    |   =  |   Y  |   U  |   I  |   O  |   P  |  -   |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * | Ctrl |   A  |   S  |   D  |   F  |   G  |   [  |                    |   ]  |   H  |   J  |   K  |   L  |   ;  |  "   |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  | Esc  |                    | Enter|   N  |   M  |   ,  |   .  |   /  | Shift|
   * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------------|
   * | LOWER|      |  ALt |      |||||||| Space| GUI  |      ||||||||      | Bksp | Enter||||||||      |      |      | LOWER|
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_QWERTY] = LAYOUT( \
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_GRV,                         KC_EQL , KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS, \
    KC_LCTL,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_LBRC,                        KC_RBRC, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_ESC ,                        KC_ENT , KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
    LOWER, _______, KC_LALT, _______,          KC_SPC,    KC_LGUI, _______,        _______,KC_BSPC,KC_ENT,            _______, _______, _______, LOWER  \
  ),

  /* Lower
   * ,----------------------------------------------------------------------------------------------------------------------.
   * |   `  |   !  |   @  |   #  |   $  |   %  |   _  |                    |   +  |   ^  |   &  |   *  |   (  |   )  |  |   |
   * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
   * |   ~  |   1  |   2  |   3  |   4  |   5  |   {  |                    |   }  | Left | Down |  Up  | Right|   :  |  "   |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * | Shift|   6  |   7  |   8  |   9  |   0  | Space|                    | Enter|   N  |   M  |   <  |   >  |   ?  | Shift|
   * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------------|
   * | Ctrl |  GUI |  ALt | EISU |||||||| Lower| Space|Delete|||||||| Bksp | Enter| Raise|||||||| Home |PageDn|PageUp|  End |
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_LOWER] = LAYOUT(
    CUSTOM,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______,                        _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS, \
    _______, _______, _______, _______, _______, _______, _______,                        _______, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, _______, _______, \
    KC_LSFT, _______, _______, _______, _______, _______, _______,                        _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, KC_RSFT, \
    LOWER,   _______, _______, _______,          _______, _______, _______,      _______, _______,          _______, _______, _______, _______, LOWER \
  ),

  /* Raise
  * ,----------------------------------------------------------------------------------------------------------------------.
  * |   `  |   !  |   @  |   #  |   $  |   %  |   _  |                    |   +  |   ^  |   &  |   *  |   (  |   )  |  |   |
  * |------+------+------+------+------+------+------+--------------------+------+------+------+------+------+------+------|
  * |   ~  |   F1 |   F2 |   F3 |   F4 |   F5 |   {  |                    |   }  | Left | Down |  Up  | Right|   :  |  "   |
  * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
  * | Shift|   F6 |   F7 |   F8 |   F9 |  F10 | Space|                    | Enter|   N  |   M  |   <  |   >  |   ?  | Shift|
  * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------------|
  * | Ctrl |  F11 |  F12 | EISU |||||||| Lower| Space|Delete|||||||| Bksp | Enter| Raise|||||||| Home |PageDn|PageUp|  End |
  * ,----------------------------------------------------------------------------------------------------------------------.
  */
  [_RAISE] = LAYOUT(
    KC_GRV , KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_UNDS,                        KC_PLUS, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE, \
    KC_TILD, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_LCBR,                        KC_RCBR, KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_COLN, KC_DQT , \
    KC_LSFT, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_SPC ,                        KC_ENT , KC_N,    KC_M,    KC_LT,   KC_GT,   KC_QUES, KC_RSFT, \
    KC_LCTL, KC_F11 , KC_F12,  EISU,             LOWER,   KC_SPC , KC_DEL,        KC_BSPC,KC_ENT , RAISE,            KC_HOME, KC_PGDN, KC_PGUP, KC_END   \
    ),

  [_CUSTOM] = LAYOUT(
    KC_TAB,  KC_Q,    _______, _______, _______, _______, _______,                        _______, _______, _______, _______, _______, _______, _______, \
    KC_LCTL, KC_LEFT, _______, _______, KC_RGHT, _______, _______,                        _______, _______, _______, _______, _______, _______, _______, \
    KC_LSFT, _______, _______, _______, _______, _______, _______,                        _______, _______, _______, _______, _______, _______, _______, \
    CUSTOM,  _______, _______, _______,          KC_SPC,  KC_LGUI, _______,      _______, _______, _______,          _______, _______, _______, _______ \
  ),

  /* Adjust
   * ,----------------------------------------------------------------------------------------------------------------------.
   * |      | Reset|RGB ON|  MODE|  HUE-|  HUE+|      |                    |      |  SAT-|  SAT+|  VAL-|  VAL+|      |      |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |                    |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+---------------------------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |                    |      |      |      |      |      |      |      |
   * |-------------+------+------+------+------+------+------+------+------+------+------+------+------+------+-------------|
   * |      |      |      |      ||||||||      |      |      ||||||||      |      |      ||||||||      |      |      |      |
   * ,----------------------------------------------------------------------------------------------------------------------.
   */
  [_ADJUST] = LAYOUT(
    _______, RESET  , RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI,_______,                       _______, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, _______, _______, \
    _______, _______, BL_TOGG, BL_BRTG, BL_INC , BL_DEC ,_______,                       _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______,_______,                       _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______,          _______,_______,_______,       _______,_______, _______,          _______, _______, _______, _______  \
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed && record->event.time - time > 20) {
    if (led_status || in_custom_layer) {
      RXLED0;
      TXLED0;
    } else {
      RXLED1;
      TXLED1;
    }

    time = record->event.time;
    led_status = !led_status;
  }

  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case CUSTOM:
      if (record->event.pressed) {
        if (in_custom_layer) {
          layer_off(_CUSTOM);
          in_custom_layer = false;
        } else {
          layer_on(_CUSTOM);
          in_custom_layer = true;
        }
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}
