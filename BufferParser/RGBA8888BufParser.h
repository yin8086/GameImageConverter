#ifndef RGBA8888BUFPARSER_H
#define RGBA8888BUFPARSER_H
#include "BufferParser.h"
class RGBA8888BufParser: public AbstractBufferParser {
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
#endif // RGBA8888BUFPARSER_H
