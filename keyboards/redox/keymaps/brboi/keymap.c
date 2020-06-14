#include QMK_KEYBOARD_H
#include <keymap_bepo.h>
#include <sendstring_bepo.h>

/* === LAYER NAMES === */
#define _BEPO 0
#define _LEFT_NAVIGATION 1
#define _RIGHT_NAVIGATION 2
#define _LEFT_NUMPAD 3
#define _RIGHT_NUMPAD 4
#define _LEFT_QMK_SETTINGS 5
#define _RIGHT_QMK_SETTINGS 6
#define _CUSTOM_LAYER_CHOICE 7

/* === LIGHTING LAYERS === */
// LEDS NUMBERS, from left to right, are:
// Left hand -   6  5  4  3  2  1  0 
// Right hand - 13 12 11 10  9  8  7
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    { 4, 3, HSV_GOLD},  // Light 3 LEDs, starting with LED 4
    { 7, 3, HSV_GOLD}   // Light 3 LEDs, starting with LED 7
);

const rgblight_segment_t PROGMEM my_choice_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    { 0, 14, HSV_AZURE}
);

const rgblight_segment_t PROGMEM my_left_navi_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    { 0, 4, HSV_CHARTREUSE}
);

const rgblight_segment_t PROGMEM my_right_navi_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {10, 4, HSV_CHARTREUSE}
);

const rgblight_segment_t PROGMEM my_left_nump_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    { 0, 4, HSV_PURPLE}
);

const rgblight_segment_t PROGMEM my_right_nump_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {10, 4, HSV_PURPLE}
);

const rgblight_segment_t PROGMEM my_left_qmks_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    { 0, 4, HSV_CORAL}
);

const rgblight_segment_t PROGMEM my_right_qmks_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {10, 4, HSV_CORAL}
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_capslock_layer,     // 0
    my_left_navi_layer,    // 1
    my_right_navi_layer,   // 2
    my_left_nump_layer,    // 3
    my_right_nump_layer,   // 4
    my_left_qmks_layer,    // 5
    my_right_qmks_layer,   // 6
    my_choice_layer        // 7
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

// Enabling lighting layers
bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(0, led_state.caps_lock);
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(1, layer_state_cmp(state, _LEFT_NAVIGATION));
    rgblight_set_layer_state(2, layer_state_cmp(state, _RIGHT_NAVIGATION));
    rgblight_set_layer_state(3, layer_state_cmp(state, _LEFT_NUMPAD));
    rgblight_set_layer_state(4, layer_state_cmp(state, _RIGHT_NUMPAD));
    rgblight_set_layer_state(5, layer_state_cmp(state, _LEFT_QMK_SETTINGS));
    rgblight_set_layer_state(6, layer_state_cmp(state, _RIGHT_QMK_SETTINGS));
    rgblight_set_layer_state(7, layer_state_cmp(state, _CUSTOM_LAYER_CHOICE));
    return state;
}

