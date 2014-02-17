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
	
	outfile = fopen( argv[3], "wb" );
	
	if ( outfile == 0 ) {
		printf("File %s failed to open!\n", argv[3]);
		fclose(infile_bottom);
		fclose(infile_top);
		return 1;
	}

	x = atoi(argv[4]);
	y = atoi(argv[5]);

	simp_bottom = (simp*) malloc(sizeof(simp));
	simp_top = (simp*) malloc(sizeof(simp));

	readSimp(simp_bottom, infile_bottom);
	readSimp(simp_top, infile_top);

	/* Edit the photo here */
	for (i = 0; i < simp_top->height; i++) {
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

			simp_bottom->data[i+y][j+x].r = ((a2*r2)/255)+((r1*a1*(255-a2))/(255*255));
			simp_bottom->data[i+y][j+x].g = ((a2*g2)/255)+((g1*a1*(255-a2))/(255*255));
			simp_bottom->data[i+y][j+x].b = ((a2*b2)/255)+((b1*a1*(255-a2))/(255*255));
			simp_bottom->data[i+y][j+x].a = 255*((a2/255)+((a1*(255-a2))/(255*255)));
		}
	}

	writeSimp(simp_bottom, outfile);

	freeSimp(simp_top);

	free(simp_bottom);
	free(simp_top);

	fclose(infile_bottom);
	fclose(infile_top);
	fclose(outfile);
	
	return 0;
}

