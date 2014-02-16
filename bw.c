#include <stdlib.h>
#include <stdio.h>
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
	for (i = 0; i < simp_file->height; i++) {
		for (j = 0; j < simp_file->width; j++) {
			
			unsigned char avg;
			avg = ((simp_file->data[i][j].r) + (simp_file->data[i][j].g) + (simp_file->data[i][j].b)) / 3;
			
			simp_file->data[i][j].r = avg;
			simp_file->data[i][j].g = avg;
			simp_file->data[i][j].b = avg;
		}	
	}

	writeSimp(simp_file, outfile);

	free(simp_file);

	fclose(infile);
	fclose(outfile);

	return 0;
}
