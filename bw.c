#include <stdlib.h>
#include <stdio.h>
#include "simp.h"

int main(int argc, char** argv) {
	
	FILE* infile;
	FILE* outfile;
	simp* simp_file;
	
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

	writeSimp(simp_file, outfile);

	freeSimp(simp_file);

	free(simp_file);

	fclose(infile);
	fclose(outfile);

	return 0;
}
