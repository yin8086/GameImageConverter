#include <QtCore>
#include <QString>
#include "BaseDef.h"
#include "PVRCT4BufParser.h"
#include <pvrtc_dll.h>

QString PVRCT4BufParser::parse(const uint8_t *pSrc, uint8_t *pDst, int width, int height) {
    pvrtc_decompress(pDst, (uint8_t *)pSrc, width, height, 0, 1, 0);
    return "PVRTC4";
}

void PVRCT4BufParser::invParse(const uint8_t *pSrc, uint8_t *&rpDst, int width, int height) {
    size_t buffer_size = (width * height) >> 1;
    if(buffer_size < 32) {
        buffer_size = 32;  // modify buffer size must be >= 32byte
    }

    rpDst = new uint8_t [buffer_size];
    pvrtc_compress((uint8_t *)pSrc, rpDst, width, height, 0, 1, 1, 0);
}

