#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <png.h>
#include <assert.h>
#include <time.h>

#define R 0
#define G 1
#define B 2

extern static int height = 0;
extern static int weight = 0;
extern static long stride = 0;

extern static png_byte bit_depth;
extern static png_byte color_type;
extern static png_bytep row_pointers[height];

void rgba2bw_modified(uint32_t *bitmap);
void rgba2bw_origin(uint32_t *bitmap);
int png_check(char name);
int png_read(char name);
int png_write(char name);
