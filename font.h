/*
 * font.h
 * By Alex Lende
 * 
 * The font.h file contains the type definitions for the font and letter data structures as well as the function prototypes that are defined in font.c
 */

#ifndef _FONT_H_
#define _FONT_H_

#include "simp.h"

typedef struct font_s {
	char* name;
	simp** characters;
} font;

/*
 * Creates space for a new font structure TODO: finish description
 */
void initFont();

/*
 * Frees the memory allocated for a simp data structure.
 */
void freeFont();

/*
 * Reads the font int the font structure
 */
size_t readFont();

#endif
