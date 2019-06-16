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
  QUIZ_COPY = SAFE_RANGE,
  QUIZ_CP_BR,
  QUIZ_REVT,
  QUIZ_FCUS,
  QUIZ_FCUS_BR,
  QUIZ_WIMG,
  QUIZ_ADDT
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT( /* Base */
    QUIZ_WIMG, QUIZ_REVT, QUIZ_COPY, QUIZ_CP_BR, \
    QUIZ_ADDT, QUIZ_REVT, QUIZ_FCUS, QUIZ_FCUS_BR \
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QUIZ_COPY:
      if (record->event.pressed) {
        SEND_STRING(SS_LGUI("c"));
        _delay_ms(50);
        SEND_STRING(SS_LGUI("\t"));
        SEND_STRING("\n");
        _delay_ms(50);
        SEND_STRING(SS_LGUI("v"));
        _delay_ms(100);
        SEND_STRING("\t");
        _delay_ms(50);
        SEND_STRING(SS_LGUI("\t"));
      } else {
      }
      break;
    case QUIZ_CP_BR:
      if (record->event.pressed) {
        SEND_STRING(SS_LGUI("c"));
        _delay_ms(50);
        SEND_STRING(SS_LGUI("\t"));
        SEND_STRING("\n");
        _delay_ms(50);
        SEND_STRING(SS_LGUI("v"));
        _delay_ms(100);
        SEND_STRING("\n");
        _delay_ms(50);
        SEND_STRING(SS_TAP(X_HOME));
        _delay_ms(50);
        SEND_STRING(SS_LGUI("\t"));
      } else {
      }
      break;
    case QUIZ_REVT:
      if (record->event.pressed) {
        SEND_STRING(SS_LGUI("\t"));
        _delay_ms(50);
        SEND_STRING(SS_LGUI("z"));
        _delay_ms(50);
        SEND_STRING(SS_LGUI("\t"));
      } else {
      }
      break;
    case QUIZ_FCUS:
      if (record->event.pressed) {
        SEND_STRING(SS_LGUI("\t"));
        _delay_ms(50);
        SEND_STRING(SS_TAP(X_LEFT));
        _delay_ms(50);
        SEND_STRING(SS_LGUI("\t"));
      } else {
      }
      break;
    case QUIZ_FCUS_BR:
      if (record->event.pressed) {
        SEND_STRING(SS_LGUI("\t"));
        _delay_ms(50);
        SEND_STRING(SS_TAP(X_UP));
        SEND_STRING(SS_TAP(X_RIGHT));
        _delay_ms(50);
        SEND_STRING(SS_TAP(X_RIGHT));
        _delay_ms(50);
        SEND_STRING(SS_TAP(X_RIGHT));
        _delay_ms(50);
        SEND_STRING(SS_TAP(X_RIGHT));
        _delay_ms(50);
        SEND_STRING(SS_LGUI("\t"));
      } else {
      }
      break;
    case QUIZ_WIMG:
      if (record->event.pressed) {
        SEND_STRING(SS_LGUI("\t"));
        _delay_ms(50);
        SEND_STRING(SS_TAP(X_END));
        SEND_STRING("TRUE\n");
        _delay_ms(50);
        SEND_STRING(SS_LGUI("\n"));
        _delay_ms(50);
        SEND_STRING(SS_TAP(X_HOME));
        _delay_ms(50);
        SEND_STRING(SS_LGUI("\t"));
      } else {
      }
      break;
    case QUIZ_ADDT:
      if (record->event.pressed) {
        SEND_STRING(SS_LGUI("\t"));
        _delay_ms(50);
        SEND_STRING(SS_TAP(X_END));
        _delay_ms(50);
        SEND_STRING(SS_TAP(X_LEFT));
        _delay_ms(50);
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
