/*
 * meme.c
 */

#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include "meme.h"
#include "font.h"
#include "simp.h"

int main (int argc, char** argv) {

	FILE* meme_file;
	FILE* action_file;
	char* line;
	size_t line_size = 0;


	/* Check to make sure there are the proper number of argumnets. */
	if (argc != 3 ) {
		printf("Invalid number of arguments!\n");
		return 1;
	}

	
	/* Open the files for reading. If one fails to open, then exit and return 1. */
	meme_file = fopen( argv[1], "r" );

	if ( meme_file == 0 ) {
		printf("File %s failed to open!\n", argv[1]);
		return 1;
	}
	
	action_file = fopen( argv[2], "r" );

	if ( action_file == 0 ) {
		printf("File %s failed to open!\n", argv[2]);
		return 1;
	}


	/* Read through the act file */
	while (getline(&line, &line_size, action_file) != -1) {
		printf("String: %sline_size: %zu\n", line, line_size);
	}

	/* Read thoough the mem file */
	while (getline(&line, &line_size, meme_file) != -1) {
		printf("String: %sline_size: %zu\n", line, line_size);
	}

	/* Read through the fsf file */

	


	/* cleanup */
	free(line);
	line = 0;

	fclose(meme_file);
	fclose(action_file);

	return 0;
}
