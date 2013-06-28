#include <QtCore>
#include <QString>
#include "RGB888BufParser.h"


QString RGB888BufParser::parse(const unsigned char *pSrc, unsigned char *pDst, int width, int height) {
    for(int i = 0, j = 0; i < (width * height) * 3; i += 3, j += 4) {
        pDst[j]     = pSrc[i+2]; //b
        pDst[j+1]   = pSrc[i+1]; //g
        pDst[j+2]   = pSrc[i]; //r
        pDst[j+3]   = 0xff; //a
    }
    return "RGB888";
}

void RGB888BufParser::invParse(const unsigned char *pSrc, unsigned char *&rpDst, int width, int height) {
    rpDst = new unsigned char [(width * height) * 3];
    for(int i = 0, j = 0; i < (width * height) * 3; i += 3, j += 4) {
        rpDst[i]     = pSrc[j+2];
        rpDst[i+1]   = pSrc[j+1];
        rpDst[i+2]   = pSrc[j];
    }
}
