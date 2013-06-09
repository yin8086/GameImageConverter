#ifndef INPARSERFAC_H
#define INPARSERFAC_H
#include "InParse.h"

class InParserFactory {
public:
    AbstractInParser* createInParser(int mode);
};

#endif // INPARSERFAC_H
