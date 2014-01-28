#include<stdint.h>
#include<stdio.h>

typedef struct pixel_s {
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
} pixel;

typedef struct simp_s {
	int32_t width;
	int32_t height;
	pixel[] data;
} simp;

// Reads a file and returns a simp data structure to work with
simp readSimp(void) {
	simp image;
	return image;
}

// Writes the simp file after manipulation
void writeSimp(void) {
	return;
}
