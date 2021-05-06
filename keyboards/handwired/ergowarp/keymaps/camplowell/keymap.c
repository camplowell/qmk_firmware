/* Copyright 2021 Lowell Camp
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
//#include process_tap_dance.h

extern keymap_config_t keymap_config;

#define DEBOUNCE_CAPS_DELAY 100

//Tap dance definitions
typedef struct {
    uint16_t keycode;
} td_keycode_t;

#define ACTION_TAP_DANCE_CTR(KC) { .fn = {NULL, tap_dance_ctrl_finished, tap_dance_ctrl_reset}, .user_data = (void *)&((td_keycode_t){KC}), }

void tap_dance_ctrl_finished(qk_tap_dance_state_t *state, void *user_data);
void tap_dance_ctrl_reset(qk_tap_dance_state_t *state, void *user_data);
void tap_dance_shft_finished(qk_tap_dance_state_t *state, void *user_data);
void tap_dance_shft_reset(qk_tap_dance_state_t *state, void *user_data);

// Custom keycodes

enum td_keycodes {
    // Tap Dance keycodes; prefixed by TD_
    _A, // A when tapped, and ctrl/cmd+A when held
    _B,
    _C,
    _D,
    _E,
    _F,
    _G,
    _H,
    _I,
    _J,
    _K,
    _L,
    _M,
    _N,
    _O,
    _P,
    _Q,
    _R,
    _S,
    _T,
    _U,
    _V,
    _W,
    _X,
    _Y,
    _Z,
    _SFT, // Multi-shift: acts as shift, oneshot and capslock
};

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _CMK,
    _QTY,
    _WASD,

    _OS1,
    _NUM,
    _NAV,

    _FN
};

// -------------------------------------- KEYMAP DEFINITION ---------------------------------------

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
        ┌───────┬───────┬───────┬───────┬───────┐       ┌───────┬───────┬───────┬───────┬───────┐
        │  Q(⌃) │  W(⌃) │  F(⌃) │  P(⌃) │  B(⌃) │       │  J(⌃) │  L(⌃) │  U(⌃) │  Y(⌃) │   ⌫   │
        ├───────┼───────┼───────┼───────┼───────┤       ├───────┼───────┼───────┼───────┼───────┤
        │  A(⌃) │  R(⌃) │  S(⌃) │  T(⌃) │  G(⌃) │       │  M(⌃) │  N(⌃) │  E(⌃) │  I(⌃) │  O(⌃) │
        ├───────┼───────┼───────┼───────┼───────┤       ├───────┼───────┼───────┼───────┼───────┤
        │  Z(⌃) │  X(⌃) │  C(⌃) │  D(⌃) │  V(⌃) │       │  K(⌃) │  H(⌃) │   ,   │   .   │   /   │
        └───────┴───────┴───┬───┴───┬───┴───────┘       └───────┴───┬───┴───┬───┴───────┴───────┘
                            │   ↹   │            COLEMAK            │  OS1  │
                            ├───────┼───────┐               ┌───────┼───────┤
                            │   ⇪   │   ⏎   │     _CMK      │  ALT  │   ␣   │
                            └───────┴───────┘               └───────┴───────┘
    */
    [_CMK] = LAYOUT(
        TD(_Q),   TD(_W),   TD(_F),   TD(_P),   TD(_B),       TD(_J),   TD(_L),   TD(_U),   TD(_Y),   KC_BSPC,
        TD(_A),   TD(_R),   TD(_S),   TD(_T),   TD(_G),       TD(_M),   TD(_N),   TD(_E),   TD(_I),   TD(_O),
        TD(_Z),   TD(_X),   TD(_C),   TD(_D),   TD(_V),       TD(_K),   TD(_H),   KC_COMM,  KC_DOT,   KC_SLSH,
                        KC_TAB,   TD(_SFT), KC_ENT,         KC_LALT,   KC_SPC,  OSL(_OS1)
     ),



    /*
        ┌───────┬───────┬───────┬───────┬───────┐       ┌───────┬───────┬───────┬───────┬───────┐
        │  Q(⌃) │  W(⌃) │  E(⌃) │  R(⌃) │  T(⌃) │       │  J(⌃) │  L(⌃) │  U(⌃) │  Y(⌃) │  P(⌃) │
        ├───────┼───────┼───────┼───────┼───────┤       ├───────┼───────┼───────┼───────┼───────┤
        │  A(⌃) │  S(⌃) │  D(⌃) │  F(⌃) │  G(⌃) │       │  H(⌃) │  J(⌃) │  K(⌃) │  L(⌃) │   ;   │
        ├───────┼───────┼───────┼───────┼───────┤       ├───────┼───────┼───────┼───────┼───────┤
        │  Z(⌃) │  X(⌃) │  C(⌃) │  V(⌃) │  B(⌃) │       │  N(⌃) │  M(⌃) │   ,   │   .   │   /   │
        └───────┴───────┴───┬───┴───┬───┴───────┘       └───────┴───┬───┴───┬───┴───────┴───────┘
                            │   ↹   │             QWERTY            │  OS1  │
                            ├───────┼───────┐               ┌───────┼───────┤
                            │   ⇪   │   ⏎   │     _QTY      │  ALT  │   ␣   │
                            └───────┴───────┘               └───────┴───────┘
    */
    [_QTY] = LAYOUT(
        TD(_Q),   TD(_W),   TD(_E),   TD(_R),   TD(_T),       TD(_Y),   TD(_U),   TD(_I),   TD(_O),   TD(_P),
        TD(_A),   TD(_S),   TD(_D),   TD(_F),   TD(_G),       TD(_H),   TD(_J),   TD(_K),   TD(_L),   KC_SCLN,
        TD(_Z),   TD(_X),   TD(_C),   TD(_V),   TD(_B),       TD(_N),   TD(_M),   KC_COMM,  KC_DOT,   KC_SLSH,
                        KC_TAB,   TD(_SFT), KC_ENT,         KC_LALT,   KC_SPC,  OSL(_OS1)
     ),



    /*
        ┌───────┬───────┬───────┬───────┬───────┐       ┌───────┬───────┬───────┬───────┬───────┐
        │  Esc  │   >   │   }   │   )   │   ]   │       │   @   │   #   │   $   │   %   │   ⌫   │
        ├───────┼───────┼───────┼───────┼───────┤       ├───────┼───────┼───────┼───────┼───────┤
        │   `   │   <   │   {   │   (   │   [   │       │   =   │   '   │   !   │   ?   │   ^   │
        ├───────┼───────┼───────┼───────┼───────┤       ├───────┼───────┼───────┼───────┼───────┤
        │   ~   │   *   │   -   │   +   │   ∅   │       │  NAV  │   "   │   \   │   :   │   ▽   │
        └───────┴───────┴───┬───┴───┬───┴───────┘       └───────┴───┬───┴───┬───┴───────┴───────┘
                            │   ▽   │            ONE-SHOT           │  NUM  │
                            ├───────┼───────┐               ┌───────┼───────┤
                            │   ▽   │   ▽   │     _OS1      │  ~L0  │   ▽   │
                            └───────┴───────┘               └───────┴───────┘
    */
    [_OS1] = LAYOUT(
        KC_ESC,   KC_RABK,  KC_RCBR,  KC_RPRN,  KC_RBRC,      KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,  _______,
        KC_GRV,   KC_LABK,  KC_LCBR,  KC_LPRN,  KC_LBRC,      KC_EQL,   KC_QUOT,  KC_EXLM,  KC_QUES,  KC_CIRC,
        KC_TILD,  KC_ASTR,  KC_MINS,  KC_PLUS,  KC_NO,        TO(_NAV), KC_DQUO,  KC_BSLS,  KC_COLN,   _______,
                KC_TRNS,   KC_TRNS,   KC_ENT,         KC_LALT,   KC_TRNS,  TO(_NUM)
     ),



     /*
        ┌───────┬───────┬───────┬───────┬───────┐       ┌───────┬───────┬───────┬───────┬───────┐
        │  Esc  │   ^   │   (   │   )   │   %   │       │   z   │   7   │   8   │   9   │   ⌫   │
        ├───────┼───────┼───────┼───────┼───────┤       ├───────┼───────┼───────┼───────┼───────┤
        │   <   │   /   │   ,   │   .   │   =   │       │   x   │   4   │   5   │   6   │   #   │
        ├───────┼───────┼───────┼───────┼───────┤       ├───────┼───────┼───────┼───────┼───────┤
        │   >   │   *   │   -   │   +   │   ∅   │       │   y   │   1   │   2   │   3   │   $   │
        └───────┴───────┴───┬───┴───┬───┴───────┘       └───────┴───┬───┴───┬───┴───────┴───────┘
                            │  ~Fn  │             NUMBER            │   ∅   │
                            ├───────┼───────┐               ┌───────┼───────┤
                            │   ␣   │   ▽   │     _NUM      │  ~L0  │   0   │
                            └───────┴───────┘               └───────┴───────┘
    */
    [_NUM] = LAYOUT(
        KC_ESC,   KC_CIRC,  KC_LPRN,  KC_RPRN,  KC_PERC,      KC_Z,     KC_7,     KC_8,     KC_9,     _______,
        KC_LT,    KC_SLSH,  KC_LCBR,  KC_LPRN,  KC_LBRC,      KC_X,     KC_4,     KC_5,     KC_6,     KC_HASH,
        KC_GT,    KC_ASTR,  KC_MINS,  KC_PLUS,  KC_NO,        KC_Y,     KC_1,     KC_2,     KC_3,     KC_DLR,
                        TO(_FN),  KC_SPC,   _______,              TO(0),    KC_0,     KC_NO
     ),



     /*
        ┌───────┬───────┬───────┬───────┬───────┐       ┌───────┬───────┬───────┬───────┬───────┐
        │  Esc  │   ⌫   │   ↑   │   ⏎   │   ∅   │       │  mute │  ◁◁◁  │   ▶︎   │  ▷▷▷  │   ⏏︎   │
        ├───────┼───────┼───────┼───────┼───────┤       ├───────┼───────┼───────┼───────┼───────┤
        │  ⌃Y   │   ←   │   ↓   │   →   │   ↹   │       │  vol+ │  MS1  │  MS3  │  MS2  │   ∅   │
        ├───────┼───────┼───────┼───────┼───────┤       ├───────┼───────┼───────┼───────┼───────┤
        │  ⌃Z   │  ⌃X   │  ⌃C   │  ⌃V   │   ∅   │       │  vol- │  MS4  │  MS5  │  MS6  │   ∅   │
        └───────┴───────┴───┬───┴───┬───┴───────┘       └───────┴───┬───┴───┬───┴───────┴───────┘
                            │  ~Fn  │           NAVIGATION          │   ∅   │
                            ├───────┼───────┐               ┌───────┼───────┤
                            │   ␣   │   ▽   │     _NAV      │  ~L0  │   ▽   │
                            └───────┴───────┘               └───────┴───────┘
    */
    [_NAV] = LAYOUT(
        KC_ESC,   KC_CIRC,  KC_LPRN,  KC_RPRN,  KC_PERC,      KC_MUTE,  KC_MPRV,  KC_8,     KC_MNXT,  KC_EJCT,
        KC_LT,    KC_SLSH,  KC_LCBR,  KC_LPRN,  KC_LBRC,      KC_VOLU,  KC_4,     KC_5,     KC_6,     KC_NO,
        KC_GT,    KC_ASTR,  KC_MINS,  KC_PLUS,  KC_NO,        KC_VOLD,  KC_1,     KC_2,     KC_3,     KC_NO,
                        TO(_FN),  KC_SPC,   _______,              TO(0),    KC_0,     KC_NO
     ),



     /*
        ┌───────┬───────┬───────┬───────┬───────┐       ┌───────┬───────┬───────┬───────┬───────┐
        │ RESET │  LED0 │  LED- │  LED+ │  PTN  │       │ SNAP+ │   F7  │   F8  │   F9  │  F10  │
        ├───────┼───────┼───────┼───────┼───────┤       ├───────┼───────┼───────┼───────┼───────┤
        │  USB  │   BT  │  WIN  │  MAC  │  JOY  │       │ SNAP- │   F4  │   F5  │   F6  │  F11  │
        ├───────┼───────┼───────┼───────┼───────┤       ├───────┼───────┼───────┼───────┼───────┤
        │  BLDR │  ANLG │  WASD │  CMK  │  QTY  │       │ SNAP0 │   F1  │   F2  │   F3  │  F12  │
        └───────┴───────┴───┬───┴───┬───┴───────┘       └───────┴───┬───┴───┬───┴───────┴───────┘
                            │   ⇧   │            FUNCTION           │  GUI  │
                            ├───────┼───────┐               ┌───────┼───────┤
                            │   ⌃   │   ▽   │      _FN      │  ~L0  │  ALT  │
                            └───────┴───────┘               └───────┴───────┘
    */
    [_FN] = LAYOUT(
        RESET,    KC_CIRC,  KC_LPRN,  _______,  _______,      _______,  KC_F7,    KC_F8,    KC_F9,    KC_F10,
        _______,  _______,  CG_NORM,  CG_SWAP,  _______,      _______,  KC_F4,    KC_F5,    KC_F6,    KC_F11,
        _______,  _______,  _______,  _______,  _______,      _______,  KC_F1,    KC_F2,    KC_F3,    KC_F12,
                        KC_LSFT,  KC_LCTRL,   _______,           TO(0),    KC_0,     KC_NO
     ),
};


