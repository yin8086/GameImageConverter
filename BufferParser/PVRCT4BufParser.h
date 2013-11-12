#ifndef PVRCT4BUFPARSER_H
#define PVRCT4BUFPARSER_H
#include "BufferParser.h"
class PVRCT4BufParser: public AbstractBufferParser {
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
#endif // PVRCT4BUFPARSER_H
