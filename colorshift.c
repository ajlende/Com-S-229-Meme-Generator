/*
 * colorshift.c
 * By Alex Lende
 *
 * The colorshift program performs an artistic color shift in the given image.
 *
 * Usage: colorshift pic.simp out.simp pattern
 *
 * The pattern should be one of the following strings:
 * RGB GBR BRG RBG BGR GRB RG GR RB BR GB BG
 * 
 * The pattern RGB says send Red to Green, Green to Blue, and Blue to Red.
 * The two-letter patterns swap two colors, such as RG to swap Red and Green,
 * while keeping Blue the same. 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "simp.h"

int main(int argc, char** argv) {

	FILE* infile;
	FILE* outfile;
	simp* simp_file;
	int i, j;

	/* Check to make sure there are the proper number of argumnets. */
	if (argc != 4) {
		printf("Invalid number of arguments!\n");
		return 1;
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


	/* Convert argv[3] (or at least the first three letters) to uppercase. */
	for (i = 0; argv[3][i] && i < 3; i++) {
		argv[3][i] = toupper((int)argv[3][i]);
	}


	/* Read the data from the infile into a simp data structure. */
	simp_file = (simp*) malloc(sizeof(simp));
	readSimp(simp_file, infile);


	/* Edit the photo here */
	if (!strcmp(argv[3], "RGB") || !strcmp(argv[3], "GBR") || !strcmp(argv[3], "BRG")) {
		for (i = 0; i < simp_file->height; i++) {
			for (j = 0; j < simp_file->width; j++) {
				unsigned char tmp = simp_file->data[i][j].r;
				simp_file->data[i][j].r = simp_file->data[i][j].b;
				simp_file->data[i][j].b = simp_file->data[i][j].g;
				simp_file->data[i][j].g = tmp;
			}
		}
	} else if (!strcmp(argv[3], "RBG") || !strcmp(argv[3], "BGR") || !strcmp(argv[3], "GRB")) {
		for (i = 0; i < simp_file->height; i++) {
			for (j = 0; j < simp_file->width; j++) {
				unsigned char tmp = simp_file->data[i][j].r;
				simp_file->data[i][j].r = simp_file->data[i][j].g;
				simp_file->data[i][j].g = simp_file->data[i][j].b;
				simp_file->data[i][j].b = tmp;
			}
		}
	} else if (!strcmp(argv[3], "RG") || !strcmp(argv[3], "GR")) {
		for (i = 0; i < simp_file->height; i++) {
			for (j = 0; j < simp_file->width; j++) {
				unsigned char tmp = simp_file->data[i][j].r;
				simp_file->data[i][j].r = simp_file->data[i][j].g;
				simp_file->data[i][j].g = tmp;
			}
		}
	} else if (!strcmp(argv[3], "RB") || !strcmp(argv[3], "BR")) {
		for (i = 0; i < simp_file->height; i++) {
			for (j = 0; j < simp_file->width; j++) {
				unsigned char tmp = simp_file->data[i][j].r;
				simp_file->data[i][j].r = simp_file->data[i][j].b;
				simp_file->data[i][j].b = tmp;
			}
		}
	} else if (!strcmp(argv[3], "GB") || !strcmp(argv[3], "BG")) {
		for (i = 0; i < simp_file->height; i++) {
			for (j = 0; j < simp_file->width; j++) {
				unsigned char tmp = simp_file->data[i][j].g;
				simp_file->data[i][j].g = simp_file->data[i][j].b;
				simp_file->data[i][j].b = tmp;
			}
		}
	} else {
		printf("Invalid argument %s\n", argv[3]);
		
		freeSimp(simp_file);
		
		free(simp_file);
		simp_file = 0;
		
		fclose(infile);
		fclose(outfile);
		
		return 1;
	}


	/* Write the image to the file and free simp data. */
	writeSimp(simp_file, outfile);
	free(simp_file);
	simp_file = 0;


	/* Close the files. */
	fclose(infile);
	fclose(outfile);
	
	return 0;
}

