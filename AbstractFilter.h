#ifndef ABSTRACTFILTER_H
#define ABSTRACTFILTER_H
#include <QtCore>

class AbstractImageFilter {
public:
    virtual int filter(uchar* &pDst, uchar* pSrc, int width, int height) = 0;
    virtual ~AbstractImageFilter(){}
};

#endif // ABSTRACTFILTER_H
