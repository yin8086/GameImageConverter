#ifndef ETC1BUFPARSER_H
#define ETC1BUFPARSER_H
#include "BufferParser.h"
class ETC1BufParser: public AbstractBufferParser {
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
#endif // ETC1BUFPARSER_H
