#include <QtCore>
#include <QString>
#include "PVRCT4BufParser.h"
#include <pvrtc_dll.h>

QString PVRCT4BufParser::parse(unsigned char *pSrc, unsigned char *pDst, int width, int height) {
    pvrtc_decompress(pDst, pSrc, width, height, 0, 1, 0);
    return "PVRTC4";
}

void PVRCT4BufParser::invParse(unsigned char *pSrc, unsigned char *&rpDst, int width, int height) {
    rpDst = new unsigned char [(width * height) >> 1];
    pvrtc_compress(pSrc, rpDst, width, height, 0, 1, 1, 0);
}
