#ifndef UNITYIMAGEFILTER_H
#define UNITYIMAGEFILTER_H
#include "AbstractFilter.h"

class UnityImageFilter: public AbstractImageFilter {
public:
    int filter(uint8_t* &pDst, uint8_t* pSrc, int width, int height, const QString&);
};

#endif // UNITYIMAGEFILTER_H
