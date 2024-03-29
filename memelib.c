/* 
 * memelib.c
 */

#include <stdlib.h>
#include<string.h>
#include "simp.h"
#include "memelib.h"

void initMeme(meme* meme_data, char* name) {
	meme_data->name = (char*) malloc(strlen(name) + 1);
	strcpy(meme_data->name, name);
	meme_data->attr = 0;
	meme_data->num_attr = 0;
}

void addAttribute(meme* meme_data, char* name, char* msg, int x, int y) {

	attribute* tmp = 0;
	
	tmp = (attribute*) realloc(meme_data->attr, (meme_data->num_attr + 1) * sizeof(attribute));

	/* If realloc was successful... */
	if (tmp) {
		/* Copy the pointer over now that it's safe. */
		meme_data->attr = tmp;
		
		/* Increment the number of attributes. */
		(meme_data->num_attr)++;
		
		/* Allocate or reallocate space for the name and message */
		meme_data->attr[(meme_data->num_attr) - 1].name = malloc(strlen(name) + 1);
		meme_data->attr[(meme_data->num_attr) - 1].msg = malloc(strlen(msg) + 1);
		
		/* Set the values of the attribute. */
		strcpy(meme_data->attr[(meme_data->num_attr) - 1].name, name);
		strcpy(meme_data->attr[(meme_data->num_attr) - 1].msg, msg);
		meme_data->attr[(meme_data->num_attr) - 1].x = x;
		meme_data->attr[(meme_data->num_attr) - 1].y = y;
	} else {
		printf("!!! REALLOC FAILED !!!\n");
	}

}

void freeMeme(meme* meme_data) {
	int i;

	free(meme_data->name);
	meme_data->name = 0;

	for (i = 0; i < meme_data->num_attr; i++) {
		
		free(meme_data->attr[i].name);
		meme_data->attr[i].name = 0;

		free(meme_data->attr[i].msg);
		meme_data->attr[i].msg = 0;
	}

	free(meme_data->attr);
	meme_data->attr = 0;
}

void printMeme(meme* m) {
	int i;
	printf("<=== MEME ===>\n");
	printf("NAME: %s\n", m->name);
	printf("NUM_ATTR: %d\n", m->num_attr);
	printf("ATTRIBUTES:\n");
	for(i = 0; i < m->num_attr; i++) {
		printAttr(m->attr[i]);
	}
	printf("<============>\n");
}

void printAttr(attribute a) {
	printf("%s : %s : (%d, %d)\n", a.name, a.msg, a.x, a.y);
}

/*
 * Searches for the given attribute name, and sets it's x and y coordinates.
 */
void setAttrCoord(meme* m, char* name, int x, int y) {
	int i;
	for (i = 0; i < m->num_attr; i++) {
		if (strcmp(name, m->attr[i].name) == 0) {
			m->attr[i].x = x;
			m->attr[i].y = y;
			break;
		}
	}
}
