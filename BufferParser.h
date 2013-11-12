#ifndef BUFFERPARSER_H
#define BUFFERPARSER_H
class AbstractBufferParser {
public:
    virtual void invParse(const uint8_t *pSrc,
                          uint8_t *&rpDst,
                          int width,
                          int height) = 0;
    virtual QString parse(const uint8_t *pSrc,
                          uint8_t *pDst,
                          int width,
                          int height) = 0;
    virtual ~AbstractBufferParser(){}
};

#endif // BUFFERPARSER_H
