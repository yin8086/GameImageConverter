#ifndef ALPHABUFPARSER_H
#define ALPHABUFPARSER_H
#include "BufferParser.h"
class AlphaBufParser: public AbstractBufferParser {
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

#endif // ALPHABUFPARSER_H
