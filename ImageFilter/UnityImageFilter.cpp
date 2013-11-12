#include <QtCore>
#include <QImage>
#include "BaseDef.h"
#include "UnityImageFilter.h"

int UnityImageFilter::filter(uint8_t *&pDst, uint8_t *pSrc, int width, int height, const QString&) {
    QImage im(pSrc, width, height, QImage::Format_ARGB32);
    im = im.mirrored(false,true);
    memcpy(pSrc, im.bits(), sizeof(char) * width * height * 4);
    pDst = NULL;
    return SUCC_STATUS;
}
