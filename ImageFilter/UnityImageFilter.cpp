#include <QtCore>
#include <QImage>
#include "BaseDef.h"
#include "UnityImageFilter.h"

int UnityImageFilter::filter(uchar *&pDst, uchar *pSrc, int width, int height) {
    QImage im(pSrc, width, height, QImage::Format_ARGB32);
    im = im.mirrored();
    pDst = NULL;
    return SUCC_STATUS;
}
