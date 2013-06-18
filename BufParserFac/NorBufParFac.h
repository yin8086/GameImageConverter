#ifndef NORBUFPARFAC_H
#define NORBUFPARFAC_H
#include "BufParFactory.h"
class NormalBufParserFac:public AbstractBufParseFactory {
public:
    AbstractBufferParser* createBufParser(const QString& type);
    ~NormalBufParserFac(){}
};

#endif // NORBUFPARFAC_H
