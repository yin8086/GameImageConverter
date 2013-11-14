#include"swizzleUtility.h"

uint32_t swizzle_x(uint32_t x0, SWIZZLETYPE sType) {
    if(sType == SWIZZLE16x8) { // both part
        uint32_t lower = x0 & 0xf;
        uint32_t higher = x0 - lower;
        return lower + (higher << 3);
    }
    else return x0;
}

uint32_t swizzle_y(uint32_t y0, SWIZZLETYPE sType) {
    if(sType == SWIZZLE16x8) { // only lower part
        uint32_t lower = y0 & 0x7;
        return lower << 4;
    }
    else return y0;
}

void swizzleARGB(uint8_t *dst, const uint8_t *src,
                 int width, int height,
                 SWIZZLETYPE sType) {

    if(sType == TILE16x8) { //16x8 Tile
        uint32_t widthInTiles = (width + tileW-1) / tileW;

        const uint32_t *pSrcCur = (uint32_t *)src;
        uint32_t *pDstCur;

        for(int y = 0; y < height; ++y) {
            for(int x = 0; x < width; ++x) {
                uint32_t tileX = x / tileW;
                uint32_t tileY = y / tileH;
                uint32_t inTileX = x % tileW;
                uint32_t inTileY = y % tileH;

                pDstCur = (uint32_t *)dst + ((tileY * widthInTiles + tileX) * (tileW * tileH)
                                      + inTileY * tileW
                                      + inTileX);
                *pDstCur = *pSrcCur++;
            }
        }
    } //16x8 Tile
    else if(sType == SWIZZLE16x8) {  //16x8 Swizzle
        uint32_t off_x0 = swizzle_x(0);
        uint32_t off_y  = swizzle_y(0);
        uint32_t x_mask = swizzle_x(~0u);
        uint32_t y_mask = swizzle_y(~0u);
        uint32_t incr_y = swizzle_x(width);

        off_x0 += incr_y * (0/tileH);

        const uint32_t *srcL = (uint32_t *)src, *srcP;
        uint32_t *dstL;

        uint32_t off_x;
        uint32_t pixel;

        for(int y = 0; y < height; ++y) {
            srcP = srcL;
            dstL = (uint32_t *)dst + off_y;
            off_x = off_x0;

            for(int x = 0; x < width; ++x) {
                pixel = *srcP++;
                *(dstL + off_x) = pixel;
                off_x = (off_x - x_mask) & x_mask;
            }
            off_y = (off_y - y_mask) & y_mask;
            if(!off_y)
                off_x0 += incr_y;
            srcL += width;
        }
    }

}

void unswizzleARGB(uint8_t *dst, const uint8_t *src,
                   int width, int height,
                   SWIZZLETYPE sType) {

    if(sType == TILE16x8) { //16x8 Tile
        uint32_t widthInTiles = (width + tileW-1) / tileW;

        const uint32_t * pSrcCur;
        uint32_t *pDstCur = (uint32_t *)dst;

        for(int y = 0; y < height; ++y) {
            for(int x = 0; x < width; ++x) {
                uint32_t tileX = x / tileW;
                uint32_t tileY = y / tileH;
                uint32_t inTileX = x % tileW;
                uint32_t inTileY = y % tileH;

                pSrcCur = (uint32_t *)src + ((tileY * widthInTiles + tileX) * (tileW * tileH)
                                      + inTileY * tileW
                                      + inTileX);

                *pDstCur++ = *pSrcCur;
            }
        }
    }//16x8 Tile

    else if(sType == SWIZZLE16x8) {
        uint32_t off_x0 = swizzle_x(0);
        uint32_t off_y  = swizzle_y(0);
        uint32_t x_mask = swizzle_x(~0u);
        uint32_t y_mask = swizzle_y(~0u);
        uint32_t incr_y = swizzle_x(width);

        off_x0 += incr_y * (0/tileH);

        //Change Src and dst pos
        const uint32_t *srcL;
        uint32_t *dstL = (uint32_t *)dst, *dstP;

        uint32_t off_x;
        uint32_t pixel;

        for(int y = 0; y < height; ++y) {
            dstP = dstL;
            srcL = (uint32_t *)src + off_y;
            off_x = off_x0;

            for(int x = 0; x < width; ++x) {
                pixel = *(srcL + off_x);
                *dstP++ = pixel;
                off_x = (off_x - x_mask) & x_mask;
            }
            off_y = (off_y - y_mask) & y_mask;
            if(!off_y)
                off_x0 += incr_y;
            dstL += width;
        }
    }

}
