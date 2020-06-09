#include QMK_KEYBOARD_H


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BEPO 0
#define _CODING 1
#define _FUNCT 2
#define _QMKS 3

enum custom_keycodes {
  BEPO = SAFE_RANGE,
  CODING,
  FUNCT,
  QMKS,
  MC_P00,
};

// Layers light config
const rgblight_segment_t PROGMEM my_bepo_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    { 0, 2, HSV_CYAN},
    {12, 2, HSV_CYAN}
);
const rgblight_segment_t PROGMEM my_coding_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    { 0, 2, HSV_CHARTREUSE},
    {12, 2, HSV_CHARTREUSE}
);
const rgblight_segment_t PROGMEM my_funct_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    { 0, 2, HSV_GOLDENROD},
    {12, 2, HSV_GOLDENROD}
);
const rgblight_segment_t PROGMEM my_qmks_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    { 0, 2, HSV_RED},
    {12, 2, HSV_RED}
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_bepo_layer,
    my_coding_layer,
    my_funct_layer,
    my_qmks_layer
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

// Enabling lighting layers
layer_state_t layer_state_set_user(layer_state_t state) {
    // Both layers will light up if both kb layers are active
    rgblight_set_layer_state(0, layer_state_cmp(state, 0));
    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    rgblight_set_layer_state(3, layer_state_cmp(state, 3));
    return state;
}

// Macros
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case MC_P00:
      if (record->event.pressed) {
        // when keycode MC_P00 is pressed
        SEND_STRING(SS_TAP(X_P0)SS_TAP(X_P0));
      } else {
        // when keycode MC_P00 is released
      }
      break;

  }
  return true;
};

// Shortcut to make keymap more readable
#define LT_CORA LT(_CODING, OSM(MOD_RALT))
#define LT_FNCA LT(_FUNCT, OSM(MOD_LCTL|MOD_LALT))
#define LT_QHOM LT(_QMKS, KC_HOME)
#define LT_QEND LT(_QMKS, KC_END)

// CTRL-H to replace text
#define KC_RPLC LCTL(KC_DOT)

// Push-to-talk (ctrl-alt-maj-ccedil)
#define KC_PUTT MEH(KC_BSLS)

// Curly braces (opening - closing)
#define KC_OCBR RALT(KC_X)
#define KC_CCBR RALT(KC_C)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BEPO] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_GRV  ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,                                            KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,KC_MINS ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     LT_FNCA ,KC_Z    ,KC_Q    ,KC_W    ,KC_R    ,KC_N    ,LT_QHOM ,                          LT_QEND ,KC_Y    ,KC_U    ,KC_O    ,KC_QUOT ,KC_C    ,LT_FNCA ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_BSLS ,KC_S    ,KC_A    ,KC_D    ,KC_F    ,KC_P    ,KC_TAB  ,                          KC_ENT  ,KC_COMM ,KC_J    ,KC_K    ,KC_SCLN ,KC_L    ,KC_SLSH ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT ,KC_M    ,KC_X    ,KC_T    ,KC_E    ,KC_B    ,KC_DEL  ,KC_ESC  ,        KC_EQL  ,KC_BSPC ,KC_RBRC ,KC_I    ,KC_LBRC ,KC_DOT  ,KC_H    ,KC_RSFT ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     KC_LCTL ,KC_LGUI ,KC_APP  ,KC_LALT ,     LT_CORA     ,KC_SPC  ,KC_V    ,        KC_G    ,KC_SPC  ,    LT_CORA ,     KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT 
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_CODING] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     KC_RPLC ,KC_MPLY ,KC_MRWD ,KC_MFFD ,KC_OCBR ,KC_CCBR ,                                            KC_Y    ,KC_PPLS ,KC_PMNS ,KC_PSLS ,KC_PAST ,KC_PEQL ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_VOLU ,KC_HOME ,KC_UP   ,KC_END  ,KC_PGUP ,_______ ,                          _______ ,KC_P7   ,KC_P8   ,KC_P9   ,KC_F    ,KC_SLSH ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,KC_VOLD ,KC_LEFT ,KC_DOWN ,KC_RGHT ,KC_PGDN ,_______ ,                          _______ ,KC_P4   ,KC_P5   ,KC_P6   ,KC_H    ,KC_I    ,KC_LGUI ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_MUTE ,KC_CUT  ,KC_COPY ,KC_PSTE ,KC_FIND ,_______ ,_______ ,        _______ ,_______ ,KC_P1   ,KC_P2   ,KC_P3   ,KC_A    ,KC_Q    ,_______ ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,_______ ,        KC_PDOT ,_______ ,    _______ ,     KC_P0   ,MC_P00  ,KC_PDOT ,KC_NLCK
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_FUNCT] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     XXXXXXX ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,                                            KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_ACL2 ,KC_WH_L ,KC_MS_U ,KC_WH_R ,KC_WH_U ,_______ ,                          _______ ,KC_INS  ,KC_HOME ,KC_UP   ,KC_END  ,KC_PGUP ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,KC_ACL1 ,KC_MS_L ,KC_MS_D ,KC_MS_R ,KC_WH_D ,_______ ,                          _______ ,KC_DEL  ,KC_LEFT ,KC_DOWN ,KC_RGHT ,KC_PGDN ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,KC_ACL0 ,KC_BTN4 ,KC_BTN3 ,KC_BTN5 ,KC_BTN3 ,_______ ,_______ ,        KC_SLCK ,_______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     _______ ,_______ ,_______ ,_______ ,     _______ ,    KC_BTN1 ,KC_BTN2 ,        KC_PAUS ,KC_PSCR ,    _______ ,     KC_F11  ,KC_F12  ,KC_F13  ,KC_F14
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  ),

  [_QMKS] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
     XXXXXXX ,RGB_M_P ,RGB_M_B ,RGB_M_R ,RGB_M_SN,RGB_TOG ,                                            RGB_TOG ,RGB_M_P ,RGB_M_B ,RGB_M_R ,RGB_M_SW,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,                          _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     XXXXXXX ,RGB_HUI ,RGB_SAI ,RGB_VAI ,RGB_SPI ,XXXXXXX ,_______ ,                          _______ ,XXXXXXX ,RGB_HUI ,RGB_SAI ,RGB_VAI ,RGB_SPI ,XXXXXXX ,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     _______ ,RGB_HUD ,RGB_SAD ,RGB_VAD ,RGB_SPD ,XXXXXXX ,DEBUG   ,RESET   ,        RESET   ,DEBUG   ,XXXXXXX ,RGB_HUD ,RGB_SAD ,RGB_VAD ,RGB_SPD ,_______ ,
  //├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
     RGB_M_SN,RGB_M_K ,RGB_M_X ,RGB_M_G ,     _______ ,    RGB_RMOD,RGB_MOD ,        RGB_RMOD,RGB_MOD ,    _______ ,     RGB_M_SN,RGB_M_K ,RGB_M_X ,RGB_M_G
  //└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
  )
};