#include QMK_KEYBOARD_H
#include <keymap_bepo.h>

/* === LAYER NAMES === */
#define _BEPO 0
#define _FNKEYS 1
#define _LEFT_CODING 2
#define _RIGHT_NUMPAD 3
#define _RIGHT_NAVIGATION 4
#define _RIGHT_MOUSE 5
#define _RIGHT_QMK_SETTINGS 6

/* === LIGHTING LAYERS === */
// LEDS NUMBERS, from left to right, are:
// Left hand -   6  5  4  3  2  1  0 
// Right hand - 13 12 11 10  9  8  7
const rgblight_segment_t PROGMEM my_fnkeys_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    { 4, 3, HSV_PINK},
    { 7, 3, HSV_PINK}
);

const rgblight_segment_t PROGMEM my_left_code_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    { 0, 4, HSV_TEAL}
);

const rgblight_segment_t PROGMEM my_right_nump_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {10, 4, HSV_CHARTREUSE}
);

const rgblight_segment_t PROGMEM my_right_navi_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {10, 4, HSV_TEAL}
);

const rgblight_segment_t PROGMEM my_right_mouse_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {10, 4, HSV_CYAN}
);

const rgblight_segment_t PROGMEM my_right_qmks_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    { 7, 7, HSV_PURPLE}
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_fnkeys_layer,       // 0
    my_left_code_layer,    // 1
    my_right_nump_layer,   // 2
    my_right_navi_layer,   // 3
    my_right_mouse_layer,   // 4
    my_right_qmks_layer    // 5
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

// Enabling lighting layers
layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _FNKEYS));
    rgblight_set_layer_state(1, layer_state_cmp(state, _LEFT_CODING));
    rgblight_set_layer_state(2, layer_state_cmp(state, _RIGHT_NUMPAD));
    rgblight_set_layer_state(3, layer_state_cmp(state, _RIGHT_NAVIGATION));
    rgblight_set_layer_state(4, layer_state_cmp(state, _RIGHT_MOUSE));
    rgblight_set_layer_state(5, layer_state_cmp(state, _RIGHT_QMK_SETTINGS));
    return state;
}

/* === MACROS === */
#define PRESS(keycode) register_code16(keycode)
#define RELEASE(keycode) unregister_code16(keycode)

void TAP(uint16_t keycode) {
   PRESS(keycode);
   RELEASE(keycode);
}

void CTRL(uint16_t keycode) {
   PRESS(KC_LCTRL);
   TAP(keycode);
   RELEASE(KC_LCTRL);
}

void SHIFT(uint16_t keycode) {
   PRESS(KC_LSHIFT);
   TAP(keycode);
   RELEASE(KC_LSHIFT);
}

void CTRL_SHIFT(uint16_t keycode) {
   PRESS(KC_LCTRL);
   SHIFT(keycode);
   RELEASE(KC_LCTRL);
}

// Macros Declarations
enum custom_keycodes {
   CM_DOUBLE_OR = SAFE_RANGE,
   CM_COMMENT,
   CM_FIND,
   CM_LOWER_OR_EQUAL,
   CM_UNDO,
   CM_RENAME,
   CM_CUT,
   CM_COPY,
   CM_PASTE,
   CM_MOVE_LINE_DOWN,
   CM_MOVE_LINE_UP
};

