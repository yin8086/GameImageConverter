#ifndef BUFPARFACTORY_H
#define BUFPARFACTORY_H
#include "BufferParser.h"
class AbstractBufParseFactory {
    virtual AbstractBufferParser* createBufParser(const QString& type) = 0;
};

#endif // BUFPARFACTORY_H