// -------------------------------------- Tap dance: ctrl letters ---------------------------------

void tap_dance_ctrl_finished(qk_tap_dance_state_t *state, void *user_data) {
    uint16_t keycode = ((td_keycode_t*)user_data)->keycode;

    // If tapped or interrupted
    if (!state->pressed || state->interrupted) {
        register_code(keycode);
        return;
    }

    // Held and not iterrupted
    switch (state->count) {
        case 1:
            register_code(LCTL(keycode));
            break;
    }
}

void tap_dance_ctrl_reset(qk_tap_dance_state_t *state, void *user_data) {
    uint16_t keycode = ((td_keycode_t*)user_data)->keycode;

    // If tapped or interrupted
    if (!state->pressed || state->interrupted) {
        unregister_code(keycode);
        return;
    }

    // Held and not interrupted
    switch (state->count) {
        case 1:
            unregister_code(LCTL(keycode));
            break;
    }
}

// -------------------------------------- Tap dance: ctrl letters ---------------------------------

/* Multi-Shift behavior:
All behavior ignores whether it is interrupted

Single tap: One-shot shift
Single hold: shift
Count = 2: Capslock
*/
void tap_dance_shft_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        if (state->pressed) {
            register_code(KC_LSFT);
            return;
        }
        // Apply or cancel oneshot lsft
        if (get_oneshot_mods() == MOD_LSFT) {
            clear_oneshot_mods();
            return;
        }
        set_oneshot_mods(MOD_LSFT);
    } else if (state->count == 2) {
        register_code(KC_CAPS);
    }
}

