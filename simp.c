/*
 * simp.c
 * By Alex Lende
 * 
 * The simp.c file contains all of the function bodies
 * for the function prototypes in simp.h.
 *
 * The functions below relate to reading and writing of
 * the simp file type.
 */

#include <stdlib.h>
#include <stdio.h>
#include "simp.h"

/*
 * Creates space for the data of a simp structure with the given width and height.
 */
void initSimp(simp *simp_data, int width, int height) {

	int i;

	if (width < 0 || height < 0) {
		simp_data->width = 0;
		simp_data->height = 0;
		simp_data->data = 0;
		return;
	}

	simp_data->width = width;
	simp_data->height = height;

	simp_data->data = (pixel**) malloc(height * sizeof(pixel*));

	for (i = 0; i < simp_data->height; i++) {
		simp_data->data[i] = (pixel*) malloc(width * sizeof(pixel));
	}
}


/*
 * Frees the data malloc'd for the simp data.
 */
void freeSimp(simp *simp_data) {

	int i;

	for (i = 0; i < simp_data->height; i++) {
		free(simp_data->data[i]);
		simp_data->data[i] = 0;
	}
	
	free(simp_data->data);
	simp_data->data = 0;
}


/*
 * Allocates space for the data part of a simp data structure. Reads the simp file
 * into the structure. Returns the number of bytes read from the file or zero if
 * the file was unable to be read correctly. (i.e. The width and height read from 
 * the file don't match up with the size of the rest of the file.)
 */
size_t readSimp(simp *simp_data, FILE *read_file) {
	
	size_t size_read, file_size;
	int i;
	int width, height;
	long int calculated_size;

	/* Read the number of bytes in the file */
	fseek(read_file, 0, SEEK_END);
	file_size = ftell(read_file);
	fseek(read_file, 0, SEEK_SET);

	/* Initialize size_read. */
	size_read = 0;
	
	/* Read the first two 32-bit integers into the width and height and count the number of bytes read. */
	size_read += fread(&width,  sizeof(int), 1, read_file) * sizeof(int);
	size_read += fread(&height, sizeof(int), 1, read_file) * sizeof(int);

	if (width < 0 || height < 0) return 0;

	calculated_size = ( (long int) width * height * sizeof(pixel) ) + (2 * sizeof(int));

	/* The expected size of the file is the size of the two 32-bit ints that were already read and the sum of all the pixels. */
	/* If the expected size is not the same as the actual size, then the file is incorrect. */
	if (file_size != calculated_size) return 0;

	/* Initialize the width and height of the simp struct and malloc space for the pixels. */
	initSimp(simp_data, width, height);

	/* Read in all of the pixels. */
	for (i = 0; i < simp_data->height; i++) {
		size_read += fread(simp_data->data[i], sizeof(pixel), simp_data->width, read_file) * sizeof(pixel);
	}

	return size_read;
}


/*
 * Writes data from a simp data structure to a simp file. Frees the space allocated for the data. Returns the number of bytes written to the file.
 */
size_t writeSimp(simp *simp_data, FILE *write_file) {

	size_t size_written;
	int i;

	size_written = 0;

	size_written += fwrite(&(simp_data->width), sizeof(int), 1, write_file) * sizeof(int);
	size_written += fwrite(&(simp_data->height), sizeof(int), 1, write_file) * sizeof(int);

	for (i = 0; i < simp_data->height; i++) {
		size_written += fwrite(simp_data->data[i], sizeof(pixel), simp_data->width, write_file) * sizeof(pixel);
	}

	freeSimp(simp_data);

	return size_written;
}


/* Thsese are the functions for modifying the simp file. */
/* 
 * Makes all pixels in simp_data grayscale by averaging the R, G, and B values.
 * Returns zero on error and a positive integer on success.
 */
void bw(simp* simp_file) {
/* TODO	if (simp_file) {
		for (i = 0; i < simp_file->height; i++) {
			for (j = 0; j < simp_file->width; j++) {
				
				unsigned char avg;
				avg = ((simp_file->data[i][j].r) + (simp_file->data[i][j].g) + (simp_file->data[i][j].b)) / 3;
				
				simp_file->data[i][j].r = avg;
				simp_file->data[i][j].g = avg;
				simp_file->data[i][j].b = avg;
			}	
		}
	}*/
}

