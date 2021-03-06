#include QMK_KEYBOARD_H
#include "pro_micro.h"

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};

bool led_status = false;
uint16_t time = 0;

// Fillers to make layering more clear
#define _______ KC_TRNS
#define __ KC_TRNS
#define KC_ KC_TRNS
#define XXXXXXX KC_NO
#define KC_EISU LALT(KC_GRV)
#define KC_XLWR LOWER
#define KC_XRIS TG(_RAISE)
#define KC_VLUP KC__VOLUP
#define KC_VLDN KC__VOLDOWN
#define KC_VLMT KC__MUTE

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_kc(
//,-----,-----,-----,-----,-----,-----,-----,     ,-----,-----,-----,-----,-----,-----,-----,
    TAB ,  Q  ,  W  ,  E  ,  R  ,  T  , GRV ,       EQL ,  Y  ,  U  ,  I  ,  O  ,  P  , MINS,
//|-----|-----|-----|-----|-----|-----|-----|     |-----|-----|-----|-----|-----|-----|-----|
    LCTL,  A  ,  S  ,  D  ,  F  ,  G  , LBRC,       RBRC,  H  ,  J  ,  K  ,  L  , SCLN, QUOT,
//|-----|-----|-----|-----|-----|-----|-----|     |-----|-----|-----|-----|-----|-----|-----|
    LSFT,  Z  ,  X  ,  C  ,  V  ,  B  , LALT,           ,  N  ,  M  , COMM, DOT , SLSH, RSFT,
//|-----|-----|-----|-----|-----|-----|-----|     |-----|-----|-----|-----|-----|-----|-----|
    XLWR, XRIS,     ,LANG2,/****/ SPC , LGUI,  ,  , BSPC, ENT ,/****/LANG1,     , XRIS, XLWR
//,-----,-----,-----,-----,-----,-----,-----,     ,-----,-----,-----,-----,-----,-----,-----,
  ),

  [_LOWER] = LAYOUT_kc(
//,-----,-----,-----,-----,-----,-----,-----,     ,-----,-----,-----,-----,-----,-----,-----,
    ESC ,  1  ,  2  ,  3  ,  4  ,  5  ,     ,           ,  6  ,  7  ,  8  ,  9  ,  0  , MINS,
//|-----|-----|-----|-----|-----|-----|-----|     |-----|-----|-----|-----|-----|-----|-----|
        , F1  , F2  , F3  , F4  , F5  ,     ,           , LEFT, DOWN, UP  , RGHT, HOME, BSLS,
//|-----|-----|-----|-----|-----|-----|-----|     |-----|-----|-----|-----|-----|-----|-----|
    LSFT, F6  , F7  , F8  , F9  , F10 , LALT,           , PGDN, PGUP, COMM, DOT , END , RSFT,
//|-----|-----|-----|-----|-----|-----|-----|     |-----|-----|-----|-----|-----|-----|-----|
    XLWR,     ,     ,     ,/****/     , LGUI,  ,  , BSPC, ENT ,/****/     ,     ,     , XLWR
//,-----,-----,-----,-----,-----,-----,-----,     ,-----,-----,-----,-----,-----,-----,-----,
  ),

  [_RAISE] = LAYOUT_kc(
//,-----,-----,-----,-----,-----,-----,-----,     ,-----,-----,-----,-----,-----,-----,-----,
    GRV , EXLM, AT  , HASH, DLR , PERC, UNDS,       PLUS,  7  ,  8  ,  9  ,     ,     ,     ,
//|-----|-----|-----|-----|-----|-----|-----|     |-----|-----|-----|-----|-----|-----|-----|
    TILD, VLDN, VLUP, VLMT, F4  , F5  , LCBR,       MINS,  4  ,  5  ,  6  ,     ,     ,     ,
//|-----|-----|-----|-----|-----|-----|-----|     |-----|-----|-----|-----|-----|-----|-----|
    LSFT, BRMD, BRMU, F8  , F9  , F10 , SPC ,       TRNS,  1  ,  2  ,  3  , ENT ,     ,     ,
//|-----|-----|-----|-----|-----|-----|-----|     |-----|-----|-----|-----|-----|-----|-----|
    LCTL, F11 , F12 , EISU,/****/ XLWR, SPC ,  ,  , BSPC,  0  ,/****/ COMM, DOT ,     ,    //
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
    if (led_status) {
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
