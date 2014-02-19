/*
 * bw.c
 * By Alex Lende
 *
 * The bw program converts an image to black and white.
 *
 * Usage: bw pic.simp out.simp
 * 
 * Each pixel is converted to black and white by averaging the Red, Green,
 * and Blue values and then setting each color channel to that averaged value.
 */

#include <stdlib.h>
#include <stdio.h>
#include "simp.h"

int main(int argc, char** argv) {
	
	FILE* infile;
	FILE* outfile;
	simp* simp_file;
	int i, j;



	/* TODO: Remove these two variables */
	size_t size_read, size_written;



	/* Check to make sure there are the proper number of argumnets. */
	if (argc != 3) {
		printf("Invalid number of arguments!\n");
		return 1;
	}


	/* Open the files. If one fails to open, then exit and return 1. */
	infile = fopen( argv[1], "rb" );

	if (infile == 0) {
		printf("File '%s' failed to open!\n", argv[1]);
		return 1;
	}
	
	outfile = fopen( argv[2], "wb" );
	
	if (outfile == 0) {
		printf("File '%s' failed to open!\n", argv[2]);
		fclose(infile);
		return 1;
	}


	/* Read the data from the infile into a simp data structure. */
	simp_file = (simp*) malloc(sizeof(simp));
	size_read = readSimp(simp_file, infile);


	printf("size_read: %u", size_read);


	/* Edit the photo here */
	for (i = 0; i < simp_file->height; i++) {
		for (j = 0; j < simp_file->width; j++) {
			
			unsigned char avg;
			avg = ((simp_file->data[i][j].r) + (simp_file->data[i][j].g) + (simp_file->data[i][j].b)) / 3;
			
			simp_file->data[i][j].r = avg;
			simp_file->data[i][j].g = avg;
			simp_file->data[i][j].b = avg;
		}	
	}


	/* Write the image to the file and free simp data. */
	size_written = writeSimp(simp_file, outfile);
	free(simp_file);
	simp_file = 0;


	printf("size_written: %u", size_written);

	
	/* Close the files. */
	fclose(infile);
	fclose(outfile);

	return 0;
}
