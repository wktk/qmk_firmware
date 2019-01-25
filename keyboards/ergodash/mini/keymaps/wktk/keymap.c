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
#define __ KC_TRNS
#define KC_ KC_TRNS
#define XXXXXXX KC_NO
#define KC_EISU LALT(KC_GRV)
#define KC_XLWR LOWER
#define KC_XCST CUSTOM
#define KC_XRIS RAISE

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_kc(
//,-----,-----,-----,-----,-----,-----,-----,     ,-----,-----,-----,-----,-----,-----,-----,
    TAB ,  Q  ,  W  ,  E  ,  R  ,  T  , GRV ,       EQL ,  Y  ,  U  ,  I  ,  O  ,  P  , MINS,
//|-----|-----|-----|-----|-----|-----|-----|     |-----|-----|-----|-----|-----|-----|-----|
    LCTL,  A  ,  S  ,  D  ,  F  ,  G  , LBRC,       RBRC,  H  ,  J  ,  K  ,  L  , SCLN, QUOT,
//|-----|-----|-----|-----|-----|-----|-----|     |-----|-----|-----|-----|-----|-----|-----|
    LSFT,  Z  ,  X  ,  C  ,  V  ,  B  , LALT,           ,  N  ,  M  , COMM, DOT , SLSH, RSFT,
//|-----|-----|-----|-----|-----|-----|-----|     |-----|-----|-----|-----|-----|-----|-----|
    XLWR,     ,     ,     ,/****/ SPC , LGUI,  ,  , BSPC, ENT ,/****/     ,     ,     , XLWR
//,-----,-----,-----,-----,-----,-----,-----,     ,-----,-----,-----,-----,-----,-----,-----,
  ),

  [_LOWER] = LAYOUT_kc(
//,-----,-----,-----,-----,-----,-----,-----,     ,-----,-----,-----,-----,-----,-----,-----,
    ESC ,  1  ,  2  ,  3  ,  4  ,  5  ,     ,           ,  6  ,  7  ,  8  ,  9  ,  0  , BSLS,
//|-----|-----|-----|-----|-----|-----|-----|     |-----|-----|-----|-----|-----|-----|-----|
        ,     ,     ,     ,     ,     ,     ,           , LEFT, DOWN, UP  , RGHT, HOME,     ,
//|-----|-----|-----|-----|-----|-----|-----|     |-----|-----|-----|-----|-----|-----|-----|
    LSFT,     ,     ,     ,     ,     , LALT,           , PGDN, PGUP, COMM, DOT , END , RSFT,
//|-----|-----|-----|-----|-----|-----|-----|     |-----|-----|-----|-----|-----|-----|-----|
    XLWR,     ,     ,     ,/****/ XCST, LGUI,  ,  ,     ,     ,/****/     ,     ,     , XLWR
//,-----,-----,-----,-----,-----,-----,-----,     ,-----,-----,-----,-----,-----,-----,-----,
  ),

  [_RAISE] = LAYOUT_kc(
//,-----,-----,-----,-----,-----,-----,-----,     ,-----,-----,-----,-----,-----,-----,-----,
    GRV , EXLM, AT  , HASH, DLR , PERC, UNDS,       PLUS, CIRC, AMPR, ASTR, LPRN, RPRN, PIPE,
//|-----|-----|-----|-----|-----|-----|-----|     |-----|-----|-----|-----|-----|-----|-----|
    TILD, F1  , F2  , F3  , F4  , F5  , LCBR,       RCBR, LEFT, DOWN, UP  , RGHT, COLN, DQT ,
//|-----|-----|-----|-----|-----|-----|-----|     |-----|-----|-----|-----|-----|-----|-----|
    LSFT, F6  , F7  , F8  , F9  , F10 , SPC ,       ENT ,  N  ,  M  , LT  , GT  , QUES, RSFT,
//|-----|-----|-----|-----|-----|-----|-----|     |-----|-----|-----|-----|-----|-----|-----|
    LCTL, F11 , F12 , EISU,/****/ XLWR, SPC ,  ,  , ENT , XRIS,/****/ HOME, PGDN, PGUP, END
//,-----,-----,-----,-----,-----,-----,-----,     ,-----,-----,-----,-----,-----,-----,-----,
    ),

  [_CUSTOM] = LAYOUT_kc(
//,-----,-----,-----,-----,-----,-----,-----,     ,-----,-----,-----,-----,-----,-----,-----,
    TAB ,  Q  ,     ,     ,     ,     ,     ,           ,     ,     ,     ,     ,     ,     ,
//|-----|-----|-----|-----|-----|-----|-----|     |-----|-----|-----|-----|-----|-----|-----|
    LCTL, LEFT,     ,     , RGHT,     ,     ,           ,     ,     ,     ,     ,     ,     ,
//|-----|-----|-----|-----|-----|-----|-----|     |-----|-----|-----|-----|-----|-----|-----|
    LSFT,     ,     ,     ,     ,     ,     ,           ,     ,     ,     ,     ,     ,     ,
//|-----|-----|-----|-----|-----|-----|-----|     |-----|-----|-----|-----|-----|-----|-----|
    XCST,     ,     ,     ,/****/ SPC , LGUI,  ,  ,     ,     ,/****/     ,     ,     ,
//,-----,-----,-----,-----,-----,-----,-----,     ,-----,-----,-----,-----,-----,-----,-----,
  ),

  [_ADJUST] = LAYOUT(
//,--------,--------,--------,--------,--------,--------,--------,--------,--------,--------,--------,--------,--------,--------,--------,
    _______, RESET  , RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI, _______,          _______, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, _______, _______,
//|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|
    _______, _______, BL_TOGG, BL_BRTG, BL_INC , BL_DEC , _______,          _______, _______, _______, _______, _______, _______, _______,
//|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|
    _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
//|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|
    _______, _______, _______, _______,          _______, _______, __,  __, _______, _______,          _______, _______, _______, _______
//,--------,--------,--------,--------,--------,--------,--------,--------,--------,--------,--------,--------,--------,--------,--------,
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
