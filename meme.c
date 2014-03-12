/*
 * meme.c
 */

#define _GNU_SOURCE
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "memelib.h"
#include "font.h"
#include "simp.h"

char* rmWhitespace(char* str);

void freeAll(char* fmt, ...);

int main (int argc, char** argv) {

	FILE* meme_file = 0;
	FILE* action_file = 0;
	FILE* font_file = 0;
	FILE* font_simp_file = 0;
	FILE* simp_file = 0;
	FILE* outfile = 0;

	char* line = 0;
	char* name = 0;
	char* value = 0;
	char* tmp_word = 0;
	char* tmp_value = 0;
	char* meme_filename = 0;
	char* action_filename = 0;

	size_t line_size = 0;

	int i = 0;
	int j = 0;
	int x = 0;
	int y = 0;
	int w = 0;
	int h = 0;
	int line_counter = 0;
	int search_flag = 0;

	meme* meme_data = 0;
	font* font_data = 0;

	simp* meme_simp = 0;
	simp* font_simp = 0;
	simp* string_simp = 0;
	simp* temp_simp = 0;

	simp* temp_swap_ptr = 0;


	/* Check to make sure there are the proper number of argumnets. */
	if (argc != 3 ) {
		printf("Invalid number of arguments!\n");
		return 1;
	}

	meme_filename = argv[1];
	action_filename = argv[2];
	
	/* Open the files for reading. If one fails to open, then exit and return 1. */
	meme_file = fopen(meme_filename, "r");

	if (meme_file == 0) {
		printf("File %s failed to open!\n", meme_filename);
		return 1;
	}

	action_file = fopen(action_filename, "r");

	if (action_file == 0) {
		printf("File %s failed to open!\n", action_filename);

		freeAll("cccmnssffffff", line, name, value, meme_data, font_data, font_simp, meme_simp, meme_file, action_file, font_file, font_simp_file, simp_file, outfile);

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

			/* If the outfile doesn't open then close everything and exit */
			if (outfile == 0) {
		
				printf("The outfile from line %d of %s failed to open!\n", line_counter, action_filename);

				freeAll("cccmnssffffff", line, name, value, meme_data, font_data, font_simp, meme_simp, meme_file, action_file, font_file, font_simp_file, simp_file, outfile);

				return 1;
			}

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
				
				printf("The Meme %s is not included in the file %s on line %d!", meme_data->name, meme_filename, line_counter);

				freeAll("cccmnssffffff", line, name, value, meme_data, font_data, font_simp, meme_simp, meme_file, action_file, font_file, font_simp_file, simp_file, outfile);

				return 1;
			}

		} else if (strncmp(line, "FONTS", 5) == 0) {
			
			/* Read the name of each one. If the name matches font_data->name, then keep that open as font_file and close all other fsf files. */
			tmp_word = strtok(value, " \t\n\v\f\r");
			
			search_flag = 0;

			/* Check that at least of of the values matches font_data->name. If none do, then exit the program. */
			while(tmp_word != 0 ) {

				/* Open each font file for reading */
				font_file = fopen(value, "r");				

				/* If the font_file doesn't open, then close everything and exit. */
				if (font_file == 0) {
			
					printf("The file %s on line %d of %s failed to open!\n", value, line_counter, meme_filename);

					freeAll("cccmnssffffff", line, name, value, meme_data, font_data, font_simp, meme_simp, meme_file, action_file, font_file, font_simp_file, simp_file, outfile);
				
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

				freeAll("cccmnssffffff", line, name, value, meme_data, font_data, font_simp, meme_simp, meme_file, action_file, font_file, font_simp_file, simp_file, outfile);

				return 1;

			}

		} else if (strncmp(line, meme_data->name, strlen(meme_data->name)) == 0) {

			/* Check to see of the next word is "FILE". If it is then open that simp file, otherwise add the values to the associated attribute. */
			tmp_word = name;
			sscanf(name, "%*s %s", tmp_word);

			if (strcmp(name, "FILE") == 0) {

				/* Open each font file for reading */
				simp_file = fopen(value, "rb");				

				/* If the simp_file doesn't open, then close everything and exit. */
				if (simp_file == 0) {
			
					printf("The simp file, %s, on line %d of %s failed to open!\n", value, line_counter, meme_filename);

					freeAll("cccmnssffffff", line, name, value, meme_data, font_data, font_simp, meme_simp, meme_file, action_file, font_file, font_simp_file, simp_file, outfile);
			
					return 1;
				}

				meme_simp = (simp*) malloc(sizeof(simp));

				if (!readSimp(meme_simp, simp_file)) {
					
					printf("The meme simp file was unable to be read!\n");

					freeAll("cccmnssffffff", line, name, value, meme_data, font_data, font_simp, meme_simp, meme_file, action_file, font_file, font_simp_file, simp_file, outfile);

					return 1;
				}

			} else {

				if (sscanf(value, "%d %d", &x, &y) != 2) {
					
					printf("Invalid argument(s) on line %d of %s: %s:value!\n", line_counter, meme_filename, line, value);

					freeAll("cccmnssffffff", line, name, value, meme_data, font_data, font_simp, meme_simp, meme_file, action_file, font_file, font_simp_file, simp_file, outfile);

					return 1;
				}

				setAttrCoord(meme_data, tmp_word, x, y);
			}

		}
	}

	printMeme(meme_data);

	line_counter = 0;

	/* Read through the fsf file */
	while (getline(&line, &line_size, font_file) != -1) {
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
		if (strncmp(line, "NAME", 4) == 0) {
			
			/* This statement may be able to be removed because the NAME was already checked in the mem file read. */

		} else if (strncmp(line, "IMAGE", 5) == 0) {

			/* Open the simp image for editing */
			font_simp_file = fopen(value, "rb");

			/* If the simp_file doesn't open, then close everything and exit. */
			if (font_simp_file == 0) {
		
				printf("The simp file, %s, on line %d of the specified fsf file failed to open!\n", value, line_counter);

				freeAll("cccmnssffffff", line, name, value, meme_data, font_data, font_simp, meme_simp, meme_file, action_file, font_file, font_simp_file, simp_file, outfile);
				
				return 1;
			}

			font_simp = (simp*) malloc(sizeof(simp));
			
			if (!readSimp(font_simp, font_simp_file)) {

				printf("The file %s from line %d of the fsf file was unable to be read!\nThe filetype may be incorrect or the file may be corrupted.\n", value, line_counter);

				freeAll("cccmnssffffff", line, name, value, meme_data, font_data, font_simp, meme_simp, meme_file, action_file, font_file, font_simp_file, simp_file, outfile);
			
				return 1;

			}
			
		} else if (strncmp(line, "CHARACTER", 9) == 0) {

			if (!font_simp_file) {
				printf("The fsf IMAGE line must come before any CHARACTERn line!\n");

				freeAll("cccmnssffffff", line, name, value, meme_data, font_data, font_simp, meme_simp, meme_file, action_file, font_file, font_simp_file, simp_file, outfile);
			
				return 1;

			}
			
			/* Check the character after CHARACTER. Crop the image at the given values and store it at the proper index. */

			if (sscanf(value, "%d %d %d %d", &x, &y, &w, &h) != 4) {
				printf("Invalid argument(s) on line %d of the fsf file!\n", line_counter);

				freeAll("cccmnssffffff", line, name, value, meme_data, font_data, font_simp, meme_simp, meme_file, action_file, font_file, font_simp_file, simp_file, outfile);

				return 1;				
			}

			addCharacter(font_simp, font_data, name[9], x, y, w, h);
			
		}
	}
	
	/* create a string_simp to overlay, and a temp_simp to hold the temporary crop. */
	string_simp = (simp*) malloc(sizeof(simp));
	temp_simp = (simp*) malloc(sizeof(simp));

	/* For each attribute in the meme */
	for (i = 0; i < meme_data->num_attr; i++) {
	
		/* TODO: take care of the scenario where there are zero letters in the message. */
		w = font_data->characters[meme_data->attr[0].msg[0]]->width;
		h = font_data->characters[meme_data->attr[0].msg[0]]->height;
	
		/* initialize the string_simp with the width of the first two letters. */
		initSimp(string_simp, w, h);
		crop(font_data->characters[meme_data->attr[0].msg[0]], string_simp, 0, 0, w, h);


		line_size = strlen(meme_data->attr[i].msg);

		/* For each letter in that attribute's message. */
		for (j = 0; j < line_size; j++) {
			w = font_data->characters[meme_data->attr[i].msg[j]]->width;
			w += string_simp->width;
			h = font_data->characters[meme_data->attr[i].msg[j]]->height;
			
			initSimp(temp_simp, w, h);
			
			/* Crop simp_string into temp_simp with simp_string->width + current character's width and the standard height. */
			crop(string_simp, temp_simp, 0, 0, w, h);

			/* Swap string_simp and temp_simp pointers. */
			temp_swap_ptr = string_simp;
			string_simp = temp_simp;
			temp_simp = temp_swap_ptr;

			freeSimp(temp_simp);
		}

		/* Overlay the completed string_simp onto the meme_simp. */
		overlay(string_simp, meme_simp, 0, 0);

		/* Free the string_simp to use on the next attribute. */
		freeSimp(string_simp);
	}

	/* Write the meme_simp to the outfile */
	writeSimp(meme_simp, outfile);
	

	/* cleanup */
	freeAll("cccmnssssffffff", line, name, value, meme_data, font_data, font_simp, meme_simp, string_simp, temp_simp, meme_file, action_file, font_file, font_simp_file, simp_file, outfile);

	return 0;
}

char* rmWhitespace(char* str) {
	int i;
	char* out = "TODO";

	return out;
}

void freeAll(char* fmt, ...) {
	const char* p = 0;
	void* a = 0;

	va_list argp;

	va_start(argp, fmt);

	for (p = fmt; *p != '\0'; p++) {

		a = va_arg(argp, void*);

		if(!a) continue;
		
		switch(*p) {
			case 'c':
				/* handle char* */
				free((char*) a);
				printf("free char*\n");
				break;
			case 'f':
				/* handle FILE* */
				fclose((FILE*) a);
				printf("free FILE*\n");
				break;
			case 'n':
				/* handle font* */
				freeFont((font*) a);
				free((font*) a);
				printf("free font*\n");
				break;
			case 'm':
				/* handle meme* */
				freeMeme((meme*) a);
				free((meme*) a);
				printf("free meme*\n");
				break;
			case 's':
				/* handle simp* */
				freeSimp((simp*) a);
				free((simp*) a);
				printf("free simp*\n");
				break;
		}
		
		printf("zeroing %p\n", a);
		a = 0;
	}

	va_end(argp);
}
