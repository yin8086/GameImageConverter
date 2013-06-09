#include <QtCore>
#include <QString>
#include "RGB888BufParser.h"


QString RGB888BufParser::parse(unsigned char *pSrc, unsigned char *pDst, int width, int height) {
    for(int i = 0, j = 0; i < (width * height) << 1; i += 3, j += 4) {
        pDst[j]     = pSrc[i+2]; //b
        pDst[j+1]   = pSrc[i+1]; //g
        pDst[j+2]   = pSrc[i]; //r
        pDst[j+3]   = 0xff; //a
    }
    return "RGB888";
}

