/* Copyright 2019 wktk
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

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  QMKBEST = SAFE_RANGE,
  QMKURL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT( /* Base */
    LCMD(KC_TAB), LCMD(KC_C), QMKBEST, QMKURL, \
    KC_ENT, LCMD(KC_V), KC_TAB, KC_HOME \
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QMKBEST:
      if (record->event.pressed) {
        SEND_STRING(SS_LGUI("c\t"));
        SEND_STRING("\n");
        SEND_STRING(SS_LGUI("v"));
        SEND_STRING("\t");
        SEND_STRING(SS_LGUI("\t"));
      } else {
      }
      break;
    case QMKURL:
      if (record->event.pressed) {
        SEND_STRING(SS_LGUI("c\t"));
        SEND_STRING("\n");
        SEND_STRING(SS_LGUI("v"));
        SEND_STRING("\n");
        SEND_STRING(SS_LGUI("\t"));
      } else {
      }
      break;
  }
  return true;
}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}
