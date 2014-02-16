#include <stdlib.h>
#include <stdio.h>
#include "simp.h"

int main(int argc, char** argv) {

	FILE* infile;
	FILE* outfile;
	simp* simp_file;
	int x, y, w, h, i;

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

	printf("Opened files...\n");

	x = atoi(argv[3]);
	y = atoi(argv[4]);
	w = atoi(argv[5]);
	h = atoi(argv[6]);

	printf("Assigned x, y, w, h...\n");

	simp_file = (simp*) malloc(sizeof(simp));

	readSimp(simp_file, infile);

	printf("Read SIMP file...\n");

	/* Adjust the width and height */
	simp_file->width = w;
	simp_file->height = h;

	printf("Set simp_file width and height...\n");

	printf("Info: simp_file->data: %X...\n", simp_file->data);
	
	/* move the pointer to the new top of the image */
	simp_file->data += y;

	printf("Moved simp_file to: %X...\n", simp_file->data);

	/* move each pointer that we are dealing with to the new left edge of the image */
	for (i = 0; i < simp_file->height; i++) {
		simp_file->data[i] += x;
	}

	printf("Moved simp_file->data[i]...\n")

	writeSimp(simp_file, outfile);

	free(simp_file);

	fclose(infile);
	fclose(outfile);
	
	return 0;
}