// Macros Definitions
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
   bool lshift_pressed = keyboard_report->mods & MOD_BIT(KC_LSHIFT);

   switch (keycode) {
      case CM_DOUBLE_OR:
         if (record->event.pressed) {
            if (lshift_pressed)
            {
               // Double ampersand - &&
               RELEASE(KC_LSHIFT);
               TAP(BP_AMPR);
               TAP(BP_AMPR);
               PRESS(KC_LSHIFT);
            }
            else
            {
               // Double pipe - ||
               TAP(BP_PIPE);
               TAP(BP_PIPE);
            }
            return false;
         }
         break;
      case CM_COMMENT:
         if (record->event.pressed) {
            if (lshift_pressed)
            {
               // Toggle block comment - CTRL + SHIFT + /
               RELEASE(KC_LSHIFT);
               CTRL_SHIFT(BP_SLSH);
               PRESS(KC_LSHIFT);
            }
            else
            {
               // Toggle inline comment - CTRL + /
               CTRL(BP_SLSH);
            }
            return false;
         }
         break;
      case CM_FIND:
         if (record->event.pressed) {
            if (lshift_pressed)
            {
               // Find in files - CTRL + SHIFT + F
               RELEASE(KC_LSHIFT);
               CTRL_SHIFT(BP_F);
               PRESS(KC_LSHIFT);
            }
            else
            {
               // Find - CTRL + F
               CTRL(BP_F);
            }
            return false;
         }
         break;
      case CM_LOWER_OR_EQUAL:
         if (record->event.pressed) {
            if (lshift_pressed)
            {
               // Greater or equal - >=
               RELEASE(KC_LSHIFT);
               TAP(BP_RABK);
               TAP(BP_EQL);
               PRESS(KC_LSHIFT);
            }
            else
            {
               // Lower or equal - <=
               TAP(BP_LABK);
               TAP(BP_EQL);
            }
            return false;
         }
         break;
      case CM_RENAME:
         if (record->event.pressed) {
            TAP(KC_F2);
            return false;
         }
         break;
      case CM_UNDO:
         if (record->event.pressed) {
            if (lshift_pressed)
            {
               // REDO shortcut - CTRL + SHIFT + Z
               RELEASE(KC_LSHIFT);
               CTRL_SHIFT(BP_Z);
               PRESS(KC_LSHIFT);
            }
            else
            {
               // UNDO shortcut - CTRL + Z
               CTRL(BP_Z);
            }
            return false;
         }
         break;
      case CM_CUT:
         if (record->event.pressed) {
            if (lshift_pressed)
            {
               RELEASE(KC_LSHIFT);
               TAP(KC_CUT);
               PRESS(KC_LSHIFT);
            }
            else {
               CTRL(BP_X);
            }
            return false;
         }
         break;
      case CM_COPY:
         if (record->event.pressed) {
            if (lshift_pressed)
            {
               RELEASE(KC_LSHIFT);
               TAP(KC_COPY);
               PRESS(KC_LSHIFT);
            }
            else {
               CTRL(BP_C);
            }
            return false;
         }
         break;
      case CM_PASTE:
         if (record->event.pressed) {
            if (lshift_pressed)
            {
               RELEASE(KC_LSHIFT);
               TAP(KC_PASTE);
               PRESS(KC_LSHIFT);
            }
            else {
               CTRL(BP_V);
            }
            return false;
         }
         break;
      case CM_MOVE_LINE_DOWN:
         if (record->event.pressed) {
            if (lshift_pressed)
            {
               // Copy line down
               RELEASE(KC_LSHIFT);
               PRESS(KC_LCTL);
               PRESS(KC_LALT);
               TAP(KC_DOWN);
               RELEASE(KC_LALT);
               RELEASE(KC_LCTL);
               PRESS(KC_LSHIFT);
            }
            else {
               // Move line down
               PRESS(KC_LALT);
               TAP(KC_DOWN);
               RELEASE(KC_LALT);
            }
            return false;
         }
         break;
      case CM_MOVE_LINE_UP:
         if (record->event.pressed) {
            if (lshift_pressed)
            {
               // Copy line up
               RELEASE(KC_LSHIFT);
               PRESS(KC_LCTL);
               PRESS(KC_LALT);
               TAP(KC_UP);
               RELEASE(KC_LALT);
               RELEASE(KC_LCTL);
               PRESS(KC_LSHIFT);
            }
            else {
               // Move line up
               PRESS(KC_LALT);
               TAP(KC_UP);
               RELEASE(KC_LALT);
            }
            return false;
         }
         break;
   }

   return true;
};

// Macros Shortcodes
#define CM_2OR  CM_DOUBLE_OR
#define CM_COMT CM_COMMENT
#define CM_LTEQ CM_LOWER_OR_EQUAL
#define CM_RENM CM_RENAME
#define CM_PSTE CM_PASTE
#define CM_MVLD CM_MOVE_LINE_DOWN
#define CM_MVLU CM_MOVE_LINE_UP

/* === LAYERS DEFINITION === */
// Shortcuts for keymap readability
#define LS_SPC  LSFT_T(KC_SPACE)
#define LC_BSPC LCTL_T(KC_BSPC)
#define LC_DEL  LCTL_T(KC_DEL)

#define TO_BEPO TO(_BEPO)
#define OSL_FNK OSL(_FNKEYS)
#define TO_FNKY TO(_FNKEYS)
#define TG_FNKY TG(_FNKEYS)
#define TG_CODE TG(_LEFT_CODING)
#define TO_RNUM TO(_RIGHT_NUMPAD)
#define TG_RNUM TG(_RIGHT_NUMPAD)
#define TG_NAVI TG(_RIGHT_NAVIGATION)
#define TG_MOUS TG(_RIGHT_MOUSE)
#define TO_RQMK TO(_RIGHT_QMK_SETTINGS)

