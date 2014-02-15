#include "simp.h"

/* TODO: Remove this include. */
#include <stdio.h>

/*
 * Reads the simp file into a simp data structure, and returns the number of bytes read from the file.
 */
size_t readSimp(simp *simp_data, FILE *read_file) {
	
	size_t size_read;
	
	size_read = 0;
	
	size_read += fread(simp_data->width,  sizeof(int), 1, read_file) * sizeof(int);
	size_read += fread(simp_data->height, sizeof(int), 1, read_file) * sizeof(int);
	
	printf("read width: %d\nread height: %d\n", simp_data->width, simp_data->height);
	
	/*
	while (!feof(read_file)) {
		// read the image part of the file
	}
	*/

	return size_read;
}

/*
 * Writes data from a simp data structure to a simp file and returns the number of bytes written to the file.
 */
size_t writeSimp(simp *simp_data, FILE *write_file) {
	size_t size_written = 0;
	return size_written;
}

void freeSimp(simp *simp_data) {
	
}
