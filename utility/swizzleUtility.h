#ifndef SWIZZLEUTILITY_H
#define SWIZZLEUTILITY_H
#include <stdint.h>

const uint32_t tileW = 16;
const uint32_t tileH = 8;

enum SWIZZLETYPE {
    TILE16x8,
    SWIZZLE16x8
};


void swizzleARGB(uint8_t *dst, const uint8_t *src,
                 int width, int height,
                 SWIZZLETYPE sType = TILE16x8);
void unswizzleARGB(uint8_t *dst, const uint8_t *src,
                   int width, int height,
                   SWIZZLETYPE sType = TILE16x8) ;

uint32_t swizzle_x(uint32_t x0,SWIZZLETYPE sType = SWIZZLE16x8);
uint32_t swizzle_y(uint32_t y0, SWIZZLETYPE sType = SWIZZLE16x8);

#endif // SWIZZLEUTILITY_H
