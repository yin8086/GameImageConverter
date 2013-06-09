#ifndef UNITYINPARSER_H
#define UNITYINPARSER_H
#include "InParse.h"
#include "BufParFactory.h"
#include "BufferParser.h"

class UnityInParser: public AbstractInParser {
    AbstractBufParseFactory *m_ptBufFac;
    AbstractBufferParser *m_ptParser;
    //int m_defaultBpp;
public:
    UnityInParser();

    QString getPixels(unsigned char *&rpDst);
    int parsePixels(unsigned char *pSrc, unsigned char *pDst, const QString &mode);
    int getPals(unsigned char *&rpDst);
    //void setDefault16(int rhs) { m_default16bpp = rhs;}
    ~UnityInParser();
};

#endif // UNITYINPARSER_H
