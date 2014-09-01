#ifndef ATCBUFPARSER_H
#define ATCBUFPARSER_H
#include "BufferParser.h"
class ATCBufParser: public AbstractBufferParser {
public:
    QString parse(const uint8_t *pSrc,
                  uint8_t *pDst,
                  int width,
                  int height);
    void invParse(const uint8_t *pSrc,
                  uint8_t *&rpDst,
                  int width,
                  int height);
private:
    static const unsigned MAX_COLOR_VAL;

    void DecompressATC(const uint8_t* block, uint8_t *rgba);
    void DXTC2ATC(uint8_t* block);

};
#endif // ATCBUFPARSER_H