/* === MACROS === */
enum custom_keycodes {
  KC_PGUP_CUSTOM_LAYER_CHOICE = SAFE_RANGE,
  KC_PGDN_CUSTOM_LAYER_CHOICE,
  BP_LCBR_SLSH,
  BP_RCBR_BSLS,
  
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


/* === LAYERS DEFINITION === */
// Shortcuts for keymap readability
#define LS_SPC  LSFT_T(KC_SPACE)
#define LS_ECIR LSFT_T(BP_ECIR)
#define LS_CCED LSFT_T(BP_CCED)
#define ACTL_LE LCTL_T(KC_LEFT)
#define ACTL_RI RCTL_T(KC_RGHT)
#define AGUI_UP RGUI_T(KC_UP)
#define AGUI_DN LGUI_T(KC_DOWN)
#define AALT_LE LALT_T(KC_LEFT)
#define AALT_RI LALT_T(KC_RGHT)
#define UP_LNAV LT(_LEFT_NAVIGATION, KC_UP)
#define DN_RNUM LT(_RIGHT_NUMPAD, KC_DOWN)
#define TO_BEPO TO(_BEPO)
#define TG_CLCH TG(_CUSTOM_LAYER_CHOICE)
#define BT_LNAV TG(_LEFT_NAVIGATION)
#define BT_RNAV TG(_RIGHT_NAVIGATION)
#define BT_LNUM TG(_LEFT_NUMPAD)
#define BT_RNUM TG(_RIGHT_NUMPAD)
#define BT_LQMK TG(_LEFT_QMK_SETTINGS)
#define BT_RQMK TG(_RIGHT_QMK_SETTINGS)

// The keymap
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BEPO] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_GESC ,BP_DQUO ,BP_LDAQ ,BP_RDAQ ,BP_LPRN ,BP_RPRN ,                                            BP_AT   ,BP_PLUS ,BP_MINS ,BP_SLSH ,BP_ASTR ,BP_W    ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB  ,BP_B    ,BP_EACU ,BP_P    ,BP_O    ,BP_EGRV ,BP_EQL  ,                          BP_PERC ,BP_DCIR ,BP_V    ,BP_D    ,BP_L    ,BP_J    ,BP_Z    ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_CAPS ,BP_A    ,BP_U    ,BP_I    ,BP_E    ,BP_COMM ,KC_HOME ,                          KC_END  ,BP_C    ,BP_T    ,BP_S    ,BP_R    ,BP_N    ,BP_M    ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     LS_ECIR ,BP_AGRV ,BP_Y    ,BP_X    ,BP_DOT  ,BP_K    ,KC_ENT  ,KC_DEL  ,        KC_DEL  ,KC_ENT  ,BP_QUOT ,BP_Q    ,BP_G    ,BP_H    ,BP_F    ,LS_CCED ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     ACTL_LE ,AGUI_DN ,UP_LNAV ,AALT_RI ,     KC_RALT     ,LS_SPC  ,KC_BSPC ,        KC_BSPC ,LS_SPC  ,    KC_RALT      ,AALT_LE ,DN_RNUM ,AGUI_UP ,ACTL_RI 
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_LEFT_NAVIGATION] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_MSEL ,KC_MRWD ,KC_MPRV ,KC_MPLY ,KC_MNXT ,KC_MFFD ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB  ,KC_INS  ,KC_HOME ,KC_UP   ,KC_END  ,KC_PGUP ,KC_MUTE ,                          _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_SPC  ,KC_DEL  ,KC_LEFT ,KC_DOWN ,KC_RGHT ,KC_PGDN ,KC_APP  ,                          _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT ,KC_PSCR ,KC_CUT  ,KC_COPY ,KC_PSTE ,KC_FIND ,KC_UNDO ,KC_AGIN ,        _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     KC_LCTL ,KC_LGUI ,BT_LNAV  ,KC_LALT ,     KC_RALT ,    KC_VOLD ,KC_VOLU ,        _______ ,_______ ,    _______ ,     _______ ,_______ ,_______ ,_______
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_RIGHT_NAVIGATION] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            KC_MRWD ,KC_MPRV ,KC_MPLY ,KC_MNXT ,KC_MFFD ,KC_MSEL ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                          KC_MUTE ,KC_PGUP ,KC_HOME ,KC_UP   ,KC_END  ,KC_INS  ,KC_TAB  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                          KC_APP  ,KC_PGDN ,KC_LEFT ,KC_DOWN ,KC_RGHT ,KC_DEL  ,KC_SPC  ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,        KC_AGIN ,KC_UNDO ,KC_FIND ,KC_CUT  ,KC_COPY ,KC_PSTE ,KC_PSCR ,KC_RSFT ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,_______ ,        KC_VOLU ,KC_VOLD ,    KC_RALT ,     KC_LALT ,BT_RNAV  ,KC_RGUI ,KC_RCTL
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_LEFT_NUMPAD] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_F11  ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     BP_CIRC ,BP_E    ,BP_F    ,KC_P7   ,KC_P8   ,KC_P9   ,KC_NLCK ,                          _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     BP_PERC ,BP_C    ,BP_D    ,KC_P4   ,KC_P5   ,KC_P6   ,KC_PEQL ,                          _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     BP_EXLM ,BP_A    ,BP_B    ,KC_P1   ,KC_P2   ,KC_P3   ,KC_PMNS ,KC_PSLS ,        _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     KC_LCTL ,KC_LGUI ,BT_LNUM ,KC_PDOT ,     KC_P0   ,    KC_PPLS ,KC_PAST ,        _______ ,_______ ,    _______ ,     _______ ,_______ ,_______ ,_______
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_RIGHT_NUMPAD] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  , KC_F12 ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                          KC_NLCK ,KC_P7   ,KC_P8   ,KC_P9   ,BP_E    ,BP_F    ,BP_CIRC ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                          KC_PEQL ,KC_P4   ,KC_P5   ,KC_P6   ,BP_C    ,BP_D    ,BP_PERC ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,        KC_PSLS ,KC_PMNS ,KC_P1   ,KC_P2   ,KC_P3   ,BP_A    ,BP_B    ,BP_EXLM ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,_______ ,        KC_PAST ,KC_PPLS ,    KC_P0   ,     KC_PDOT ,BT_RNUM ,KC_RGUI ,KC_RCTL
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_LEFT_QMK_SETTINGS] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,RGB_HUD ,RGB_HUI ,RGB_M_X ,RGB_M_G ,XXXXXXX ,XXXXXXX ,                          _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,RGB_SAD ,RGB_SAI ,RGB_M_SW,RGB_M_SN,RGB_M_K ,BT_LQMK ,                          _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,RGB_VAD ,RGB_VAI ,RGB_M_P ,RGB_M_B ,RGB_M_R ,RESET   ,DEBUG   ,        _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,RGB_SPD ,RGB_SPI ,XXXXXXX ,     RGB_TOG ,    XXXXXXX ,XXXXXXX ,        _______ ,_______ ,    _______ ,     _______ ,_______ ,_______ ,_______
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_RIGHT_QMK_SETTINGS] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                          XXXXXXX ,RGB_M_X ,RGB_M_G ,XXXXXXX ,RGB_HUI ,RGB_HUD ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                          BT_RQMK ,RGB_M_SW,RGB_M_SN,RGB_M_K ,RGB_SAI ,RGB_SAD ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,        DEBUG   ,RESET   ,RGB_M_P ,RGB_M_B ,RGB_M_R ,RGB_VAI ,RGB_VAD ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,_______ ,        XXXXXXX ,XXXXXXX ,    RGB_TOG ,     XXXXXXX ,RGB_SPI ,RGB_SPD ,XXXXXXX
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_CUSTOM_LAYER_CHOICE] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                                            XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,BT_LNUM ,                          BT_RNAV ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,TG_CLCH ,                          TG_CLCH ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,BT_LQMK ,XXXXXXX ,        XXXXXXX ,BT_RQMK ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,XXXXXXX ,BT_LNAV ,XXXXXXX ,     XXXXXXX ,    XXXXXXX ,XXXXXXX ,        XXXXXXX ,XXXXXXX ,    XXXXXXX ,     XXXXXXX ,BT_RNUM ,XXXXXXX ,XXXXXXX
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  )
};