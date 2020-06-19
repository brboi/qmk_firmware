#include QMK_KEYBOARD_H
#include <keymap_bepo.h>

/* === LAYER NAMES === */
#define _BEPO 0
#define _FNKEYS 1
#define _LEFT_CODING 2
#define _RIGHT_NUMPAD 3
#define _RIGHT_NAVIGATION 4
#define _RIGHT_QMK_SETTINGS 5

/* === LIGHTING LAYERS === */
// LEDS NUMBERS, from left to right, are:
// Left hand -   6  5  4  3  2  1  0 
// Right hand - 13 12 11 10  9  8  7
const rgblight_segment_t PROGMEM my_fnkeys_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    { 1, 1, HSV_WHITE},
    { 3, 1, HSV_WHITE},
    { 5, 1, HSV_WHITE},
    {12, 1, HSV_WHITE},
    {10, 1, HSV_WHITE},
    { 8, 1, HSV_WHITE}
);

const rgblight_segment_t PROGMEM my_left_code_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    { 0, 3, HSV_BLUE}
);

const rgblight_segment_t PROGMEM my_right_nump_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {11, 3, HSV_YELLOW}
);

const rgblight_segment_t PROGMEM my_right_navi_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {11, 3, HSV_BLUE}
);

const rgblight_segment_t PROGMEM my_right_qmks_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    { 7, 7, HSV_CORAL}
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_fnkeys_layer,       // 0
    my_left_code_layer,    // 1
    my_right_nump_layer,   // 2
    my_right_navi_layer,   // 3
    my_right_qmks_layer    // 4
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
    rgblight_set_layer_state(4, layer_state_cmp(state, _RIGHT_QMK_SETTINGS));
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
   CM_DOUBLE_AND,
   CM_COMMENT,
   CM_FIND,
   CM_LOWER_OR_EQUAL,
   CM_RENAME
};

// Macros Definitions
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
   bool lshift_pressed = keyboard_report->mods & MOD_BIT(KC_LSHIFT);

   switch (keycode) {
      case CM_DOUBLE_OR:
         if (record->event.pressed) {
            TAP(BP_PIPE);
            TAP(BP_PIPE);
            return false;
         }
         break;
      case CM_DOUBLE_AND:
         if (record->event.pressed) {
            TAP(BP_AMPR);
            TAP(BP_AMPR);
            return false;
         }
         break;
      case CM_COMMENT:
         if (record->event.pressed) {
            if (lshift_pressed)
            {
               CTRL_SHIFT(BP_SLSH);
            }
            else
            {
               CTRL(BP_SLSH);
            }
            return false;
         }
         break;
      case CM_FIND:
         if (record->event.pressed) {
            if (lshift_pressed)
            {
               CTRL_SHIFT(BP_F);
            }
            else
            {
               CTRL(BP_F);
            }
            return false;
         }
         break;
      case CM_LOWER_OR_EQUAL:
         if (record->event.pressed) {
            if (lshift_pressed)
            {
               TAP(BP_RABK);
               TAP(BP_EQL);
            }
            else
            {
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
   }

   return true;
};

// Macros Shortcodes
#define CM_2OR  CM_DOUBLE_OR
#define CM_2AND CM_DOUBLE_AND
#define CM_COMT CM_COMMENT
#define CM_LTEQ CM_LOWER_OR_EQUAL
#define CM_RENM CM_RENAME
//*/

/* === LAYERS DEFINITION === */
// Shortcuts for keymap readability
#define LS_SPC  LSFT_T(KC_SPACE)
#define LS_CCED LSFT_T(BP_CCED)
#define LS_W    LSFT_T(BP_W)
#define LC_ENT  LCTL_T(KC_ENT)
#define RA_BSPC RALT_T(KC_BSPC)
#define OSL_FNK OSL(_FNKEYS)
#define TT_CODE TT(_LEFT_CODING)
#define TT_NAVI TT(_RIGHT_NAVIGATION)
#define BT_RNUM TG(_RIGHT_NUMPAD)
#define TO_BEPO TO(_BEPO)
#define TO_RQMK TO(_RIGHT_QMK_SETTINGS)

// The keymap
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BEPO] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_ESC  ,BP_DQUO ,BP_LDAQ ,BP_RDAQ ,BP_LPRN ,BP_RPRN ,                                            BP_AT   ,BP_PLUS ,BP_MINS ,BP_SLSH ,BP_ASTR ,BP_EQL  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     BP_W    ,BP_B    ,BP_EACU ,BP_P    ,BP_O    ,BP_EGRV ,BP_DLR  ,                          BP_PERC ,BP_DCIR ,BP_V    ,BP_D    ,BP_L    ,BP_J    ,BP_Z    ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     BP_CCED ,BP_A    ,BP_U    ,BP_I    ,BP_E    ,BP_COMM ,KC_BSPC ,                          KC_DEL  ,BP_C    ,BP_T    ,BP_S    ,BP_R    ,BP_N    ,BP_M    ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     TT_CODE ,BP_AGRV ,BP_Y    ,BP_X    ,BP_DOT  ,BP_K    ,KC_TAB  ,KC_PSCR ,        KC_PGUP ,KC_PGDN ,BP_QUOT ,BP_Q    ,BP_G    ,BP_H    ,BP_F    ,TT_NAVI ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     KC_LALT ,OSL_FNK ,KC_MEH  ,KC_LGUI ,     KC_RALT     ,LS_SPC  ,LC_ENT  ,        LC_ENT  ,LS_SPC  ,    KC_RALT      ,KC_RGUI ,BT_RNUM ,OSL_FNK ,KC_LALT 
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
     _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,_______ ,        _______ ,_______ ,    _______ ,     _______ ,_______ ,_______ ,_______
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),


  [_LEFT_CODING] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,CM_2OR  ,KC_UNDO ,KC_UP   ,KC_AGIN ,CM_LTEQ ,_______ ,                          _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,CM_2AND ,KC_LEFT ,KC_DOWN ,KC_RGHT ,CM_FIND ,_______ ,                          _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,CM_COMT ,KC_CUT  ,KC_COPY ,KC_PSTE ,CM_RENM ,_______ ,_______ ,        _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,_______ ,        _______ ,_______ ,    _______ ,     _______ ,_______ ,_______ ,_______
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_RIGHT_NUMPAD] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            KC_NLCK ,KC_PPLS ,KC_PMNS ,KC_PSLS ,KC_PAST ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                          _______ ,KC_PCMM ,KC_P7   ,KC_P8   ,KC_P9   ,XXXXXXX ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                          _______ ,KC_P0   ,KC_P4   ,KC_P5   ,KC_P6   ,XXXXXXX ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,        _______ ,_______ ,KC_PDOT ,KC_P1   ,KC_P2   ,KC_P3   ,KC_PEQL ,_______ ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,_______ ,        _______ ,_______ ,    _______ ,     _______ ,_______ ,_______ ,_______
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_RIGHT_NAVIGATION] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                          _______ ,KC_PGUP ,KC_HOME ,KC_UP   ,KC_END  ,XXXXXXX ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                          _______ ,KC_PGDN ,KC_LEFT ,KC_DOWN ,KC_RGHT ,XXXXXXX ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,        _______ ,_______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,_______ ,        _______ ,_______ ,    _______ ,     _______ ,_______ ,_______ ,_______
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