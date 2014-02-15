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
	uint32_t width;
	uint32_t height;
	pixel**  data;
} simp;

/*
 * Reads the simp file into a simp data structure, and returns the number of bytes read from the file.
 */
size_t readSimp(simp *simp_data, FILE *read_file);

/*
 * Writes data from a simp data structure to a simp file and returns the number of bytes written to the file.
 */
size_t writeSimp(simp *simp_data, FILE *write_file);

/*
 * Frees the memory allocated for a simp data structure.
 */
void freeSimp(simp *simp_data);

#endif
