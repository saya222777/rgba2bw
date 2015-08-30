#include "conf.h"

void rgba2bw_modified(uint32_t *bitmap){

    /* build the table ----------------------------------------------------*/
    uint32_t val = 0;
    uint32_t table[256][3];
    for(val=0; val<256; val++) {     // table size = 4 byte * 256 * 3
        table[val][R]=val*0.299;    
        table[val][G]=val*0.587;   
        table[val][B]=val*0.114;   
    }

   /* convert the pixel data from RGBA to BW --------------- */
    int row, col;
    uint32_t a,r,g,b,bw,pixel;
    for(row = 0; row < height; row++) {
            for(col = 0; col < width; col++) {
                pixel = bitmap[col + row + stride];
                b = pixel & 0xff;
                b = table[b][B];
                pixel = pixel>>8;
                g = pixel & 0xff;
                g = table[g][G];
                pixel = pixel>>8;
                r = pixel & 0xff;
                r = table[r][R];
                pixel = pixel>>8;
                a = pixel & 0xff;
                bw = (uint32_t) (r+g+b);
                bitmap[col + row * stride] = (a << 24) + (bw << 16) + (bw << 8) + (bw);
            }
    }
}