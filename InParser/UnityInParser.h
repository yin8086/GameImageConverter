#ifndef UNITYINPARSER_H
#define UNITYINPARSER_H
#include "InParse.h"
#include "BufParFactory.h"
#include "BufferParser.h"

class UnityInParser: public AbstractInParser {
    AbstractBufParseFactory *m_ptBufFac;
    AbstractBufferParser *m_ptParser;
    int m_iDefault16bpp;
public:
    UnityInParser();

    QString getPixels(unsigned char *&rpDst);
    void parsePixels(unsigned char *pSrc, unsigned char *pDst, const QString &mode);
    void getPals(unsigned char *&rpDst);
    ~UnityInParser();
};

#endif // UNITYINPARSER_H
