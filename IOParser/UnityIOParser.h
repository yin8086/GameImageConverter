#ifndef UNITYIOPARSER_H
#define UNITYIOPARSER_H
#include "IOParser.h"
#include "BufParFactory.h"
#include "BufferParser.h"

class UnityIOParser: public AbstractIOParser {
    AbstractBufParseFactory *m_ptBufFac;
    AbstractBufferParser *m_ptParser;
    int m_iDefault16bpp;
public:
    UnityIOParser();

    virtual QString getPixels(unsigned char *&rpDst);
    virtual void setPixels(unsigned char *pSrc);
    virtual void parsePixels(unsigned char *pSrc, unsigned char *pDst, const QString& mode);
    virtual void invParsePixels(unsigned char *pSrc, unsigned char *&rpDst, const QString& mode);

    virtual void getPals(unsigned char *&rpDst);
    ~UnityIOParser();
};
#endif // UNITYIOPARSER_H