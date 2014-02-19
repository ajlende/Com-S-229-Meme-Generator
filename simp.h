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
	unsigned int width;
	unsigned int height;
	pixel**  data;
} simp;

/*
 * Creates space for a new simp structure with the given width and height
 */
void initSimp(simp *simp_data, unsigned int width, unsigned int height);

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

#endif
