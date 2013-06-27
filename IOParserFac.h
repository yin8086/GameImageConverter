#ifndef IOPARSERFAC_H
#define IOPARSERFAC_H
#include "IOParser.h"

class IOParserFactory {
public:
    AbstractIOParser* createIOParser(int mode);
};
#endif // IOPARSERFAC_H
