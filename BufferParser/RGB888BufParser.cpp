#include <QtCore>
#include <QString>
#include "RGB888BufParser.h"


QString RGB888BufParser::parse(unsigned char *pSrc, unsigned char *pDst, int width, int height) {
    for(int i = 0, j = 0; i < (width * height) * 3; i += 3, j += 4) {
        pDst[j]     = pSrc[i+2]; //b
        pDst[j+1]   = pSrc[i+1]; //g
        pDst[j+2]   = pSrc[i]; //r
        pDst[j+3]   = 0xff; //a
    }
    return "RGB888";
}

void RGB888BufParser::invParse(unsigned char *pSrc, unsigned char *pDst, int width, int height) {
    for(int i = 0, j = 0; i < (width * height) * 3; i += 3, j += 4) {
        pDst[i]     = pSrc[j+2];
        pDst[i+1]   = pSrc[j+1];
        pDst[i+2]   = pSrc[j];
    }
}
