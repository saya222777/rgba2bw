#include "conf.h"

void rgba2bw(uint32_t **img, uint32_t **bwimg, int height,int width){

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
    uint32_t a,r,g,b,bw;
    for(row = 0; row < height; row++) {
            for(col = 0; col < width; col++) {
                b = img[row][col] & 0xff;
                b = table[b][B];
                img[row][col]=img[row][col]>>8;
                g = img[row][col] & 0xff;
                g = table[g][G];
                img[row][col]=img[row][col]>>8;
                r = img[row][col] & 0xff;
                r = table[r][R];
                img[row][col]=img[row][col]>>8;
                a = img[row][col] & 0xff;
                bw=r+g+b;
                bwimg[row][col] = (a << 24) + (bw << 16) + (bw << 8) + (bw);
            }
    }
}
