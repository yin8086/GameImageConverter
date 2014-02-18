#ifndef BGRA4444BUFPARSER_H
#define BGRA4444BUFPARSER_H
#include "BufferParser.h"
class BGRA4444BufParser: public AbstractBufferParser {
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
#endif // BGRA4444BUFPARSER_H
