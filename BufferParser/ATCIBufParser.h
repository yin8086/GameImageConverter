#ifndef ATCIBUFPARSER_H
#define ATCIBUFPARSER_H
#include "BufferParser.h"
class ATCIBufParser: public AbstractBufferParser {
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
#endif // ATCIBUFPARSER_H
