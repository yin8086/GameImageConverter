#ifndef OUTPARSER_H
#define OUTPARSER_H
#include <QtCore>
class AbstractOutParser {
public:
    virtual int write(const QString& fName, uchar* pSrc, int width, int height) = 0;
    virtual ~AbstractOutParser(){}
};

#endif // OUTPARSER_H
