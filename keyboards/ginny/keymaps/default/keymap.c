/* Welcome to ASETNIOP
 *
 * This is a very different layout based off this table
 * http://asetniop.com/combinations
 *
 * Unlike standard Asetniop there are a few concessions that must be
 * made. Namely we don't do partials and if a chord has multiple left/
 * right words we go with the most common of the two.
 *
 * Also note, All Combos _must_ be done through Command Mode! If you
 * use a combo enough add it to your dictionary in the USR section!
 *
 * Two 'layers' are avalible, CMD and USR. Just add these into a chord. 
 * You'll enter/exit these layers with SET_STICKY(CMD) and SET_STICKY(0)
 *
 * Note: The engine optimizes for the longest chord it can find, every
 * now and again this makes conflicts! If you have a better dictionary
 * or come up with improvements, please submit a PR!
 */

#define LANG en

#include QMK_KEYBOARD_H

enum aset_keys {
  AA    = 1,
  AS    = (1 << 1),
  AE    = (1 << 2),
  AT    = (1 << 3),
  AN    = (1 << 4),
  AI    = (1 << 5),
  AO    = (1 << 6),
  AP    = (1 << 7),
  ASFT  = (1 << 8),
  ASPC  = (1 << 9),
  NUM   = (1 << 10),
  USR   = (1 << 11),
  CMD   = (1 << 12),
  RIGHT = (1 << 13),
};

#define GN_KEY(k) GN_##k = (SAFE_RANGE + A##k)

enum custom_keycodes {
    GN_KEY(A),
    GN_KEY(S),
    GN_KEY(E),
    GN_KEY(T),
    GN_KEY(N),
    GN_KEY(I),
    GN_KEY(O),
    GN_KEY(P),
    GN_KEY(SFT),
    GN_KEY(SPC)
};

// Asetniop aliases, to Ginny Fingers

void send_shiftable_string(const char * str) {
    uint8_t temp_mods = get_mods();
    clear_mods();
    if(temp_mods & (MOD_LSFT | MOD_RSFT)) set_oneshot_mods(MOD_LSFT);
    send_string(str);
    set_mods(temp_mods);
}

uint16_t processChord(uint16_t c, bool test);

uint16_t pressed;
uint16_t chord;
uint16_t mode;
uint16_t repeat_timer;
bool repeated;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    bool pr = record->event.pressed;
    bool inChord = (pressed & 0xFF);
    if(keycode > SAFE_RANGE) {
        if(pr) {
            pressed |= (keycode-SAFE_RANGE);
        } else {
            pressed &= ~(keycode-SAFE_RANGE);
        }

        if(!inChord && pressed & 0xF0 ) {
           chord |= RIGHT;
        }

        chord |= pressed;

        clear_keyboard_but_mods();
        repeat_timer = timer_read();

        if(chord & ASFT) {
            set_mods(MOD_LSFT | get_mods());
        } else {
            set_mods(~MOD_LSFT & get_mods());
        }


        if (!(pressed & 0xFF) && chord && !pr) {
            if(!repeated) processChord((chord | mode) & ~(ASFT), false);
            clear_keyboard_but_mods();
            repeated = false;
            chord = 0;
        } 

        if(pressed & ASFT) {
            set_mods(MOD_LSFT | get_mods());
        } else {
            set_mods(~MOD_LSFT & get_mods());
        }


        if (!pressed) {
            clear_keyboard();
            repeated = false;
            chord = 0;
        }
        return false;
        
    }
    return true;
}

void matrix_scan_user(void) {
  if (chord) {
    if (timer_elapsed(repeat_timer) > 500 && !repeated) {
        processChord((chord | mode) & ~(ASFT), false);
        repeated = true;
    }
  }
}

void set_mode(uint16_t m) {
   mode = m;
}  

void noop(void){}

#define CH(code, macro) case code: if(!test) {macro;} return code;
#define CH_S(code, unshifted, shifted) case code: if(!test) {if(get_mods() & (MOD_LSFT | MOD_RSFT)) {shifted;} else {unshifted;}} return code;

