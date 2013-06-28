#ifndef BUFFERPARSER_H
#define BUFFERPARSER_H
class AbstractBufferParser {
public:
    virtual void invParse(const unsigned char *pSrc,
                          unsigned char *&rpDst,
                          int width,
                          int height) = 0;
    virtual QString parse(const unsigned char *pSrc,
                          unsigned char *pDst,
                          int width,
                          int height) = 0;
    virtual ~AbstractBufferParser(){}
};

#endif // BUFFERPARSER_H
