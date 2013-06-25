#include <QtCore>
#include "squish.h"
#include "DXTBufParser.h"

QString DXTBufParser::parse(unsigned char *pSrc, unsigned char *pDst, int width, int height) {

    squish::DecompressImage(pDst, width, height, pSrc, squish::kDxt5);
    quint8 tmpVal;
    for(int i = 0; i < width*height*4; i+=4) {
        tmpVal = pDst[i];
        pDst[i] = pDst[i+2];
        pDst[i+2] = tmpVal;
    }

    return "DXT5";
}

void DXTBufParser::invParse(unsigned char *pSrc, unsigned char *pDst, int width, int height) {
    quint8 tmpBuf[width*height*4];
    for(int i = 0; i < width*height*4; i+=4) {
        tmpBuf[i] = pSrc[i+2];
        tmpBuf[i+1] = pSrc[i+1];
        tmpBuf[i+2] = pSrc[i];
        tmpBuf[i+3] = pSrc[i+3];
    }
    squish::CompressImage(tmpBuf, width, height, pDst, squish::kDxt5);
}


