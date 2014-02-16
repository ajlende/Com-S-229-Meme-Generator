#include <stdlib.h>
#include <stdio.h>
#include "simp.h"

int main(int argc, char** argv) {
	
	FILE* infile;
	FILE* outfile;
	simp* simp_file;

	size_t size_read;
	size_t size_written;
	
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

	size_read = readSimp(simp_file, infile);

	printf("read width: %d\nread height: %d\n", simp_file->width, simp_file->height);

	size_written = writeSimp(simp_file, outfile);

	printf("filein size: %zu", size_read);
	printf("fileout size: %zu", size_written);

	freeSimp(simp_file);

	free(simp_file);

	fclose(infile);
	fclose(outfile);

	return 0;
}
