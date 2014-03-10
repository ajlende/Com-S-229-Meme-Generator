/*
 * overlay.c
 * By Alex Lende
 *
 * The overlay program takes two images and places one on top of the other.
 * 
 * Usage: overlay pic1.simp pic2.simp out.simp x y
 * 
 * Overlay creates a new image given by drawing the second picture on top of 
 * the first picture using a translation such that the top-left corner of pic2
 * is at the position (x, y) inside pic1.
 */

#include <stdlib.h>
#include <stdio.h>
#include "simp.h"

int main(int argc, char** argv) {

	FILE* infile_bottom;
	FILE* infile_top;
	FILE* outfile;
	simp* simp_bottom;
	simp* simp_top;
	int x, y;
	int i, j;
	size_t size_read_bottom, size_read_top, size_written;

	/* Check to make sure there are the proper number of argumnets. */
	if (argc != 6 ) {
		printf("Invalid number of arguments!\n");
		return 1;
	}


	/* Read the values of x and y. If either is not an integer, then exit and return 1. */
	if (sscanf(argv[4], "%d", &x) != 1) {
		printf("Invalid argument '%s' must be a positive integer!\n", argv[4]);
		return 1;
	}

	if (sscanf(argv[5], "%d", &y) != 1) {
		printf("Invalid argument '%s' must be a positive integer!\n", argv[5]);
		return 1;
	}


	/* Open the files for reading. If one fails to open, then exit and return 1. */
	infile_bottom = fopen( argv[1], "rb" );

	if ( infile_bottom == 0 ) {
		printf("File %s failed to open!\n", argv[1]);
		return 1;
	}

	infile_top = fopen( argv[2], "rb" );
	
	if ( infile_top == 0 ) {
		printf("File %s failed to open!\n", argv[2]);
		fclose(infile_bottom);
		return 1;
	}
	

	/* Read the two simp files into data structures. */
	simp_bottom = (simp*) malloc(sizeof(simp));
	simp_top = (simp*) malloc(sizeof(simp));
	size_read_bottom = readSimp(simp_bottom, infile_bottom);
	size_read_top = readSimp(simp_top, infile_top);


	/* readSimp() returns zero if there was an error. */
	if (!size_read_bottom || !size_read_top) {
		printf("The file was unable to be read! The filetype may be incorrect or the file may be corrupted.\n");
		
		freeSimp(simp_bottom);
		freeSimp(simp_top);

		free(simp_bottom);
		simp_bottom = 0;

		free(simp_top);
		simp_top = 0;

		fclose(infile_bottom);
		fclose(infile_top);

		return 1;
	}


	/* overlay the new image */
	overlay(simp_top, simp_bottom, x, y);


	/* Open the file to write to. If it fails to open, then exit and return 1. */
	outfile = fopen( argv[3], "wb" );
	
	if ( outfile == 0 ) {
		
		printf("File %s failed to open!\n", argv[3]);
		
		freeSimp(simp_bottom);
		freeSimp(simp_top);

		free(simp_bottom);
		simp_bottom = 0;

		free(simp_top);
		simp_top = 0;

		fclose(infile_bottom);
		fclose(infile_top);

		return 1;
	}


	/* Write the image to the file and free the data part of each simp struct. */
	/* NOTE: writeSimp(simp_bottom, outfile) automatically frees simp_bottom->data, but simp_top->data still needs to be freed using freeSimp(simp_top). */
	size_written = writeSimp(simp_bottom, outfile);
	freeSimp(simp_top);


	/* Free the space allocated for the simp structures. */
	free(simp_bottom);
	simp_bottom = 0;

	free(simp_top);
	simp_top = 0;


	/* Close the files. */
	fclose(infile_bottom);
	fclose(infile_top);
	fclose(outfile);
	
	return 0;
}

