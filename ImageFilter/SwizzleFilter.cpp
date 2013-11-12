#include <QtCore>
#include "BaseDef.h"
#include "SwizzleFilter.h"

int SwizzleFilter::filter(uint8_t *&pDst,
                          uint8_t *pSrc,
                          int width,
                          int height,
                          const QString &mode) {

    if(mode == "REG" || mode == "FACE" || mode == "MAP") {

    }
}
