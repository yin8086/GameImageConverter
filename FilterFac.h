#ifndef FILTERFAC_H
#define FILTERFAC_H
#include "AbstractFilter.h"

class FilterFactory {
public:
    AbstractImageFilter* createFilter(int iMode, int oMode);
};

#endif // FILTERFAC_H
