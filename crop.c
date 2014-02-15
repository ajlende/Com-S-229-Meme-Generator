#include "simp.h"

int main(int argc, char** argv) {

	FILE* infile;

	infile = fopen( argv[1], "rb" );

	if ( infile == 0 ) {
		printf("File %s failed to open!\n", argv[1]);
		return 1;
	}

	FILE* outfile;
	
	outfile = fopen( argv[2], "wb" );
	
	if ( outfile == 0 ) {
		printf("File %s failed to open!\n", argv[2]);
		fclose(infile);
		return 1;
	}

	fclose(infile);
	fclose(outfile);
	
	return 0;
}
