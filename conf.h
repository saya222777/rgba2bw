#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <png.h>
#include <assert.h>
#include <time.h>

#include "imgio.h"
#include "rgba2bw_modified.h"
#include "rgba2bw_origin.h"

#define R 0
#define G 1
#define B 2

extern static int height = 0;
extern static int weight = 0;
extern static long stride = 0;

extern static png_byte bit_depth;
extern static png_byte color_type;
extern static png_bytep row_pointers[height];
extern static png_bytep pixels;