// The keymap
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BEPO] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_ESC  ,BP_DQUO ,BP_LDAQ ,BP_RDAQ ,BP_LPRN ,BP_RPRN ,                                            BP_AT   ,BP_PLUS ,BP_MINS ,BP_SLSH ,BP_ASTR ,BP_EQL  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     BP_W    ,BP_B    ,BP_EACU ,BP_P    ,BP_O    ,BP_EGRV ,BP_DLR  ,                          BP_PERC ,BP_DCIR ,BP_V    ,BP_D    ,BP_L    ,BP_J    ,BP_Z    ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     BP_CCED ,BP_A    ,BP_U    ,BP_I    ,BP_E    ,BP_COMM ,KC_ENT  ,                          KC_ENT  ,BP_C    ,BP_T    ,BP_S    ,BP_R    ,BP_N    ,BP_M    ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     TG_CODE ,BP_AGRV ,BP_Y    ,BP_X    ,BP_DOT  ,BP_K    ,KC_TAB  ,KC_DEL  ,        KC_DEL  ,KC_PSCR ,BP_QUOT ,BP_Q    ,BP_G    ,BP_H    ,BP_F    ,TG_NAVI ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     KC_LALT ,OSL_FNK ,KC_MEH  ,KC_LGUI ,     KC_RALT     ,LS_SPC  ,LC_BSPC ,        LC_BSPC ,LS_SPC  ,    KC_RALT      ,KC_RGUI ,TG_RNUM ,OSL_FNK ,KC_LALT 
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_FNKEYS] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,                                            KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,TO_RQMK ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,KC_F11  ,                          KC_F12  ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                          _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,        _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,TG_FNKY ,_______ ,_______ ,     _______ ,    _______ ,_______ ,        _______ ,_______ ,    _______ ,     _______ ,TO_RNUM ,TG_FNKY ,_______
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),


  [_LEFT_CODING] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     CM_MVLU ,CM_2OR  ,KC_HOME ,KC_UP   ,KC_END  ,CM_LTEQ ,_______ ,                          _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     CM_MVLD ,CM_UNDO ,KC_LEFT ,KC_DOWN ,KC_RGHT ,CM_COMT ,_______ ,                          _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,CM_RENM ,CM_CUT  ,CM_COPY ,CM_PSTE ,CM_FIND ,_______ ,_______ ,        _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,_______ ,        _______ ,_______ ,    _______ ,     _______ ,_______ ,_______ ,_______
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_RIGHT_NUMPAD] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            KC_NLCK ,KC_PPLS ,KC_PMNS ,KC_PSLS ,KC_PAST ,KC_PEQL ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                          _______ ,KC_PCMM ,KC_P7   ,KC_P8   ,KC_P9   ,KC_PSLS ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                          _______ ,KC_P0   ,KC_P4   ,KC_P5   ,KC_P6   ,KC_PMNS ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,        _______ ,_______ ,KC_PDOT ,KC_P1   ,KC_P2   ,KC_P3   ,KC_PPLS ,_______ ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,_______ ,        _______ ,_______ ,    _______ ,     _______ ,_______ ,TO_FNKY ,_______
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_RIGHT_NAVIGATION] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                          _______ ,KC_PGUP ,KC_HOME ,KC_UP   ,KC_END  ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                          _______ ,KC_PGDN ,KC_LEFT ,KC_DOWN ,KC_RGHT ,XXXXXXX ,TG_MOUS ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,        _______ ,_______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,_______ ,        _______ ,_______ ,    _______ ,     _______ ,TO_RNUM ,_______ ,_______
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_RIGHT_MOUSE] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                          _______ ,KC_WH_U ,KC_WH_L ,KC_MS_U ,KC_WH_R ,KC_ACL0 ,KC_ACL2 ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                          _______ ,KC_WH_D ,KC_MS_L ,KC_MS_D ,KC_MS_R ,XXXXXXX ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,        _______ ,_______ ,KC_BTN4 ,KC_BTN1 ,KC_BTN3 ,KC_BTN2 ,KC_BTN5 ,TG_MOUS ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,_______ ,        _______ ,_______ ,    _______ ,     _______ ,TO_RNUM ,_______ ,_______
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_RIGHT_QMK_SETTINGS] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,TO_BEPO ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                          XXXXXXX ,RGB_M_X ,RGB_M_G ,XXXXXXX ,RGB_HUD ,RGB_HUI ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                          XXXXXXX ,RGB_M_SW,RGB_M_SN,RGB_M_K ,RGB_SAD ,RGB_SAI ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,        DEBUG   ,XXXXXXX ,RGB_M_P ,RGB_M_B ,RGB_M_R ,RGB_VAD ,RGB_VAI ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,_______ ,        RESET   ,XXXXXXX ,    RGB_TOG ,     XXXXXXX ,RGB_SPD ,RGB_SPI ,XXXXXXX
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  )
};