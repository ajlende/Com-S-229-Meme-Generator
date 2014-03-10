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
void initFont(font* f, char* name) {
	
	/* The name of the font */
	f->name = name;

	/* Allocate space for all 128 possible ascii characters */
	/* This will make it much easier for looking up a specific character */
	/* Used calloc because not all characters may be present when reading the file, and the spaces for them will be left empty. */
	f->characters = (simp*) calloc(128 * sizeof(simp));
}

/* Frees the memory allocated for a font data structure. */
void freeFont(font* f) {
	int i;
	
	for (i = 0; i < 128; i++) {
		/* if there was a character at that position, then we can free the simp file that is there. */
		if (f->characters[i]) {
			freeSimp(f->characters[i]);
			f->characters[i] = 0;
		}
	}

	free(f->characters);
	f->characters = 0;
}

/* Loads simp images of each file into the font's simp character array */
size_t readFont(font* f, FILE* font_simp, FILE* fsf_file) {
		
}

