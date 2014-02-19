/*
 * simp.c
 * By Alex Lende
 * 
 * The simp.c file contains all of the function bodies
 * for the function prototypes in simp.h.
 *
 * The functions below relate to reading and writing of
 * the simp file type.
 */

#include <stdlib.h>
#include <stdio.h>
#include "simp.h"

/*
 * Creates space for the data of a simp structure with the given width and height.
 */
void initSimp(simp *simp_data, unsigned int width, unsigned int height) {

	int i;

	simp_data->width = width;
	simp_data->height = height;

	simp_data->data = (pixel**) malloc(height * sizeof(pixel*));

	for (i = 0; i < simp_data->height; i++) {
		simp_data->data[i] = (pixel*) malloc(width * sizeof(pixel));
	}
}


/*
 * Frees the data malloc'd for the simp data.
 */
void freeSimp(simp *simp_data) {

	int i;

	for (i = 0; i < simp_data->height; i++) {
		free(simp_data->data[i]);
		simp_data->data[i] = 0;
	}
	
	free(simp_data->data);
	simp_data->data = 0;
}


/*
 * Allocates space for the data part of a simp data structure. Reads the simp file
 * into the structure. Returns the number of bytes read from the file or zero if
 * the file was unable to be read correctly. (i.e. The width and height read from 
 * the file don't match up with the size of the rest of the file.)
 */
size_t readSimp(simp *simp_data, FILE *read_file) {
	
	size_t size_read, file_size;
	int i;
	unsigned int width, height;

	/* Read the number of bytes in the file */
	fseek(read_file, 0, SEEK_END);
	file_size = ftell(read_file);
	fseek(read_file, 0, SEEK_SET);

	/* Initialize size_read. */
	size_read = 0;
	
	/* Read the first two 32-bit integers into the width and height and count the number of bytes read. */
	size_read += fread(&width,  sizeof(int), 1, read_file) * sizeof(int);
	size_read += fread(&height, sizeof(int), 1, read_file) * sizeof(int);

	printf("WIDTH (s): %d\n", width);
	printf("WIDTH (u): %u\n", width);
	printf("HEIGHT (s): %d\n", height);
	printf("HEIGHT (u): %u\n", height);


	/* The expected size of the file is the size of the two 32-bit ints that were already read and the sum of all the pixels. */
	/* If the expected size is not the same as the actual size, then the file is incorrect. */
	if (file_size != ((width * height * sizeof(pixel)) + (2 * sizeof(int)))) return 0;

	/* Initialize the width and height of the simp struct and malloc space for the pixels. */
	initSimp(simp_data, width, height);

	/* Read in all of the pixels. */
	for (i = 0; i < simp_data->height; i++) {
		size_read += fread(simp_data->data[i], sizeof(pixel), simp_data->width, read_file) * sizeof(pixel);
	}

	return size_read;
}


/*
 * Writes data from a simp data structure to a simp file. Frees the space allocated for the data. Returns the number of bytes written to the file.
 */
size_t writeSimp(simp *simp_data, FILE *write_file) {

	size_t size_written;
	int i;

	size_written = 0;

	size_written += fwrite(&(simp_data->width), sizeof(int), 1, write_file) * sizeof(int);
	size_written += fwrite(&(simp_data->height), sizeof(int), 1, write_file) * sizeof(int);

	for (i = 0; i < simp_data->height; i++) {
		size_written += fwrite(simp_data->data[i], sizeof(pixel), simp_data->width, write_file) * sizeof(pixel);
	}

	freeSimp(simp_data);

	return size_written;
}
