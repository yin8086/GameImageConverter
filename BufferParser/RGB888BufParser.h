#ifndef RGB888BUFPARSER_H
#define RGB888BUFPARSER_H
#include "BufferParser.h"
class RGB888BufParser: public AbstractBufferParser {
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
#endif // RGB8888BUFPARSER_H
