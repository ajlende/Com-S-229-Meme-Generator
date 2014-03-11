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

char* rmWhitespace(char* str);

int main (int argc, char** argv) {

	FILE* meme_file;
	FILE* action_file;
	FILE* font_file;
	FILE* simp_file;
	FILE* outfile;

	char* line = 0;
	char* name = 0;
	char* value = 0;
	char* tmp_word = 0;
	char* tmp_value = 0;
	size_t line_size = 0;

	int i, j, x, y, line_counter, search_flag;

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
	/* line = (char*) malloc(256); */
	name = (char*) malloc(128);
	value = (char*) malloc(128);

	line_counter = 0;

	/* Read through the act file */
	while (getline(&line, &line_size, action_file) != -1) {
		line_counter++;

		/* TODO: remove testing print statements */
		printf("<%p> line:  %s", line, line);

		if (line[0] == '\n') continue;

		/* Split the line into a name and a value. */
		strcpy(name, strtok(line, ":\n"));
		strcpy(value, strtok(0, ":\n"));
		
		printf("<%p> name:  %s\n", name, name);
		printf("<%p> value: %s\n", value, value);

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

	/* TODO: remove this. it is a test print message */
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

	line_counter = 0;

	/* Read through the mem file */
	while (getline(&line, &line_size, meme_file) != -1) {
		line_counter++;

		/* TODO: remove testing print statements */
		printf("<%p> line:  %s", line, line);

		if (line[0] == '\n') continue;

		/* Split the line into a name and a value. */
		strcpy(name, strtok(line, ":\n"));
		strcpy(value, strtok(0, ":\n"));
		
		printf("<%p> name:  %s\n", name, name);
		printf("<%p> value: %s\n", value, value);

		/* For each line, take action based on what it starts with */
		if (strncmp(line, "MEMES", 5) == 0) {
			search_flag = 0;
			tmp_word = strtok(value, " \t\n\v\f\r");
			/* Check that at least of of the values matches meme_data->name. If none do, then exit the program. */
			while(tmp_word != 0 ) {
				if (strcmp(tmp_word, meme_data->name) == 0) {
					search_flag = 1;
					break;
				}
				tmp_word = strtok(0, " \t\n\v\f\r");
			}

			/* If the meme we are looking for is not included in this file, then exit. */
			if (!search_flag) {
				
				printf("The Meme %s is not included in the mem file on line %d!", meme_data->name, line_counter);

				fclose(meme_file);
				fclose(action_file);
				fclose(outfile);

				if (font_file) {
					fclose(font_file);
				}

				freeMeme(meme_data);
				free(meme_data);
				meme_data = 0;

				freeFont(font_data);
				free(font_data);
				font_data = 0;

				return 1;
			}

		} else if (strncmp(line, "FONTS", 5) == 0) {
			
			/* Read the name of each one. If the name matches font_data->name, then keep that open as font_file and close all other fsf files. */
			tmp_word = strtok(value, " \t\n\v\f\r");
			
			search_flag = 0

			/* Check that at least of of the values matches font_data->name. If none do, then exit the program. */
			while(tmp_word != 0 ) {

				/* Open each font file for reading */
				font_file = fopen(value, "r");				

				/* If the font_file doesn't open, then close everything and exit. */
				if (font_file == 0) {
			
					printf("The file %s on line %d failed to open!\n", value, line_counter);
			
					fclose(meme_file);
					fclose(action_file);
					fclose(outfile);

					if (simp_file) {
						fclose(simp_file);
					}
			
					freeMeme(meme_data);
					free(meme_data);
					meme_data = 0;
			
					freeFont(font_data);
					free(font_data);
					font_data = 0;
			
					return 1;
				}

				/* TODO: Read the fsf file, and look for the name tag. */
				/* TODO: Change the first parameter of strcmp to ne the name that gets read. For now, I am using IMPACT because that is the name of the font that we will be using for tests. */

				if (strcmp("IMPACT", font_data->name) == 0) {
					search_flag = 1;
					break;
				}

				fclose(font_file);

				tmp_word = strtok(0, " \t\n\v\f\r");
			}

			/* If the meme we are looking for is not included in this file, then exit. */
			if (!search_flag) {
				
				printf("The Font %s on line %d is not included in the mem file!\n", font_data->name, line_counter);

				fclose(meme_file);
				fclose(action_file);
				fclose(outfile);

				if (font_file) {
					fclose(font_file);
				}

				if (simp_file) {
					fclose(simp_file);
				}

				freeMeme(meme_data);
				free(meme_data);
				meme_data = 0;

				freeFont(font_data);
				free(font_data);
				font_data = 0;

			}

		} else if (strncmp(line, meme_data->name, strlen(meme_data->name)) == 0) {

			/* Check to see of the next word is "FILE". If it is then open that simp file, otherwise add the values to the associated attribute. */
			sscanf(name, "%*s %s", tmp_word);

			if (strcmp(tmp_word, "FILE") == 0) {
				/* Open each font file for reading */
				simp_file = fopen(value, "rb");				

				/* If the simp_file doesn't open, then close everything and exit. */
				if (simp_file == 0) {
			
					printf("The simp file, %s, on line %d failed to open!\n", value, line_counter);
			
					fclose(meme_file);
					fclose(action_file);
					fclose(outfile);

					if (font_file) {
						fclose(font_file);
					}
			
					freeMeme(meme_data);
					free(meme_data);
					meme_data = 0;
			
					freeFont(font_data);
					free(font_data);
					font_data = 0;
			
					return 1;
				}

			} else {

				if(sscanf(value, "%d %d", &x, &y) != 2) {
					
					printf("Invalid argument(s) on line %d: %s!", line_counter, line);

					fclose(meme_file);
					fclose(action_file);
					fclose(outfile);

					if (font_file) {
						fclose(font_file);
					}
			
					freeMeme(meme_data);
					free(meme_data);
					meme_data = 0;
			
					freeFont(font_data);
					free(font_data);
					font_data = 0;
			
					return 1;
				}

				setAttrCoord(meme_data, tmp_word, x, y);
			}

		}
	}


	/* Read through the fsf file */
	while (getline(&line, &line_size, font_file) != -1) {
		/* TODO: remove testing print statements */
		printf("<%p> line:  %s", line, line);

		if (line[0] == '\n') continue;

		/* Split the line into a name and a value. */
		strcpy(name, strtok(line, ":\n"));
		strcpy(value, strtok(0, ":\n"));
		
		printf("<%p> name:  %s\n", name, name);
		printf("<%p> value: %s\n", value, value);

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
	free(name);
	name = 0;
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
	fclose(simp_file);
	fclose(outfile);

	return 0;
}

char* rmWhitespace(char* str) {
	int i;
	char* out = "TODO";

	return out;
}
