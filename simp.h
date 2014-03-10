/* 
 * simp.h
 * By Alex Lende
 * 
 * The simp.h header file contains the type definitions for the
 * simp and pixel data structure as well as the function prototypes
 * that are defined in simp.c
 */

#ifndef _SIMP_H_
#define _SIMP_H_

#include <stdio.h>

typedef struct pixel_s {
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
} pixel;

typedef struct simp_s {
	int width;
	int height;
	pixel**  data;
} simp;

/*
 * Creates space for a new simp structure with the given width and height
 */
void initSimp(simp *simp_data, int width, int height);

/*
 * Frees the memory allocated for a simp data structure.
 */
void freeSimp(simp *simp_data);

/*
 * Reads the simp file into a simp data structure, and returns the number 
 * of bytes read from the file or zero if the file could not be read
 * correctly.
 */
size_t readSimp(simp *simp_data, FILE *read_file);

/*
 * Writes data from a simp data structure to a simp file and returns the number of bytes written to the file.
 */
size_t writeSimp(simp *simp_data, FILE *write_file);

/*
 * Makes all pixels in simp_data grayscale by averaging the R, G, and B values.
 */
void bw(simp* simp_data);

/*
 * Swaps the R, G, and B values of all pixels in simp_data using the given pattern.
 */
void colorshift(simp* simp_data, char* pattern);

/*
 * Copies the pixels from simp_in to simp_out that are within the given x, y, w, and h bounds
 */
int crop(simp* simp_in, simp* simp_out, int x, int y, int w, int h);

/* 
 * Overlays the pixels from simp_top onto the pixels of simp_bottom, calculating the transparencies
 */
int overlay(simp* simp_top, simp* simp_bottom, int x, int y);

#endif
