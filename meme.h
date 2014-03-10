/*
 * meme.h
 */

#ifndef _MEME_H_
#define _MEME_H_

typedef struct attribute_s {
	char* name;
	char* msg;
	int x;
	int y;
} attribute;

typedef struct meme_s {
	char* name;
	attribute* attr;
} meme;

void initMeme(meme *meme_data);

void freeMeme(meme *meme_data);

size_t readMeme();

#endif
