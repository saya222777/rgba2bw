// void rgba_to_bw(uint32_t *bitmap, int width, int height, long stride) {
//     int row, col;
//     uint32_t pixel, r, g, b, a, bw;
//     for (row = 0; row < height; row++) {
//         for (col = 0; col < width; col++) {
//             pixel = bitmap[col + row + stride / 4];
//             a = (pixel >> 24) & 0xff;
//             r = (pixel >> 16) & 0xff;
//             g = (pixel >> 8) & 0xff;
//             b = pixel & 0xff;
//             bw = (uint32_t) (r * 0.299 + g * 0.587 + b * 0.114);
//             bitmap[col + row * stride / 4] = (a << 24) + (bw << 16) + (bw << 8) + (bw);
//         }
//     }
// }

#include "conf.h"

void rgba2bw_origin(uint32_t *bitmap){

   /* convert the pixel data from RGBA to BW --------------- */
    int row, col;
    uint32_t a,r,g,b,bw,pixel;
    for(row = 0; row < height; row++) {
            for(col = 0; col < width; col++) {
                pixel = bitmap[col + row + stride];
                a = (pixel >> 24) & 0xff;
                r = (pixel >> 16) & 0xff;
                g = (pixel >> 8) & 0xff;
                b = pixel & 0xff;
                bw = (uint32_t) (r * 0.299 + g * 0.587 + b * 0.114);
                bitmap[col + row * stride] = (a << 24) + (bw << 16) + (bw << 8) + (bw);
            }
    }
}