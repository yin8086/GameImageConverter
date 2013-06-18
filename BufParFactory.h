#ifndef BUFPARFACTORY_H
#define BUFPARFACTORY_H
#include "BufferParser.h"
class AbstractBufParseFactory {
public:
    virtual AbstractBufferParser* createBufParser(const QString& type) = 0;
    virtual ~AbstractBufParseFactory(){}
};

#endif // BUFPARFACTORY_H
