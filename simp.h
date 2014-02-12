#ifndef _SIMP_H_
#define _SIMP_H_

#include<stdint.h>
#include<stdio.h>

typedef struct pixel_s {
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
} pixel;

typedef struct simp_s {
	uint32_t   width;
	uint32_t   height;
	pixel** data;
} simp;

/*
 * Reads the simp file into a simp data structure
 */
simp readSimp(FILE *read_file) {
	simp image;
	return image;
}

/*
 * Writes the simp file after manipulation
 */
void writeSimp(FILE *write_file, simp *data) {
	return;
}

#endif
