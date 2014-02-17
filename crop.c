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


	/* Check to make sure there are the proper number of argumnets. */
	if (argc != 7) {
		printf("Invalid number of arguments!\n");
		return 1;
	}


	/* Read the values of x, y, w, and h. If any is not an integer, then exit and return 1. */
	if (sscanf(argv[3], "%u", &x) != 1) {
		printf("Invalid argument %s must be an integer!\n", argv[3]);
		return 1;
	}

	if (sscanf(argv[4], "%u", &y) != 1) {
		printf("Invalid argument %s must be an integer!\n", argv[4]);
		return 1;
	}

	if (sscanf(argv[5], "%u", &w) != 1) {
		printf("Invalid argument %s must be an integer!\n", argv[5]);
		return 1;
	}

	if (sscanf(argv[6], "%u", &h) != 1) {
		printf("Invalid argument %s must be an integer!\n", argv[6]);
		return 1;
	}


	/* Make sure that all integers read were not negative. */
	for (i = 3; i < argc; i++) {
		if (argv[i][0] == '-') {
			printf("Invalid argument %s must be positive!\n", argv[i]);
			return 1;
		}
	}


	/* Open the files. If one fails to open, then exit and return 1. */
	infile = fopen( argv[1], "rb" );

	if ( infile == 0 ) {
		printf("File %s failed to open!\n", argv[1]);
		return 1;
	}
	
	outfile = fopen( argv[2], "wb" );
	
	if ( outfile == 0 ) {
		printf("File %s failed to open!\n", argv[2]);
		fclose(infile);
		return 1;
	}


	/* Read the data from the infile into a simp data structure. */
	simp_in = (simp*) malloc(sizeof(simp));	
	readSimp(simp_in, infile);

	
	/* Make sure that the width and height to crop to are within the size of the image. */
	/* Also, make sure that the x and y coordinates are within the bounds of the image. */
	if ((x+w) > simp_in->width || (y+h) > simp_in->height) {
		printf("Width or height is too large or x, y coordinates are out of range!\n");
		freeSimp(simp_in);
		free(simp_in);
		simp_in = 0;
		fclose(infile);
		fclose(outfile);
		return 1;
	}

	
	/* Prepare space for the cropped image. */
	simp_out = (simp*) malloc(sizeof(simp));
	initSimp(simp_out, w, h);


	/* Copy the cropped area of the image into the new structure. */
	for (i = 0; i < h; i++) {
		for (j = 0; j < w; j++) {
			simp_out->data[i][j] = simp_in->data[i+y][j+x];
		}
	}

	
	/* Write the image to the file and free the data part of each simp struct. */
	/* NOTE: writeSimp(simp_out, outfile) automatically frees simp_out->data, but simp_in->data still needs to be freed using freeSimp(simp_in). */
	writeSimp(simp_out, outfile);
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
