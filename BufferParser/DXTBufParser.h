#ifndef DXTBUFPARSER_H
#define DXTBUFPARSER_H
#include <stdint.h>
#include <stddef.h>
#include "BufferParser.h"
class DXTBufParser: public AbstractBufferParser {
public:
    QString parse(unsigned char *pSrc,
                  unsigned char *pDst,
                  int width,
                  int height);

private:
    uint32_t PackRGBA (uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    void DecompressBlockDXT1Internal (const uint8_t* block,
        uint32_t* output,
        uint32_t outputStride,
        const uint8_t* alphaValues);
    void DecompressBlockDXT1(uint32_t x, uint32_t y, uint32_t width,
        const uint8_t* blockStorage,
        uint32_t* image);
    void DecompressBlockDXT5(uint32_t x, uint32_t y, uint32_t width,
        const uint8_t* blockStorage, uint32_t* image);
    void DecompressBlockDXT3(uint32_t x, uint32_t y, uint32_t width,
        const uint8_t* blockStorage,
        uint32_t* image);

};
#endif // DXTBUFPARSER_H
