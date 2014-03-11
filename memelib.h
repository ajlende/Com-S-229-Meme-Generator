/*
 * memelib.h
 */

#ifndef _MEMELIB_H_
#define _MEMELIB_H_

typedef struct attribute_s {
	char* name;
	char* msg;
	int x;
	int y;
} attribute;

typedef struct meme_s {
	char* name;
	int num_attr;
	attribute* attr;
} meme;

void initMeme(meme* meme_data, char* name);

void addAttribute(meme* meme_data, char* name, char* msg, int x, int y);

void freeMeme(meme* meme_data);

size_t readMeme();

void printMeme(meme* m);

void printAttr(attribute a);

void setAttrCoord(attribute* a, int x, int y);

#endif
