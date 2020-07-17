/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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

uint16_t copy_paste_timer;

enum layers {
    QWERTY = 0,
    HOTKEYS,
    TEXT,
    SELECT,
    NUMBERS,
    SYMBOLS,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[QWERTY] = LAYOUT(KC_EQL, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_MINS, KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_QUOT, KC_ENT, KC_LSPO, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_NO, MO(5), LALT(KC_A), KC_NO, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSPC, KC_LALT, KC_LCTL, KC_LGUI, MO(2), MO(4), KC_BSPC, KC_SPC, MO(1), KC_PGDN, TG(1)),

[HOTKEYS] = LAYOUT(KC_F6, LGUI(LALT(KC_1)), LGUI(LALT(KC_2)), LCTL(KC_U), SGUI(KC_R), KC_F2, SGUI(KC_K), LCTL(KC_9), LCTL(KC_0), KC_F14, KC_F11, KC_F15, KC_F7, LGUI(LCTL(KC_A)), KC_F10, KC_LBRC, KC_RBRC, KC_F9, KC_F18, LSFT(KC_TAB), KC_TAB, KC_NO, KC_F12, KC_F16, KC_F8, KC_ASTG, KC_NO, KC_LCBR, KC_RCBR, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_F19, KC_F3, KC_F4, KC_NO, KC_F13, KC_F17, KC_F5, KC_NO, KC_LGUI, KC_LCTL, KC_NO, KC_BSPC, KC_SPC, KC_TRNS, KC_NO, KC_NO),

[TEXT] = LAYOUT(LGUI(KC_BSPC), LGUI(KC_Q), LGUI(KC_W), KC_ESC, LGUI(KC_R), LGUI(KC_T), LCTL(KC_Y), LGUI(KC_LEFT), KC_UP, LGUI(KC_RGHT), KC_SCLN, KC_F20, KC_BSPC, MO(3), LGUI(KC_S), LGUI(KC_C), LGUI(KC_V), LGUI(KC_X), KC_DEL, KC_LEFT, KC_DOWN, KC_RGHT, KC_GRV, KC_ENT, KC_F24, LGUI(KC_A), LGUI(KC_D), KC_F1, LGUI(KC_Z), LGUI(KC_Y), KC_NO, KC_NO, KC_NO, KC_NO, KC_BSPC, LGUI(KC_F), SGUI(KC_G), LGUI(KC_G), KC_BSLS, KC_F21, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_BSPC, KC_SPC, KC_LGUI, KC_PGUP, KC_NO),

[SELECT] = LAYOUT(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, SGUI(KC_LEFT), LSFT(KC_UP), SGUI(KC_RGHT), KC_NO, KC_F22, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, LSFT(KC_LEFT), LSFT(KC_DOWN), LSFT(KC_RGHT), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, LALT(LSFT(KC_LEFT)), LALT(LSFT(KC_RIGHT)), KC_NO, KC_F23, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_BSPC, KC_SPC, KC_LGUI, KC_NO, KC_NO),

[NUMBERS] = LAYOUT(KC_NO, LGUI(KC_1), LGUI(KC_2), LGUI(KC_3), LGUI(KC_4), LGUI(KC_5), KC_EQL, KC_7, KC_8, KC_9, KC_TILD, KC_MINS, KC_NO, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_PLUS, KC_4, KC_5, KC_6, KC_COLN, KC_ENT, KC_LSPO, KC_NO, KC_NO, KC_CIRC, KC_AMPR, KC_ASTR, KC_NO, KC_NO, KC_NO, KC_NO, KC_MINS, KC_1, KC_2, KC_3, KC_SLSH, KC_PIPE, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_BSPC, KC_SPC, KC_0, KC_DOT, KC_NO),

[SYMBOLS] = LAYOUT(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_EQL, KC_AMPR, KC_ASTR, KC_PIPE, KC_TILD, KC_MINS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_PLUS, KC_DLR, KC_PERC, KC_CIRC, KC_COLN, KC_ENT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_NO, KC_NO, KC_MINS, KC_EXLM, KC_AT, KC_HASH, KC_SLSH, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_BSPC, KC_SPC, KC_UNDS, KC_NO, KC_NO)

};

