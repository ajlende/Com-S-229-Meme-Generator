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
 * Allocates space for the data part of a simp data structure. Reads the simp file into the structure. Returns the number of bytes read from the file.
 */
size_t readSimp(simp *simp_data, FILE *read_file) {
	
	size_t size_read;
	int i;
	unsigned int width, height;

	size_read = 0;
	
	size_read += fread(&width,  sizeof(int), 1, read_file) * sizeof(int);
	size_read += fread(&height, sizeof(int), 1, read_file) * sizeof(int);

	initSimp(simp_data, width, height);

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
