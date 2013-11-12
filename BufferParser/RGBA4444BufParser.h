#ifndef RGBA4444BUFPARSER_H
#define RGBA4444BUFPARSER_H
#include "BufferParser.h"
class RGBA4444BufParser: public AbstractBufferParser {
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
#endif // RGBA4444BUFPARSER_H
