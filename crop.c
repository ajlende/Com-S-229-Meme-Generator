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

	x = atoi(argv[3]);
	y = atoi(argv[4]);
	w = atoi(argv[5]);
	h = atoi(argv[6]);

	simp_in = (simp*) malloc(sizeof(simp));
	
	readSimp(simp_in, infile);
	
	simp_out = (simp*) malloc(sizeof(simp));

	initSimp(simp_out, w, h);

	for (i = 0; i < h; i++) {
		for (j = 0; j < w; j++) {
			simp_out->data[i][j] = simp_in->data[i+y][j+x];
		}
	}

	writeSimp(simp_out, outfile);

	freeSimp(simp_in);

	free(simp_out);

	free(simp_in);

	fclose(infile);
	fclose(outfile);
	
	return 0;
}
