/*
 * meme.c
 */

#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include "memelib.h"
#include "font.h"
#include "simp.h"

int main (int argc, char** argv) {

	FILE* meme_file;
	FILE* action_file;
	FILE* font_file;
	FILE* outfile;

	char* line;
	char* value;
	size_t line_size = 0;

	meme meme_data;
	font font_data;


	/* Check to make sure there are the proper number of argumnets. */
	if (argc != 3 ) {
		printf("Invalid number of arguments!\n");
		return 1;
	}

	
	/* Open the files for reading. If one fails to open, then exit and return 1. */
	meme_file = fopen( argv[1], "r" );

	if (meme_file == 0) {
		printf("File %s failed to open!\n", argv[1]);
		return 1;
	}
	
	action_file = fopen( argv[2], "r" );

	if (action_file == 0) {
		printf("File %s failed to open!\n", argv[2]);
		fclose(meme_file);
		return 1;
	}


	/* Read through the act file */
	while (getline(&line, &line_size, action_file) != -1) {
		/* TODO: remove testing print statements */
		printf("--> %s", line);

		/* For each line, take action based on what it starts with */
		if (strncmp(line, "OUTFILE", 7) == 0) {
			/* Open the outfile for writing binary. */
			/* TODO: find the out_name. */
			outfile = fopen(out_name, "wb");
		} else if (strncmp(line, "MEME", 4) == 0) {
			/* Initialize the meme structure with the given name. */
			initMeme(meme_data, value);
		} else if (strncmp(line, "FONT", 4) == 0) {
			/* Initialize the font structure with the given name. */
			
		} else {
			/* If the meme structure already exists, add attributes. */
			
		}
	}

	
	if (outfile == 0) {

		printf("File '%s' failed to open!\n", out_name);

		fclose(meme_file);
		fclose(action_file);

		return 1;
	}

	/* Read through the mem file */
	while (getline(&line, &line_size, meme_file) != -1) {
		printf("--> %s", line);
		/* Split at the ':' delimiter */
	}

	/* Read through the fsf file */

	


	/* cleanup */
	free(line);
	line = 0;

	fclose(meme_file);
	fclose(action_file);
	fclose(font_file);
	fclose(outfile);

	return 0;
}


