#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "simp.h"

int main(int argc, char** argv) {

	FILE* infile;
	FILE* outfile;
	simp* simp_file;
	int i, j;

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
	} else if (!strcmp(argv[3], "RGB") || !strcmp(argv[3], "GBR") || !strcmp(argv[3], "BRG")) {
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
		printf("Invalid argument %s", argv[3]);
		freeSimp(simp_file);
		free(simp_file);
		fclose(infile);
		fclose(outfile);
		return 1;
	}

	writeSimp(simp_file, outfile);

	free(simp_file);

	fclose(infile);
	fclose(outfile);
	
	return 0;
}

