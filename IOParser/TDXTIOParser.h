#ifndef TDXTIOPARSER_H
#define TDXTIOPARSER_H
#include "IOParser.h"
#include "BufParFactory.h"
#include "BufferParser.h"

class TDXTIOParser: public AbstractIOParser {
    AbstractBufParseFactory *m_ptBufFac;
    AbstractBufferParser *m_ptParser;
public:
    TDXTIOParser();
    virtual QString getPixels(uint8_t *&rpDst) ;
    virtual void setPixels(uint8_t *pSrc);
    virtual void parsePixels(uint8_t *pSrc, uint8_t *pDst, const QString& mode);
    virtual void invParsePixels(uint8_t *pSrc, uint8_t *&rpDst, const QString&);
    virtual QString exportName(const QString& origName, QString& mode) const;
    virtual void fromIndexed(uint8_t *&, uint8_t *){}
    virtual void fromMapped(uint8_t *, uint8_t *){}
    virtual void toIndexed(uint8_t *&, uint8_t *){}
    virtual void toMapped(uint8_t *, uint8_t *){}
};
#endif // TDXTIOPARSER_H
