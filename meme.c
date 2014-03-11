/*
 * meme.c
 */

#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "memelib.h"
#include "font.h"
#include "simp.h"

int main (int argc, char** argv) {

	FILE* meme_file;
	FILE* action_file;
	FILE* font_file;
	FILE* outfile;

	char* line;
	char* name;
	char* value;
	size_t line_size = 0;

	int i, j;

	meme* meme_data;
	font* font_data;


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


	/* Create space for the meme and font data structure */
	meme_data = (meme*) malloc(sizeof(meme));
	font_data = (font*) malloc(sizeof(font));

	/* Create space for the strings */
	name = (char*) malloc(128);
	value = (char*) malloc(128);


	/* Read through the act file */
	while (getline(&line, &line_size, action_file) != -1) {
		/* TODO: remove testing print statements */
		printf("--> %s", line);

		/* Split the line into a name and a value. */
		strcpy(strtok(line, ":\n"), name);
		strcpy(strtok(0, ":\n"), value);

		printf("name: %s\n", name);
		printf("value: %s\n", value);

		/* For each line, take action based on what it starts with */
		if (strncmp(line, "OUTFILE", 7) == 0) {
			
			/* Open the outfile for writing binary. */
			/* TODO: find the value. */
			outfile = fopen(value, "wb");

		} else if (strncmp(line, "MEME", 4) == 0) {

			/* Initialize the meme structure with the given name. */
			initMeme(meme_data, value);

		} else if (strncmp(line, "FONT", 4) == 0) {
			
			/* Initialize the font structure with the given name. */
			initFont(font_data, value);

		} else {

			/* If the meme structure already exists, add attributes. */
			addAttribute(meme_data, name, value, 0, 0);
		}
	}

	printMeme(meme_data);


	/* If the outfile doesn't open then close everything and exit */
	if (outfile == 0) {

		printf("The outfile file failed to open!\n");

		fclose(meme_file);
		fclose(action_file);
		printf("closed mem file and act file.\n");

		freeMeme(meme_data);
		free(meme_data);
		meme_data = 0;
		printf("freed meme_data\n");

		freeFont(font_data);
		free(font_data);
		font_data = 0;
		printf("freed font_data.\n");

		return 1;
	}


	/* Read through the mem file */
	while (getline(&line, &line_size, meme_file) != -1) {
		/* TODO: remove testing print statements */
		printf("--> %s", line);

		/* Split the line into a name and a value. */
		name = strtok(line, ":\n");
		value = strtok(0, ":\n");

		printf("name: %s\n", name);
		printf("value: %s\n", value);


		/* For each line, take action based on what it starts with */
		if (strncmp(line, "MEMES", 5) == 0) {

			/* Check that at least of of the values matches meme_data->name. If none do, then exit the program. */

		} else if (strncmp(line, "FONTS", 5) == 0) {

			/* Open each font file for reading */
			fopen(value, "r");

			/* Read the name of each one. If the name matches font_data->name, then keep that open as font_file and close all other fsf files. */

		} else if (strncmp(line, meme_data->name, strlen(meme_data->name)) == 0) {

			/* Check to see of the next word is "FILE". If it is then open that simp file, otherwise add the values to the associated attribute. */
		}
	}


	/* If the font_file doesn't open, then close everything and exit. */
	if (font_file == 0) {

		printf("The fsf file failed to open!\n");

		fclose(meme_file);
		fclose(action_file);

		freeMeme(meme_data);
		free(meme_data);
		meme_data = 0;

		freeFont(font_data);
		free(font_data);
		font_data = 0;

		return 1;
	}


	/* Read through the fsf file */
	while (getline(&line, &line_size, font_file) != -1) {
		/* TODO: remove testing print statements */
		printf("--> %s", line);

		/* Split the line into a name and a value. */
		name = strtok(line, ":\n");
		value = strtok(0, ":\n");

		printf("name: %s\n", name);
		printf("value: %s\n", value);


		/* For each line, take action based on what it starts with */
		if (strncmp(line, "NAME", 4) == 0) {
			
			/* This statement may be able to be removed because the NAME was already checked in the mem file read. */

		} else if (strncmp(line, "IMAGE", 5) == 0) {

			/* Open the simp image for editing */
			
		} else if (strncmp(line, "CHARACTER", 9) == 0) {
			
			/* Check the character after CHARACTER. Crop the image at the given values and store it at the proper index. */
			
		}
	}
	

	/* cleanup */
	free(line);
	line = 0;

	free(value);
	value = 0;

	freeMeme(meme_data);
	free(meme_data);
	meme_data = 0;

	freeFont(font_data);
	free(font_data);
	font_data = 0;

	fclose(meme_file);
	fclose(action_file);
	fclose(font_file);
	fclose(outfile);

	return 0;
}


