#ifndef UNITYINPARSER_H
#define UNITYINPARSER_H
#include "InParse.h"
#include "BufParFactory.h"
#include "BufferParser.h"

class UnityInParser: public AbstractInParser {
    AbstractBufParseFactory *m_ptBufFac;
    AbstractBufferParser *m_ptParser;
public:
    UnityInParser();

    QString getPixels(unsigned char *&rpDst);
    int parsePixels(unsigned char *pSrc, unsigned char *pDst, const QString &mode);
    int getPals(unsigned char *&rpDst);
    ~UnityInParser();
};

#endif // UNITYINPARSER_H
