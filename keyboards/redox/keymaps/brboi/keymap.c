#include QMK_KEYBOARD_H
#include <keymap_bepo.h>
#include <sendstring_bepo.h>

/* === LAYER NAMES === */
#define _BEPO 0
#define _LEFT_NAVIGATION 1
#define _RIGHT_NUMPAD 2
#define _FNKEYS 3
#define _RIGHT_QMK_SETTINGS 4

/* === LIGHTING LAYERS === */
// LEDS NUMBERS, from left to right, are:
// Left hand -   6  5  4  3  2  1  0 
// Right hand - 13 12 11 10  9  8  7
const rgblight_segment_t PROGMEM my_fnkeys_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    { 1, 1, HSV_BLUE},
    { 3, 1, HSV_BLUE},
    { 5, 1, HSV_BLUE},
    {12, 1, HSV_BLUE},
    {10, 1, HSV_BLUE},
    { 8, 1, HSV_BLUE}
);

const rgblight_segment_t PROGMEM my_left_navi_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    { 0, 3, HSV_YELLOW}
);

const rgblight_segment_t PROGMEM my_right_nump_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {11, 3, HSV_YELLOW}
);

const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    { 2, 1, HSV_RED},
    { 4, 1, HSV_RED},
    { 6, 1, HSV_RED},
    {11, 1, HSV_RED},
    { 9, 1, HSV_RED},
    { 7, 1, HSV_RED}
);

const rgblight_segment_t PROGMEM my_right_qmks_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    { 7, 7, HSV_CORAL}
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_fnkeys_layer,       // 0
    my_left_navi_layer,    // 1
    my_right_nump_layer,   // 2
    my_capslock_layer,     // 3
    my_right_qmks_layer    // 4
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

// Enabling lighting layers
bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(3, led_state.caps_lock);
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _FNKEYS));
    rgblight_set_layer_state(1, layer_state_cmp(state, _LEFT_NAVIGATION));
    rgblight_set_layer_state(2, layer_state_cmp(state, _RIGHT_NUMPAD));
    rgblight_set_layer_state(4, layer_state_cmp(state, _RIGHT_QMK_SETTINGS));
    return state;
}

/* === MACROS === * /
enum custom_keycodes {
  KC_NEWMACRO = SAFE_RANGE
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
   bool ralt_pressed = keyboard_report->mods & MOD_BIT(KC_RALT);

   switch (keycode) {
      case KC_HOME:
      case KC_END:
         if (ralt_pressed) {
            if (record->event.pressed){
               layer_on(_CUSTOM_LAYER_CHOICE);
               return false;
            }
            else {
               layer_off(_CUSTOM_LAYER_CHOICE);
               return false;
            }
         }
         break;
   }

   return true;
};
//*/

/* === TAP DANCE === */
//Tap Dance Declarations
enum {
  TD_LGUI_FN = 0,
  TD_RGUI_FN
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
   [TD_LGUI_FN]   = ACTION_TAP_DANCE_LAYER_TOGGLE(KC_LGUI, _FNKEYS),
   [TD_RGUI_FN]   = ACTION_TAP_DANCE_LAYER_TOGGLE(KC_RGUI, _FNKEYS)
};
//*/


/* === LAYERS DEFINITION === */
// Shortcuts for keymap readability
#define LS_SPC  LSFT_T(KC_SPACE)
#define LS_CCED LSFT_T(BP_CCED)
#define LS_W    LSFT_T(BP_W)
#define LC_ENT  LCTL_T(KC_ENT)
#define RA_BSPC RALT_T(KC_BSPC)
#define TD_LGFN TD(TD_LGUI_FN)
#define TD_RGFN TD(TD_RGUI_FN)
#define BT_LNAV TT(_LEFT_NAVIGATION)
#define BT_RNUM TT(_RIGHT_NUMPAD)
#define TO_BEPO TO(_BEPO)
#define TO_RQMK TO(_RIGHT_QMK_SETTINGS)

// The keymap
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BEPO] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     BP_DLR  ,BP_DQUO ,BP_LDAQ ,BP_RDAQ ,BP_LPRN ,BP_RPRN ,                                            BP_AT   ,BP_PLUS ,BP_MINS ,BP_SLSH ,BP_ASTR ,KC_ESC  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB  ,BP_B    ,BP_EACU ,BP_P    ,BP_O    ,BP_EGRV ,KC_PGUP ,                          KC_HOME ,BP_DCIR ,BP_V    ,BP_D    ,BP_L    ,BP_J    ,BP_Z    ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_CAPS ,BP_A    ,BP_U    ,BP_I    ,BP_E    ,BP_COMM ,KC_PGDN ,                          KC_END  ,BP_C    ,BP_T    ,BP_S    ,BP_R    ,BP_N    ,BP_M    ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     LS_W    ,BP_AGRV ,BP_Y    ,BP_X    ,BP_DOT  ,BP_K    ,BP_EQL  ,KC_DEL  ,        KC_DEL  ,BP_PERC ,BP_QUOT ,BP_Q    ,BP_G    ,BP_H    ,BP_F    ,LS_CCED ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     KC_LCTL ,KC_LALT ,BT_LNAV ,TD_LGFN ,     LS_SPC      ,RA_BSPC ,LC_ENT  ,        LC_ENT  ,RA_BSPC ,    LS_SPC       ,TD_RGFN ,BT_RNUM ,KC_LALT ,KC_RCTL 
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_LEFT_NAVIGATION] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,KC_HOME ,KC_UP   ,KC_END  ,KC_PGUP ,_______ ,                          _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,KC_LEFT ,KC_DOWN ,KC_RGHT ,KC_PGDN ,_______ ,                          _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_CUT  ,KC_COPY ,KC_PSTE ,KC_PSCR ,_______ ,_______ ,_______ ,        _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,_______ ,        _______ ,_______ ,    _______ ,     _______ ,_______ ,_______ ,_______
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_RIGHT_NUMPAD] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            KC_NLCK ,KC_PPLS ,KC_PMNS ,KC_PSLS ,KC_PAST ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                          KC_PDOT ,KC_P7   ,KC_P8   ,KC_P9   ,KC_PAST ,BP_A    ,BP_B    ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                          KC_P0   ,KC_P4   ,KC_P5   ,KC_P6   ,KC_PMNS ,BP_C    ,BP_D    ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,        _______ ,_______ ,KC_P1   ,KC_P2   ,KC_P3   ,KC_PPLS ,BP_E    ,BP_F    ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,_______ ,        _______ ,_______ ,    _______ ,     _______ ,_______ ,_______ ,_______
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

  [_RIGHT_QMK_SETTINGS] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,TO_BEPO ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                          XXXXXXX ,RGB_M_X ,RGB_M_G ,XXXXXXX ,RGB_HUD ,RGB_HUI ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                          XXXXXXX ,RGB_M_SW,RGB_M_SN,RGB_M_K ,RGB_SAD ,RGB_SAI ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,        DEBUG   ,RESET   ,RGB_M_P ,RGB_M_B ,RGB_M_R ,RGB_VAD ,RGB_VAI ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,_______ ,        XXXXXXX ,XXXXXXX ,    RGB_TOG ,     XXXXXXX ,RGB_SPD ,RGB_SPI ,XXXXXXX
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  )
};