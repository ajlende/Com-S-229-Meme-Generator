/* 
 * memelib.c
 */

#include <stdlib.h>
#include "simp.h"
#include "memelib.h"

void initMeme(meme* meme_data, char* name) {
	meme_data->name = name;
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
		
		/* Set the values of the attribute. */
		meme_data->attr[meme_data->num_attr - 1].name = name;
		meme_data->attr[meme_data->num_attr - 1].msg = msg;
		meme_data->attr[meme_data->num_attr - 1].x = x;
		meme_data->attr[meme_data->num_attr - 1].y = y;
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

size_t readMeme() {
	return 0;
}
