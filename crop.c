/*
 * crop.c
 * By Alex Lende
 *
 * The crop program performs a crop operation on an image, selecting a smaller portion to create a smaller image.
 * 
 * Usage: crop picture.simp out.simp x y w h
 * 
 * Overlay creates a new image given by drawing the second picture on top of 
 * the first picture using a translation such that the top-left corner of pic2
 * is at the position (x, y) inside pic1.
 */


#include <stdlib.h>
#include <stdio.h>
#include "simp.h"

int main(int argc, char** argv) {

	FILE* infile;
	FILE* outfile;
	simp* simp_in;
	simp* simp_out;
	unsigned int x, y, w, h;
	int i, j;
	size_t size_read, size_written;


	/* Check to make sure there are the proper number of argumnets. */
	if (argc != 7) {
		printf("Invalid number of arguments!\n");
		return 1;
	}


	/* Read the values of x, y, w, and h. If any is not an integer, then exit and return 1. */
	if (sscanf(argv[3], "%d", &x) != 1) {
		printf("Invalid argument '%s' must be an integer!\n", argv[3]);
		return 1;
	}

	if (sscanf(argv[4], "%d", &y) != 1) {
		printf("Invalid argument '%s' must be an integer!\n", argv[4]);
		return 1;
	}

	if (sscanf(argv[5], "%d", &w) != 1) {
		printf("Invalid argument '%s' must be an integer!\n", argv[5]);
		return 1;
	}

	if (sscanf(argv[6], "%d", &h) != 1) {
		printf("Invalid argument '%s' must be an integer!\n", argv[6]);
		return 1;
	}


	/* Open the file to read. If one fails to open, then exit and return 1. */
	infile = fopen( argv[1], "rb" );

	if (infile == 0) {
		printf("File '%s' failed to open!\n", argv[1]);
		return 1;
	}
	

	/* Read the data from the infile into a simp data structure. */
	simp_in = (simp*) malloc(sizeof(simp));	
	size_read = readSimp(simp_in, infile);


	/* readSimp() returns zero if there was an error. */
	if (!size_read) {

		printf("The file was unable to be read! The filetype may be incorrect or the file may be corrupted.\n");
		
		freeSimp(simp_in);
		
		free(simp_in);
		simp_in = 0;
		
		fclose(infile);

		return 1;
	}


	/* Prepare space for the cropped image. */
	simp_out = (simp*) malloc(sizeof(simp));
	initSimp(simp_out, w, h);


	/* Crop the image here! */
	crop(simp_in, simp_out, x, y, w, h);


	/* Open the file to read. If it fails to open, then exit and return 1. */
	outfile = fopen( argv[2], "wb" );


	if (outfile == 0) {
		printf("File '%s' failed to open!\n", argv[2]);

		freeSimp(simp_in);
		freeSimp(simp_out);
		
		free(simp_in);
		simp_in = 0;

		free(simp_out);
		simp_out = 0;
		
		fclose(infile);

		return 1;
	}

	
	/* Write the image to the file and free the data part of each simp struct. */
	/* NOTE: writeSimp(simp_out, outfile) automatically frees simp_out->data, but simp_in->data still needs to be freed using freeSimp(simp_in). */
	size_written = writeSimp(simp_out, outfile);
	freeSimp(simp_in);


	/* Free the space allocated for the simp structures. */
	free(simp_out);
	simp_out = 0;

	free(simp_in);
	simp_in = 0;


	/* Close the files. */
	fclose(infile);
	fclose(outfile);
	
	return 0;
}