/* Swaps the R, G, and B values of all pixels in simp_data using the given pattern. */
void colorshift(simp* simp_data, char* pattern) {
/* TODO	if (!strcmp(argv[3], "RGB") || !strcmp(argv[3], "GBR") || !strcmp(argv[3], "BRG")) {
		for (i = 0; i < simp_file->height; i++) {
			for (j = 0; j < simp_file->width; j++) {
				unsigned char tmp = simp_file->data[i][j].r;
				simp_file->data[i][j].r = simp_file->data[i][j].b;
				simp_file->data[i][j].b = simp_file->data[i][j].g;
				simp_file->data[i][j].g = tmp;
			}
		}
	} else if (!strcmp(argv[3], "RBG") || !strcmp(argv[3], "BGR") || !strcmp(argv[3], "GRB")) {
		for (i = 0; i < simp_file->height; i++) {
			for (j = 0; j < simp_file->width; j++) {
				unsigned char tmp = simp_file->data[i][j].r;
				simp_file->data[i][j].r = simp_file->data[i][j].g;
				simp_file->data[i][j].g = simp_file->data[i][j].b;
				simp_file->data[i][j].b = tmp;
			}
		}
	} else if (!strcmp(argv[3], "RG") || !strcmp(argv[3], "GR")) {
		for (i = 0; i < simp_file->height; i++) {
			for (j = 0; j < simp_file->width; j++) {
				unsigned char tmp = simp_file->data[i][j].r;
				simp_file->data[i][j].r = simp_file->data[i][j].g;
				simp_file->data[i][j].g = tmp;
			}
		}
	} else if (!strcmp(argv[3], "RB") || !strcmp(argv[3], "BR")) {
		for (i = 0; i < simp_file->height; i++) {
			for (j = 0; j < simp_file->width; j++) {
				unsigned char tmp = simp_file->data[i][j].r;
				simp_file->data[i][j].r = simp_file->data[i][j].b;
				simp_file->data[i][j].b = tmp;
			}
		}
	} else if (!strcmp(argv[3], "GB") || !strcmp(argv[3], "BG")) {
		for (i = 0; i < simp_file->height; i++) {
			for (j = 0; j < simp_file->width; j++) {
				unsigned char tmp = simp_file->data[i][j].g;
				simp_file->data[i][j].g = simp_file->data[i][j].b;
				simp_file->data[i][j].b = tmp;
			}
		}
	}*/
}

/* 
 * Copies the pixels from simp_in to simp_out that are within the given x, y, w, and h bounds.
 * Returns zero if error and one if otherwise.
 */
void crop(simp* simp_in, simp* simp_out, int x, int y, int w, int h) {
	int i = j = 0;

	pixel empty_pixel = 0;
	
	/* Copy the cropped area of the image into the new structure. */
	for (i = 0; i < h; i++) {
		for (j = 0; j < w; j++) {
			if ((i+y) < 0 || (j+x) < 0 || (i+y) >= simp_in->height || (j+x) >= simp_in->width) {
				/* If the pixel doesn't exist in the image, make a empty one in it's place. */
				simp_out->data[i][j] = empty_pixel;
			} else {
				simp_out->data[i][j] = simp_in->data[i+y][j+x];
			}
		}
	}
}

/* 
 * Overlays the pixels from simp_top onto the pixels of simp_bottom, calculating the transparencies
 * Returns zero if error and one if otherwise.
 */
void overlay(simp* simp_top, simp* simp_bottom, int x, int y) {
	int i, j, i_start, j_start;

	i_start = (y < 0) ? -y : 0;
	j_start = (x < 0) ? -x : 0;

	for (i = i_start; (i < simp_top->height) && ((i+y) < simp_bottom->height); i++) {
		for (j = j_start; (j < simp_top->width) && ((j+x) < simp_bottom->width); j++) {

			unsigned char r1, g1, b1, a1, r2, g2, b2, a2;
			
			r1 = simp_bottom->data[i+y][j+x].r;
			g1 = simp_bottom->data[i+y][j+x].g;
			b1 = simp_bottom->data[i+y][j+x].b;
			a1 = simp_bottom->data[i+y][j+x].a;

			r2 = simp_top->data[i][j].r;
			g2 = simp_top->data[i][j].g;
			b2 = simp_top->data[i][j].b;
			a2 = simp_top->data[i][j].a;

			if (a2 == 0xFF) {
				simp_bottom->data[i+y][j+x].r = r2;
            	simp_bottom->data[i+y][j+x].g = g2;
            	simp_bottom->data[i+y][j+x].b = b2;
				simp_bottom->data[i+y][j+x].a = a2;
			} else {
				simp_bottom->data[i+y][j+x].r = ((a2*r2)/0xFF)+((r1*a1*(0xFF-a2))/(0xFF*0xFF));
				simp_bottom->data[i+y][j+x].g = ((a2*g2)/0xFF)+((g1*a1*(0xFF-a2))/(0xFF*0xFF));
				simp_bottom->data[i+y][j+x].b = ((a2*b2)/0xFF)+((b1*a1*(0xFF-a2))/(0xFF*0xFF));
				simp_bottom->data[i+y][j+x].a = (((0xFF*(a1+a2))-(a1*a2))/0xFF);
			}
		}
	}
}

