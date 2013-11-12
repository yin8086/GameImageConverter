#ifndef ARGB8888BUFPARSER_H
#define ARGB8888BUFPARSER_H
#include "BufferParser.h"
class ARGB8888BufParser: public AbstractBufferParser {
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
#endif // ARGB8888BUFPARSER_H
