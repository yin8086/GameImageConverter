#ifndef ABSTRACTFILTER_H
#define ABSTRACTFILTER_H

class AbstractImageFilter {
public:
    virtual int filter(uint8_t* &pDst, uint8_t* pSrc, int width, int height, const QString& mode) = 0;
    virtual ~AbstractImageFilter(){}
};

#endif // ABSTRACTFILTER_H
