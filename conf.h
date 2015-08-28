#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <png.h>

#include "rgba2bw_modified.c"
#include "rgba2bw_origin.c"
#include "imgio.c"

#define R 0
#define G 1
#define B 2

void rgba2bw(uint32_t **img, uint32_t **bwimg, int height,int width);
