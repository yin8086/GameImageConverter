#ifndef UNITYIOPARSER_H
#define UNITYIOPARSER_H
#include "IOParser.h"
#include "BufParFactory.h"
#include "BufferParser.h"

class UnityIOParser: public AbstractIOParser {
    AbstractBufParseFactory *m_ptBufFac;
    AbstractBufferParser *m_ptParser;
    int m_iDefault16bpp;
    uint8_t *m_ptOriBuf;
public:
    UnityIOParser();

    virtual QString getPixels(uint8_t *&rpDst);
    virtual void setPixels(uint8_t *pSrc);
    virtual void parsePixels(uint8_t *pSrc, uint8_t *pDst, const QString& mode);
    virtual void invParsePixels(uint8_t *pSrc, uint8_t *&rpDst, const QString& mode);

    virtual QString exportName(const QString& origName, QString& mode) const;
    virtual void parsePals(uint8_t *&,
                                     uint8_t *,
                                     uint8_t *,
                                     const QString& );
    virtual void getPals(uint8_t *&rpDst);
    ~UnityIOParser();
};
#endif // UNITYIOPARSER_H
