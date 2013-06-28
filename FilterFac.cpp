#include<QtCore>
#include"FilterFac.h"
#include "ImageFilter/UnityImageFilter.h"

AbstractImageFilter* FilterFactory::createFilter(int iMode, int oMode) {
    if(iMode == 0)
        return new UnityImageFilter();
    else if(oMode == 0)
        return new UnityImageFilter();
    else
        return NULL;
}
