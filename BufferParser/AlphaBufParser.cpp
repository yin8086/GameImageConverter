#include <QtCore>
#include <QString>
#include "AlphaBufParser.h"


QString AlphaBufParser::parse(unsigned char *pSrc, unsigned char *pDst, int width, int height) {
    for(int i = 0, j = 0; i < width * height; i++, j += 4) {
        pDst[j] = 0;
        pDst[j + 1] = 0;
        pDst[j + 2] = 0;
        pDst[j + 3] = pSrc[i];
    }
    return "Alpha8";
}

void AlphaBufParser::invParse(unsigned char *pSrc,
                              unsigned char *pDst,
                              int width, int height) {
    for(int i = 0, j = 0; i < width * height; i++, j += 4) {
        pDst[i] = pSrc[j+3];
    }

}
