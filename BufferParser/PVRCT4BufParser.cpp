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
    rpDst = new uint8_t [(width * height) >> 1];
    pvrtc_compress((uint8_t *)pSrc, rpDst, width, height, 0, 1, 1, 0);
}
