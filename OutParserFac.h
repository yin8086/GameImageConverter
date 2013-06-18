#ifndef OUTPARSERFAC_H
#define OUTPARSERFAC_H
#include "OutParser.h"

class OutParserFactory {
public:
    AbstractOutParser* createOutParser(int oMode);
};

#endif // OUTPARSERFAC_H