void tap_dance_shft_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1 && state->pressed) {
         unregister_code(KC_LSFT);
    } else if (state->count == 2) {
        // Ensure capslock isn't debounced
        wait_ms(DEBOUNCE_CAPS_DELAY);
        unregister_code(KC_CAPS);
    }
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [_A] = ACTION_TAP_DANCE_CTR(KC_A),
    [_B] = ACTION_TAP_DANCE_CTR(KC_B),
    [_C] = ACTION_TAP_DANCE_CTR(KC_C),
    [_D] = ACTION_TAP_DANCE_CTR(KC_D),
    [_E] = ACTION_TAP_DANCE_CTR(KC_E),
    [_F] = ACTION_TAP_DANCE_CTR(KC_F),
    [_G] = ACTION_TAP_DANCE_CTR(KC_G),
    [_H] = ACTION_TAP_DANCE_CTR(KC_H),
    [_I] = ACTION_TAP_DANCE_CTR(KC_I),
    [_J] = ACTION_TAP_DANCE_CTR(KC_J),
    [_K] = ACTION_TAP_DANCE_CTR(KC_K),
    [_L] = ACTION_TAP_DANCE_CTR(KC_L),
    [_M] = ACTION_TAP_DANCE_CTR(KC_M),
    [_N] = ACTION_TAP_DANCE_CTR(KC_N),
    [_O] = ACTION_TAP_DANCE_CTR(KC_O),
    [_P] = ACTION_TAP_DANCE_CTR(KC_P),
    [_Q] = ACTION_TAP_DANCE_CTR(KC_Q),
    [_R] = ACTION_TAP_DANCE_CTR(KC_R),
    [_S] = ACTION_TAP_DANCE_CTR(KC_S),
    [_T] = ACTION_TAP_DANCE_CTR(KC_T),
    [_U] = ACTION_TAP_DANCE_CTR(KC_U),
    [_V] = ACTION_TAP_DANCE_CTR(KC_V),
    [_W] = ACTION_TAP_DANCE_CTR(KC_W),
    [_X] = ACTION_TAP_DANCE_CTR(KC_X),
    [_Y] = ACTION_TAP_DANCE_CTR(KC_Y),
    [_Z] = ACTION_TAP_DANCE_CTR(KC_Z),
    [_SFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tap_dance_shft_finished, tap_dance_shft_reset)
};
