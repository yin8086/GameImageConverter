#include <QtCore>
#include <QString>
#include "PVRCT4BufParser.h"
#include <pvrtc_dll.h>

QString PVRCT4BufParser::parse(unsigned char *pSrc, unsigned char *pDst, int width, int height) {
    pvrtc_decompress(pDst, pSrc, width, height, 0, 1, 0);
    return "PVRTC4";
}
