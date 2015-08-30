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

static int height = 0;
static int width = 0;
static long stride = 0;

static png_byte bit_depth;
static png_byte color_type;
static png_bytep *row_pointers;
static png_bytep pixels;
