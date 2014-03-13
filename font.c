/*
 * font.c
 * By Alex Lende
 * 
 * The font.c file contains the function definitions from the font.h file.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "simp.h"
#include "font.h"

/* Creates space for a new font structure TODO: finish description */
void initFont(font* f, char* name) {
	
	/* The name of the font */
	f->name = (char*) malloc(strlen(name) + 1);
	strcpy(f->name, name);

	/* Allocate space for all 128 possible ascii characters */
	/* This will make it much easier for looking up a specific character */
	/* Used calloc because not all characters may be present when reading the file, and the spaces for them will be left empty. */
	f->characters = (simp**) calloc(128, sizeof(simp*));
}

void addCharacter(simp* s, font* f, char idx, int x, int y, int w, int h) {
	f->characters[idx] = (simp*) malloc(sizeof(simp));
	initSimp(f->characters[idx], w, h);
	crop(s, f->characters[idx], x, y, w, h);
}

void printCharacter(font* f, char idx, int x, int y) {
	printf("<== CHARACTER ==>\n");
	printf("char: %c\n", idx);
	printf("x: %d\n", x);
	printf("y: %d\n", y);
	printf("w: %d\n", f->characters[idx]->width);
	printf("h: %d\n", f->characters[idx]->height);
	printf("<===============>\n");

}

/* Frees the memory allocated for a font data structure. */
void freeFont(font* f) {
	int i;

	if (!f->name) return;

	free(f->name);
	f->name = 0;

	if (!f->characters) return;

	for (i = 0; i < 128; i++) {
		if (f->characters[i] != 0) {
			freeSimp(f->characters[i]);
			free(f->characters[i]);
			f->characters[i] = 0;
		}
	}

	free(f->characters);
	f->characters = 0;
}


