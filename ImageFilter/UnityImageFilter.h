#ifndef UNITYIMAGEFILTER_H
#define UNITYIMAGEFILTER_H
#include <QtCore>
#include "AbstractFilter.h"

class UnityImageFilter: public AbstractImageFilter {
public:
    int filter(uchar* &pDst, uchar* pSrc, int width, int height);
};

#endif // UNITYIMAGEFILTER_H
