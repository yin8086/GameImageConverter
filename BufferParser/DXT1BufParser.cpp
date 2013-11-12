
#include <QtCore>
#include "squish.h"
#include "BaseDef.h"
#include "DXT1BufParser.h"

QString DXT1BufParser::parse(const uint8_t *pSrc, uint8_t *pDst, int width, int height) {

    squish::DecompressImage(pDst, width, height, pSrc, squish::kDxt1);
    uint8_t tmpVal;
    for(int i = 0; i < width*height*4; i+=4) {
        tmpVal = pDst[i];
        pDst[i] = pDst[i+2];
        pDst[i+2] = tmpVal;
    }

    return "DXT1";
}

void DXT1BufParser::invParse(const uint8_t *pSrc, uint8_t *&rpDst, int width, int height) {
    uint8_t *tmpBuf = new uint8_t[width*height*4];
    for(int i = 0; i < width*height*4; i+=4) {
        tmpBuf[i] = pSrc[i+2];
        tmpBuf[i+1] = pSrc[i+1];
        tmpBuf[i+2] = pSrc[i];
        tmpBuf[i+3] = pSrc[i+3];
    }
    int bufW = ((width % 4) ? (width/4+1) : (width /4) ) << 2;
    int bufH = ((height % 4) ? (height/4+1) : (height /4) ) << 2;

    rpDst = new uint8_t [(bufW * bufH)>>1];
    squish::CompressImage(tmpBuf, width, height, rpDst, squish::kDxt1);
    delete []tmpBuf;
}


