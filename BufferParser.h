#ifndef BUFFERPARSER_H
#define BUFFERPARSER_H
class AbstractBufferParser {
public:
//    virtual void invParse(unsigned char *pSrc,
//                          unsigned char *pDst,
//                          int bufSize) = 0;
    virtual QString parse(unsigned char *pSrc,
                          unsigned char *pDst,
                          int width,
                          int height) = 0;
    virtual ~AbstractBufferParser(){}
};

#endif // BUFFERPARSER_H
