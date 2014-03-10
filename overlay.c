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
	unsigned int x, y;
	int i, j;
	size_t size_read_bottom, size_read_top, size_written;

	/* Check to make sure there are the proper number of argumnets. */
	if (argc != 6 ) {
		printf("Invalid number of arguments!\n");
		return 1;
	}


	/* Read the values of x and y. If either is not a positive integer, then exit and return 1. */
/*	if (argv[4][0] == '-' || sscanf(argv[4], "%u", &x) != 1) {
		printf("Invalid argument '%s' must be a positive integer!\n", argv[4]);
		return 1;
	}

	if (argv[5][0] == '-' || sscanf(argv[5], "%u", &y) != 1) {
		printf("Invalid argument '%s' must be a positive integer!\n", argv[5]);
		return 1;
	}
*/

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


	/* Make sure that the width and height to overlay to are within the size of the bottom image. */
	/* Also, make sure that the x and y coordinates are within the bounds of the bottom image. */
/*	if ((x + simp_top->width) > simp_bottom->width || (y + simp_top->height) > simp_bottom->height) {
		
		printf("X or y coordinates are out of range!\n");
		
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
*/



	/* Edit the photo here */
/*	for (i = 0; i < simp_top->height; i++) {
		for (j = 0; j < simp_top->width; j++) {

			unsigned char r1, g1, b1, a1, r2, g2, b2, a2;
			
			r1 = simp_bottom->data[i+y][j+x].r;
			g1 = simp_bottom->data[i+y][j+x].g;
			b1 = simp_bottom->data[i+y][j+x].b;
			a1 = simp_bottom->data[i+y][j+x].a;

			r2 = simp_top->data[i][j].r;
			g2 = simp_top->data[i][j].g;
			b2 = simp_top->data[i][j].b;
			a2 = simp_top->data[i][j].a;

			if (a2 == 0xFF) {
				simp_bottom->data[i+y][j+x].r = r2;
            	simp_bottom->data[i+y][j+x].g = g2;
            	simp_bottom->data[i+y][j+x].b = b2;
				simp_bottom->data[i+y][j+x].a = a2;
			} else {
				simp_bottom->data[i+y][j+x].r = ((a2*r2)/0xFF)+((r1*a1*(0xFF-a2))/(0xFF*0xFF));
				simp_bottom->data[i+y][j+x].g = ((a2*g2)/0xFF)+((g1*a1*(0xFF-a2))/(0xFF*0xFF));
				simp_bottom->data[i+y][j+x].b = ((a2*b2)/0xFF)+((b1*a1*(0xFF-a2))/(0xFF*0xFF));
				simp_bottom->data[i+y][j+x].a = (((0xFF*(a1+a2))-(a1*a2))/0xFF);
			}
		}
	}
*/


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