uint16_t processChord(uint16_t c, bool test) {
#ifndef NO_DEBUG 
    if(c & AA) uprintf("A");
    else uprintf(" ");
    if(c & AS) uprintf("S");
    else uprintf(" ");
    if(c & AE) uprintf("E");
    else uprintf(" ");
    if(c & AT) uprintf("T");
    else uprintf(" ");
    if(c & AN) uprintf("N");
    else uprintf(" ");
    if(c & AI) uprintf("I");
    else uprintf(" ");
    if(c & AO) uprintf("O");
    else uprintf(" ");
    if(c & AP) uprintf("P");
    else uprintf(" ");

    if(c & ASFT) uprintf(" SHIFT");
    else uprintf("      ");
    if(c & ASPC) uprintf(" SPACE");
    else uprintf("      ");
    if(c & NUM) uprintf(" NUM");
    else uprintf("    ");
    uprintf("\n");
#endif

    switch(c) {
        CH  (AA,                                                          register_code(KC_A))
        CH  (AS,                                                          register_code(KC_S))
        CH  (AE,                                                          register_code(KC_E))
        CH  (AT,                                                          register_code(KC_T))
        CH  (AN,                                                          register_code(KC_N))
        CH  (AI,                                                          register_code(KC_I))
        CH  (AO,                                                          register_code(KC_O))
        CH  (AP,                                                          register_code(KC_P))
        CH  (AA | AS,                                                     register_code(KC_W))
        CH  (AA | AE,                                                     register_code(KC_X))
        CH  (AA | AT,                                                     register_code(KC_F))
        CH  (AA | AN,                                                     register_code(KC_Q))
        CH  (AA | AI,                                                     register_code(KC_Z))
        CH_S(AA | AO,                                                     register_code(KC_LSFT);register_code(KC_9), unregister_code(KC_LSFT);register_code(KC_LBRC))
        CH_S(AA | AP,                                                     register_code(KC_LSFT);register_code(KC_SLSH), unregister_code(KC_LSFT);register_code(KC_SLSH))
        CH  (AS | AE,                                                     register_code(KC_D))
        CH  (AS | AT,                                                     register_code(KC_C))
        CH  (AS | AN,                                                     register_code(KC_J))
        CH  (AS | AI,                                                     register_code(KC_K))
        CH  (AS | AO,                                                     register_code(KC_DOT))
        CH_S(AS | AP,                                                     register_code(KC_LSFT);register_code(KC_0), unregister_code(KC_LSFT);register_code(KC_RBRC))
        CH  (AE | AT,                                                     register_code(KC_R))
        CH  (AE | AN,                                                     register_code(KC_Y))
        CH  (AE | AI,                                                     register_code(KC_COMM))
        CH  (AE | AO,                                                     register_code(KC_MINS))
        CH  (AE | AP,                                                     register_code(KC_QUOT))
        CH  (AT | AN,                                                     register_code(KC_B))
        CH  (AT | AI,                                                     register_code(KC_V))
        CH  (AT | AO,                                                     register_code(KC_G))
        CH  (AT | AP,                                                     register_code(KC_BSPC))
        CH  (AN | AI,                                                     register_code(KC_H))
        CH  (AN | AO,                                                     register_code(KC_U))
        CH  (AN | AP,                                                     register_code(KC_M))
        CH  (AI | AO,                                                     register_code(KC_L))
        CH  (AI | AP,                                                     register_code(KC_LSFT);register_code(KC_1))
        CH  (AO | AP,                                                     register_code(KC_SCLN))
            
        CH  (ASPC,                                                        register_code(KC_SPC))
        CH  (AN | AI | AO | AP,                                           register_code(KC_ENT))
        CH  (AN | AS | AE | AT,                                           register_code(KC_TAB))

        CH  (AA | AS | AE | AT | ASPC,                                    send_shiftable_string("were "))
        CH  (AA | AS | AE | AT | AN | AI | AO | AP | ASPC,                send_shiftable_string("especially "))
        CH  (AA | AS | AE | AT | AN | AI | AO | AP | ASPC | RIGHT,        send_shiftable_string("himself "))
            
        CH  (AA | AT | AN | AP,                                           set_mode(NUM))
        CH  (AA | AT | AN | AP | NUM,                                     set_mode(0))
            
        CH  (AA | NUM,                                                    register_code(KC_1))
        CH  (AS | NUM,                                                    register_code(KC_2))
        CH  (AE | NUM,                                                    register_code(KC_3))
        CH  (AT | NUM,                                                    register_code(KC_4))
        CH  (AN | NUM,                                                    register_code(KC_7))
        CH  (AI | NUM,                                                    register_code(KC_8))
        CH  (AO | NUM,                                                    register_code(KC_9))
        CH  (AP | NUM,                                                    register_code(KC_0))
        CH  (AE | AT | NUM,                                               register_code(KC_5))
        CH  (AN | AI | NUM,                                               register_code(KC_6))
        CH  (AA | AN | NUM,                                               register_code(KC_GRV))
        CH  (AA | AI | NUM,                                               register_code(KC_BSLS))
        CH  (AT | AN | NUM,                                               register_code(KC_EQL))
        CH  (AA | AT | NUM,                                               register_code(KC_LSFT);register_code(KC_LBRC))
        CH  (AN | AP | NUM,                                               register_code(KC_LSFT);register_code(KC_RBRC))
        CH  (AA | AS | AE | AT | NUM,                                     register_code(KC_TAB))
    }

    if(c & RIGHT) {
#ifndef NO_DEBUG 
        uprintf("No right chord found, falling back\n");
#endif
        return processChord(c & ~(RIGHT), false);
    }
    if(c & ASPC) {                                                  
#ifndef NO_DEBUG 
        uprintf("No chord found with space, falling back\n");
#endif
        return processChord(c & ~(ASPC), false);
    }
    if(c & mode) {
#ifndef NO_DEBUG 
        uprintf("No chord found on mode, falling back\n");
#endif
        return processChord(c & ~(mode), false);
    }
    return 0;
}
#define LAYOUT( \
    A, S, E, T,  N, I, O, P, \
             L,  R \
) \
LAYOUT_ginny( GN_##A, GN_##S, GN_##E, GN_##T, GN_##L, GN_##R, GN_##N, GN_##I, GN_##O, GN_##P )

// QMK layout, Make all your changesw in processQwerty!
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT(
    A, S, E, T,  N, I, O, P,
           SFT,  SPC
)};

// Don't fuck with this, thanks.
size_t keymapsCount  = sizeof(keymaps)/sizeof(keymaps[0]);
