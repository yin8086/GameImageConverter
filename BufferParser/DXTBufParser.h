#ifndef DXTBUFPARSER_H
#define DXTBUFPARSER_H
#include "BufferParser.h"
class DXTBufParser: public AbstractBufferParser {
public:
    QString parse(const uint8_t *pSrc,
                  uint8_t *pDst,
                  int width,
                  int height);
    void invParse(const uint8_t *pSrc,
                  uint8_t *&rpDst,
                  int width,
                  int height);

};
#endif // DXTBUFPARSER_H