LEADER_EXTERNS();

void matrix_scan_user(void) {

    LEADER_DICTIONARY() {
        leading = false;
        leader_end();

        SEQ_ONE_KEY(KC_C) { // Inline Code
            SEND_STRING("`` " SS_TAP(X_LEFT) SS_TAP(X_LEFT));
        }
        SEQ_ONE_KEY(KC_P) { // Invoke Password Manager
            SEND_STRING(SS_LCTRL(SS_LALT("\\")));
        }
        SEQ_ONE_KEY(KC_S) { // Windows screenshot
            SEND_STRING(SS_LGUI("\nS"));
        }
        SEQ_TWO_KEYS(KC_F, KC_P) { // Fusion Projection prefix
            SEND_STRING("[Projection] ");
        }
        SEQ_TWO_KEYS(KC_B, KC_B) { // Basecone invoice description
            SEND_STRING("[Leveranciersnaam] [Factuurnummer]");
        }
        SEQ_TWO_KEYS(KC_E, KC_S) { // Support email splitkb
            SEND_STRING("support@splitkb.com");
        }
        SEQ_TWO_KEYS(KC_E, KC_T) { // Email splitkb
            SEND_STRING("thomas@splitkb.com");
        }
        SEQ_TWO_KEYS(KC_E, KC_P) { // Email personal
            SEND_STRING("mail@thomasbaart.nl");
        }
        SEQ_TWO_KEYS(KC_S, KC_D) { // Splitkb documentation
            SEND_STRING("https://docs.splitkb.com/");
        }
        SEQ_TWO_KEYS(KC_S, KC_V) { // Splitkb VAT number
            SEND_STRING("NL210593349B01");
        }
        SEQ_TWO_KEYS(KC_B, KC_C) { // Discord bongocat
            SEND_STRING(":bongocat:\n");
        }
        SEQ_TWO_KEYS(KC_C, KC_B) { // Discord code block
            SEND_STRING("```c" SS_LSFT("\n\n") "``` " SS_TAP(X_UP));
        }
        SEQ_TWO_KEYS(KC_Y, KC_S) { // Greeting
            SEND_STRING("Yours sincerely,\n\nThomas Baart");
        }
        SEQ_THREE_KEYS(KC_M, KC_V, KC_G) { // Greeting
            SEND_STRING("Met vriendelijke groet,\n\nThomas Baart");
        }
    }
}

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	return OLED_ROTATION_180;
}

