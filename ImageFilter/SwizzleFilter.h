#ifndef SWIZZLEFILTER_H
#define SWIZZLEFILTER_H
#include "AbstractFilter.h"

class SwizzleFilter: public AbstractImageFilter {
public:
    int filter(uint8_t* &pDst, uint8_t* pSrc, int width, int height, const QString& mode);
};
#endif // SWIZZLEFILTER_H
