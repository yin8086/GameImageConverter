#ifndef NORBUFPARFAC_H
#define NORBUFPARFAC_H
#include "BufParFactory.h"
class NormalBufParserFac:public AbstractBufParseFactory {
    AbstractBufferParser* createBufParser(const QString& type);
};

#endif // NORBUFPARFAC_H