static void render_kyria_logo(void) {
    static const char PROGMEM kyria_logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192,224,240,112,120, 56, 60, 28, 30, 14, 14, 14,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 14, 14, 14, 30, 28, 60, 56,120,112,240,224,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,192,224,240,124, 62, 31, 15,  7,  3,  1,128,192,224,240,120, 56, 60, 28, 30, 14, 14,  7,  7,135,231,127, 31,255,255, 31,127,231,135,  7,  7, 14, 14, 30, 28, 60, 56,120,240,224,192,128,  1,  3,  7, 15, 31, 62,124,240,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,240,252,255, 31,  7,  1,  0,  0,192,240,252,254,255,247,243,177,176, 48, 48, 48, 48, 48, 48, 48,120,254,135,  1,  0,  0,255,255,  0,  0,  1,135,254,120, 48, 48, 48, 48, 48, 48, 48,176,177,243,247,255,254,252,240,192,  0,  0,  1,  7, 31,255,252,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,255,255,255,  0,  0,  0,  0,  0,254,255,255,  1,  1,  7, 30,120,225,129,131,131,134,134,140,140,152,152,177,183,254,248,224,255,255,224,248,254,183,177,152,152,140,140,134,134,131,131,129,225,120, 30,  7,  1,  1,255,255,254,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0,255,255,  0,  0,192,192, 48, 48,  0,  0,240,240,  0,  0,  0,  0,  0,  0,240,240,  0,  0,240,240,192,192, 48, 48, 48, 48,192,192,  0,  0, 48, 48,243,243,  0,  0,  0,  0,  0,  0, 48, 48, 48, 48, 48, 48,192,192,  0,  0,  0,  0,  0,
        0,  0,  0,255,255,255,  0,  0,  0,  0,  0,127,255,255,128,128,224,120, 30,135,129,193,193, 97, 97, 49, 49, 25, 25,141,237,127, 31,  7,255,255,  7, 31,127,237,141, 25, 25, 49, 49, 97, 97,193,193,129,135, 30,120,224,128,128,255,255,127,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0, 63, 63,  3,  3, 12, 12, 48, 48,  0,  0,  0,  0, 51, 51, 51, 51, 51, 51, 15, 15,  0,  0, 63, 63,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48, 48, 63, 63, 48, 48,  0,  0, 12, 12, 51, 51, 51, 51, 51, 51, 63, 63,  0,  0,  0,  0,  0,
        0,  0,  0,  0, 15, 63,255,248,224,128,  0,  0,  3, 15, 63,127,255,239,207,141, 13, 12, 12, 12, 12, 12, 12, 12, 30,127,225,128,  0,  0,255,255,  0,  0,128,225,127, 30, 12, 12, 12, 12, 12, 12, 12, 13,141,207,239,255,127, 63, 15,  3,  0,  0,128,224,248,255, 63, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  3,  7, 15, 62,124,248,240,224,192,128,  1,  3,  7, 15, 30, 28, 60, 56,120,112,112,224,224,225,231,254,248,255,255,248,254,231,225,224,224,112,112,120, 56, 60, 28, 30, 15,  7,  3,  1,128,192,224,240,248,124, 62, 15,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  7, 15, 14, 30, 28, 60, 56,120,112,112,112,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,112,112,112,120, 56, 60, 28, 30, 14, 15,  7,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
    };
    oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
}

static void render_qmk_logo(void) {
  static const char PROGMEM qmk_logo[] = {
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};

  oled_write_P(qmk_logo, false);
}

static void render_status(void) {
    // QMK Logo and version information
    render_qmk_logo();
    oled_write_P(PSTR("       Kyria rev1.0\n\n"), false);

    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case QWERTY:
            oled_write_P(PSTR("QWERTY\n"), false);
            break;
        case HOTKEYS:
            oled_write_P(PSTR("HOTKEYS\n"), false);
            break;
        case TEXT:
            oled_write_P(PSTR("TEXT\n"), false);
            break;
        case SELECT:
            oled_write_P(PSTR("SELECT\n"), false);
            break;
        case NUMBERS:
            oled_write_P(PSTR("NUMBERS\n"), false);
            break;
        case SYMBOLS:
            oled_write_P(PSTR("SYMBOLS\n"), false);
            break;
        default:
            oled_write_P(PSTR("Undefined\n"), false);
    }

}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status(); // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_kyria_logo();
    }
}
#endif

void encoder_update_user(uint8_t index, bool clockwise) {
    if (IS_LAYER_ON(HOTKEYS)) {
        if (clockwise) {
            tap_code(KC_VOLD);
        } else {
            tap_code(KC_VOLU);
        }
    } else if (IS_LAYER_ON(TEXT)) {
        if (clockwise) {
            tap_code(KC_MS_WH_LEFT);
        } else {
            tap_code(KC_MS_WH_RIGHT);
        }
    } else if (IS_LAYER_ON(NUMBERS)) {
        if (clockwise) {
            register_code(KC_LGUI);
            tap_code(KC_MINS);
            unregister_code(KC_LGUI);
        } else {
            register_code(KC_LGUI);
            tap_code(KC_EQL);
            unregister_code(KC_LGUI);
        }
    } else {
        if (clockwise) {
            tap_code(KC_MS_WH_UP);
        } else {
            tap_code(KC_MS_WH_DOWN);
        }
    }
}
