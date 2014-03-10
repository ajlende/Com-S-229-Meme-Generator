/*
 * font.c
 * By Alex Lende
 * 
 * The font.c file contains the function definitions from the font.h file.
 */

#include <stdlib.h>
#include <stdio.h>
#include "simp.h"
#include "font.h"

/* Creates space for a new font structure TODO: finish description */
void initFont(font* f) {
	/* Allocate space for all 128 possible ascii characters */
	/* This will make it much easier for looking up a specific character */
	f->characters = (simp*) malloc(128 * sizeof(simp));
}

/* Frees the memory allocated for a font data structure. */
void freeFont(font* f) {
	free(f->characters);
	f->characters = 0;
}

/* Loads simp images of each file into the font's simp character array */
size_t readFont(font* f, FILE* font_simp, FILE* fsf_file) {
	
}

