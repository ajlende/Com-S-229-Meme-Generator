/*
 * font.h
 * By Alex Lende
 * 
 * The font.h file contains the type definitions for the font and letter data 
 * structures as well as the function prototypes that are defined in font.c
 */

#ifndef _FONT_H_
#define _FONT_H_

#include "simp.h"

typedef struct font_s {
	char* name;
	simp** characters;
} font;

/*
 * Creates space for a new font structure
 */
void initFont();

/*
 * Frees the memory allocated for a simp data structure.
 */
void freeFont();

/*
 * Prints the information for a single character to the console.
 */
void printCharacter(font* f, char idx, int x, int y);

#endif
