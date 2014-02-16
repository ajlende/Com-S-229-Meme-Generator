#include "simp.h"

/* TODO: Remove this include. */
#include <stdio.h>

/*
 * Reads the simp file into a simp data structure, and returns the number of bytes read from the file.
 */
size_t readSimp(simp *simp_data, FILE *read_file) {
	
	size_t size_read;
	int i;

	size_read = 0;
	
	size_read += fread(&(simp_data->width),  sizeof(int), 1, read_file) * sizeof(int);
	size_read += fread(&(simp_data->height), sizeof(int), 1, read_file) * sizeof(int);
	
	printf("read width: %d\nread height: %d\n", simp_data->width, simp_data->height);
	
	simp_data->data = (pixel**) malloc(simp_data->height * sizeof(pixel*));

	for (i = 0; i < simp_data->height; i++) {
		simp_data->data[i] = (pixel*) malloc(simp_data->width * sizeof(pixel));
	}

	/* TODO: actually read the data */
	for (i = 0; i < simp_data->height; i++) {
		size_read += fread(simp_data->data[i], sizeof(pixel), simp_data->width, read_file) * sizeof(pixel);
	}

	return size_read;
}

/*
 * Writes data from a simp data structure to a simp file and returns the number of bytes written to the file.
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

	return size_written;
}

/*
 * Frees the data malloc'd for the simp data structure in 
 */
void freeSimp(simp *simp_data) {

	for (i = 0; i < simp_data->height; i++) {
		free(simp_data->data[i]);
	}
	
	free(simp_data->data);

}
