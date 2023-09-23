#pragma once

#include "quantum.h"

#define XXX KC_NO

#define LAYOUT( \
    LA1, LA2, LA3, LA4, LA5, LA6,           	RA6, RA5, RA4, RA3, RA2, RA1, \
    LB1, LB2, LB3, LB4, LB5, LB6,           	RB6, RB5, RB4, RB3, RB2, RB1, \
    LC1, LC2, LC3, LC4, LC5, LC6, LC7,          RC6, RC5, RC4, RC3, RC2, RC1, \
    LD1, LD2, LD3, LD4, LD5, LD6, 	 RE6, RD6, RD5, RD4, RD3, RD2, RD1, \
    LE1,                LE5, LE6, LE7, 	 RE5, RE4, RE3 \
    ) \
    { \
        { LA1, LA2, LA3, LA4, LA5, LA6, XXX }, \
        { LB1, LB2, LB3, LB4, LB5, LB6, XXX }, \
        { LC1, LC2, LC3, LC4, LC5, LC6, LC7 }, \
        { LD1, LD2, LD3, LD4, LD5, LD6, XXX }, \
        { LE1, XXX, XXX, XXX, LE5, LE6, LE7 }, \
        { RA1, RA2, RA3, RA4, RA5, RA6, XXX}, \
        { RB1, RB2, RB3, RB4, RB5, RB6, XXX}, \
        { RC1, RC2, RC3, RC4, RC5, RC6, XXX }, \
        { RD1, RD2, RD3, RD4, RD5, RD6, XXX }, \
        { XXX, XXX, RE3, RE4, RE5, RE6, XXX } \
    }
